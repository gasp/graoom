/*
** init.c for graoom in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 21:37:06 2009 sebastien rannou
** Last update Fri Aug 14 22:07:13 2009 
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "errors.h"
#include "network.h"
#include "server.h"

#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/**!
 * @author	rannou_s
 * initialize the primary network socket, which will accept new connections
 */

static int
network_initialize_primary_sock(network_t *network)
{
  struct sockaddr_in	iost;
  int			sock;
  
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
network_initialize(server_t *server, network_t *network)
{
  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if (network_initialize_primary_sock(network) == ERROR)
    {
      return (ERROR);
    }
  return (SUCCESS);
}
