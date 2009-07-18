/*
** loop.c for graoom in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sat Jul 18 18:24:41 2009 sebastien rannou
** Last update Sun Jul 19 00:33:36 2009 sebastien rannou
*/

#include <stdlib.h>
#include <sys/select.h>

#include "lists.h"
#include "server.h"
#include "errors.h"
#include "shortcuts.h"
#include "network.h"
#include "client.h"

/**!
 * @author	rannou_s
 * No need to make a header file here as these functions are internals
 * of network's module, and are called only here.
 */

int	/* let's read incoming data */
network_read_from_client(server_t *server, network_client_t *client);

int	/* let's accept a new connection */
network_accept_new_connection(server_t *server, network_t *network, int sock);

/**!
 * @author	rannou_s
 * called when there's acitvity somewhere...
 * check where it comes from and call the appropriated function
 */

static __inline int
network_loop_activity(server_t *server, network_t *network)
{
  list_t		*cur;
  network_client_t	*client;

  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
  if (FD_ISSET(network->primary_socket, &network->select.readfs))
    network_accept_new_connection(server, network, network->primary_socket);
  for (cur = network->clients; cur != NULL; cur = cur->li_next)
    {
      if ((client = (network_client_t *) cur->data) != NULL)
	{
	  if (FD_ISSET(client->sock, &network->select.readfs))
	    network_read_from_client(server, client);
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialize fds to prepare the select call
 * As we need to optimize this part of the program, this is also the
 * place where we perform operations on each client and players 
 * (would be a mistake to loop again on that list in another part of the code)
 * This is also the place where we kick clients.
 */

#define	MAXFD(val)	((val) > network->select.current_fd_max ? (val) : \
			 network->select.current_fd_max)

static __inline int
network_loop_init(server_t *server, network_t *network)
{
  list_t		*cur;
  network_client_t	*client;

  if (server == NULL || network == NULL)
   {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
  FD_ZERO(&network->select.readfs);
  FD_SET(network->primary_socket, &network->select.readfs);
  network->select.current_fd_max = MAXFD(network->primary_socket);
  cur = network->clients;
  while (cur != NULL)
    {
      client = (network_client_t *) cur->data;
      if (client->state & CLIENT_KICKED)
	{
	  /* Let's kick him */
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
network_loop(server_t *server, network_t *network)
{
  int		res;
  
  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  while (server->state == SERVER_STATE_ON)
    {
      network_loop_init(server, network);
      res = select(network->select.current_fd_max + 1, 
		   &network->select.readfs,
		   NULL, NULL, NULL);
      if (ERROR == res)
	ERR_RAISE(EC_SYS_SELECT);
      else if (res > 0)
	network_loop_activity(server, network);
    }
  return (SUCCESS);
}
