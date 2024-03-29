/*
** loop.c for battletrantor in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sat Jul 18 18:24:41 2009 sebastien rannou
** Last update Thu Oct  1 14:12:03 2009 sebastien rannou
*/

#include <sys/select.h>

#include "lists.h"
#include "server.h"
#include "errors.h"
#include "shortcuts.h"
#include "network.h"
#include "client.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/**!
 * @author	rannou_s
 * No need to make a header file here as these functions are internals
 * of network's module, and are called only here.
 */

int	/* let's send data */
network_client_send(server_t *server, network_client_t *client);

int	/* let's read incoming data */
network_read_from_client(server_t *server, network_client_t *client);

int	/* let's accept a new connection */
network_accept_new_connection(server_t *server, int sock);

/**!
 * @author	rannou_s
 * called when there's acitvity somewhere...
 * check where it comes from and call the appropriated function
 */

static int
network_loop_activity(server_t *server)
{
  list_t		*cur;
  network_client_t	*client;

  if (FD_ISSET(NETWORK->primary_socket, &NETWORK->select.readfs))
    {
      network_accept_new_connection(server, NETWORK->primary_socket);
    }
  for (cur = NETWORK->clients; cur != NULL; cur = cur->li_next)
    {
      if ((client = (network_client_t *) cur->data) != NULL)
	{
	  if (FD_ISSET(client->sock, &NETWORK->select.readfs))
	    {
	      network_read_from_client(server, client);
	    }
	  else if (client->obuff.offset > 0)
	    {
	      network_client_send(server, client);
	    }
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Ninja's skill: kick a client while looping on the list with
 * some pointer's modifications
 */

static int
network_loop_init_pop(network_t *network, list_t **ptr)
{
  list_t		*cur;
  network_client_t	*client;

  cur = *ptr;
  *ptr = cur->li_next;
  if ((client = (network_client_t *) cur->data) != NULL)
    {
      if (close(client->sock) == ERROR)
	{
	  ERR_RAISE(EC_SYS_CLOSE, strerror(errno));
	}
    }
  if (cur->li_next != NULL)
    {
      cur->li_next->li_prev = cur->li_prev;
    }
  if (cur->li_prev == NULL)
    {
      network->clients = cur->li_next;
      /* kick -> client->data */
      free(cur);
      return (SUCCESS);
    }
  cur->li_prev->li_next = cur->li_next;
  /* kick client->data */
  free(cur);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialize fds to prepare the select call
 * As we need to optimize this part of the program, this is also the
 * place where we perform operations on each client and players 
 * (would be a mistake to loop again on that list in another part of the code)
 * This is also the place where we kick clients:
 * -> ninja's skill: we kick him while looping on the list
 */

#define	MAXFD(val)	((val) > network->select.current_fd_max ? (val) : \
			 network->select.current_fd_max)

static int
network_loop_init(network_t *network)
{
  list_t		*cur;
  network_client_t	*client;

  FD_ZERO(&network->select.readfs);
  FD_SET(network->primary_socket, &network->select.readfs);
  network->select.current_fd_max = MAXFD(network->primary_socket);
  cur = network->clients;
  while (cur != NULL)
    {
      client = (network_client_t *) cur->data;
      if (client->state & CLIENT_KICKED)
	{
	  network_loop_init_pop(network, &cur);
	}
      else
	{
	  FD_SET(client->sock, &network->select.readfs);
	  network->select.current_fd_max = MAXFD(client->sock);
	  cur = cur->li_next;
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Main loop of the server, everything is made around
 * the select and we try to optimize as much as possible
 * what is made here.
 */

int
network_loop(server_t *server)
{
  int		res;
  
  if (server == NULL || NETWORK == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  while (server->state == SERVER_STATE_ON)
    {
      network_loop_init(NETWORK);
      res = select(NETWORK->select.current_fd_max + 1, 
		   &NETWORK->select.readfs,
		   NULL, NULL, NULL);
      if (ERROR == res)
	ERR_RAISE(EC_SYS_SELECT);
      else if (res > 0)
	network_loop_activity(server);
    }
  return (SUCCESS);
}
