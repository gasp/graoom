/*
** network.c for graoom in /usr/home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 17:08:02 2009 Sebastien Rannou
** Last update Mon Jul 13 10:40:32 2009 Sebastien Rannou
*/

#include "lists.h"
#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

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
  network->primary_socket = sock;
  network->current_fd_max = MAX(network->current_fd_max, sock);
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
 */

int
network_clean(server_t *server)
{
  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  return (SUCCESS);
}
