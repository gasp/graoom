/*
** network.c for graoom in /usr/home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 17:08:02 2009 Sebastien Rannou
** Last update Mon Jul 13 22:36:34 2009 Sebastien Rannou
*/

#include "lists.h"
#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"
#include "log.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>

/**!
 * @author	rannou_s
 * If the fd's value is too high, let's get rid of it
 */

static __inline int
network_accept_new_connection_limit(server_t *server, int sock)
{
  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
  if (sock >= NETWORK->configuration.num_max_connection)
    {
      ERR_RAISE(EC_NETWORK_MAX, NETWORK->configuration.num_max_connection);
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
network_accept_new_connection_cfg(server_t *server, int sock)
{
  if (server == NULL)
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
network_accept_new_connection_push(server_t *server, int sock, 
				   struct sockaddr_in *addr)
{
  network_client_t	*new_client;

  if (server == NULL || addr == NULL)
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
  new_client->cli_ip = inet_ntoa(addr->sin_addr);
  if (new_client->cli_ip == (char *) INADDR_NONE)
    {
      ERR_RAISE(EC_SYS_INET_NTOA);
      if (close(sock) == ERROR)
	ERR_RAISE(EC_SYS_CLOSE);
      free(new_client);
      return (ERROR);
    }
  if (list_push(&NETWORK->li_clients, new_client) == ERROR)
    {
      ERR_RAISE(EC_SYS_MALLOC);
      if (close(sock) == ERROR)
	ERR_RAISE(EC_SYS_CLOSE);
      free(new_client);
      return (ERROR);
    }
  new_client->cli_socket = sock;
  LOG("new connection accepted from (%s)", new_client->cli_ip);
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
  struct sockaddr_in	sockaddr;
  socklen_t		size;
  int			client_socket;

  if (server == NULL)
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
  client_socket = accept(sock, (struct sockaddr *) &sockaddr, &size);
  if (client_socket == ERROR)
    {
      ERR_RAISE(EC_SYS_ACCEPT);
      return (ERROR);
    }
  if (network_accept_new_connection_limit(server, client_socket))
    return (ERROR);
  if (network_accept_new_connection_push(server, client_socket, &sockaddr))
    return (ERROR);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * initialize the primary network socket, which will accept new connections
 */

static __inline int
network_initialize_primary_sock(network_t *network)
{
  struct sockaddr_in	iost;
  int			sock;

  if (network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == ERROR)
    {
      ERR_RAISE(EC_NETWORK_SOCK, strerror(errno));
      return (ERROR);
    }
  iost.sin_family = AF_INET;
  iost.sin_port = htons(network->configuration.port);
  iost.sin_addr.s_addr= INADDR_ANY;
  if (bind(sock, (struct sockaddr *) &iost, sizeof(struct sockaddr)) == ERROR)
    {
      ERR_RAISE(EC_NETWORK_SOCK, strerror(errno));
      if (close(sock) == ERROR)
	ERR_RAISE(EC_SYS_CLOSE, strerror(errno));
      return (ERROR);
    }
  if (listen(sock, network->configuration.num_max_connection) == ERROR)
    {
      ERR_RAISE(EC_NETWORK_SOCK, strerror(errno));
      if (close(sock) == ERROR)
	ERR_RAISE(EC_SYS_CLOSE, strerror(errno));
      return (ERROR);      
    }
  network->primary_socket = sock;
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * initialization of the network:
 * -> initialize the primary socket that will accept connections
 */

int
network_initialize(server_t *server)
{
  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (network_initialize_primary_sock(&server->network) == ERROR)
    {
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Called before leaving the program, clean everything that was
 * loaded by network_initialize
 * -> close primary socket
 */

int
network_clean(server_t *server)
{
  network_t		*network;

  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  network = &server->network;
  if (network->primary_socket > 0)
    {
      if (close(network->primary_socket) == ERROR)
	{
	  ERR_RAISE(EC_SYS_CLOSE);
	}
    }
  return (SUCCESS);
}
