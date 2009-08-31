/*
** connection.c for graoom in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 23:27:33 2009 sebastien rannou
** Last update Fri Aug 14 22:07:04 2009 
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"
#include "log.h"
#include "client.h"
#include "cmd.h"
#include "server_log.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

/**!
 * @author	rannou_s
 * If the fd's value is too high, let's get rid of it
 */

static int
network_accept_new_connection_limit(network_t *network, int sock)
{
  if (sock >= network->configuration.num_max_connection)
    {
      ERR_RAISE(EC_NETWORK_MAX, network->configuration.num_max_connection);
      if (close(sock) == ERROR)
	{
	  ERR_RAISE(EC_SYS_CLOSE);
	}
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * configure the given socket, set it to non-blocking mode
 * with fnctl
 */

static int
network_accept_new_connection_cfg(int sock)
{
  if (fcntl(sock, F_SETFL, O_NONBLOCK) == ERROR)
    {
      ERR_RAISE(EC_SYS_FCNTL);
      if (close(sock) == ERROR)
	{
	  ERR_RAISE(EC_SYS_CLOSE);
	}
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * creates a new client and pushes it to the client's list
 * cleans up everything if something goes wrong
 */

static int
network_accept_new_connection_push(server_t *server, int sock, 
				   struct sockaddr_in *addr)
{
  network_client_t	*new_client;

  if ((new_client = malloc(sizeof(*new_client))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  memset(new_client, 0, sizeof(*new_client));
  new_client->ip = inet_ntoa(addr->sin_addr);
  if (new_client->ip == (char *) INADDR_NONE)
    {
      ERR_RAISE(EC_SYS_INET_NTOA);
      if (close(sock) == ERROR)
	{
	  ERR_RAISE(EC_SYS_CLOSE);
	}
      free(new_client);
      return (ERROR);
    }
  if (list_push(&NETWORK->clients, new_client) == ERROR)
    {
      ERR_RAISE(EC_SYS_MALLOC);
      if (close(sock) == ERROR)
	{
	  ERR_RAISE(EC_SYS_CLOSE);
	}
      free(new_client);
      return (ERROR);
    }
  new_client->sock = sock;
  new_client->id = ++NETWORK->last_client_id;
  cmd_welcome(server, new_client);
  cmd_map(server, new_client);
  LOG(LOG_CLIENT_NEW, new_client->ip);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * accepts a new client
 * -> initialize its socket
 * -> pushes it to client's list
 */

int
network_accept_new_connection(server_t *server, int sock)
{
  struct sockaddr_in	saddr;
  socklen_t		size;
  int			client_sock;
  
  if (server == NULL || NETWORK == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if (!(sock > 0))
    {
      ERR_RAISE(EC_SYS_FD, sock);
      return (ERROR);
    }
  size = sizeof(struct sockaddr);
  client_sock = accept(sock, (struct sockaddr *) &saddr, &size);
  if (client_sock == ERROR)
    {
      ERR_RAISE(EC_SYS_ACCEPT);
      return (ERROR);
    }
  if (network_accept_new_connection_limit(NETWORK, client_sock) ||
      network_accept_new_connection_cfg(client_sock) ||
      network_accept_new_connection_push(server, client_sock, &saddr))
    {
      return (ERROR);
    }
  return (SUCCESS);
}
