/*
** connection.c for graoom in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 23:27:33 2009 sebastien rannou
** Last update Fri Jul 17 23:28:38 2009 sebastien rannou
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"
#include "log.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/**!
 * @author	rannou_s
 * If the fd's value is too high, let's get rid of it
 */

static __inline int
network_accept_new_connection_limit(server_t *server, network_t *network, 
				    int sock)
{
  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
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

static __inline int
network_accept_new_connection_cfg(server_t *server, network_t *network, 
				  int sock)
{
  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
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

static __inline int
network_accept_new_connection_push(server_t *server, network_t *network, 
				   int sock, struct sockaddr_in *addr)
{
  network_client_t	*new_client;

  if (server == NULL || addr == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((new_client = malloc(sizeof(*new_client))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC);
      return (ERROR);
    }
  memset(new_client, 0, sizeof(*new_client));
  new_client->ip = inet_ntoa(addr->sin_addr);
  if (new_client->ip == (char *) INADDR_NONE)
    {
      ERR_RAISE(EC_SYS_INET_NTOA);
      if (close(sock) == ERROR)
	ERR_RAISE(EC_SYS_CLOSE);
      free(new_client);
      return (ERROR);
    }
  if (list_push(&network->clients, new_client) == ERROR)
    {
      ERR_RAISE(EC_SYS_MALLOC);
      if (close(sock) == ERROR)
	ERR_RAISE(EC_SYS_CLOSE);
      free(new_client);
      return (ERROR);
    }
  new_client->sock = sock;
  LOG("new connection accepted from (%s)", new_client->ip);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * accepts a new client
 * -> initialize its socket
 * -> pushes it to client's list
 */

int
network_accept_new_connection(server_t *server, network_t *network, int sock)
{
  struct sockaddr_in	saddr;
  socklen_t		size;
  int			client_sock;

  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
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
  if (network_accept_new_connection_limit(server, network, client_sock))
    return (ERROR);
  if (network_accept_new_connection_push(server, network, client_sock, &saddr))
    return (ERROR);
  return (SUCCESS);
}

