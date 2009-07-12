/*
** network.c for graoom in /usr/home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 17:08:02 2009 Sebastien Rannou
** Last update Sun Jul 12 21:41:32 2009 Sebastien Rannou
*/

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
 * initialize the primary network socket
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
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * initialization of the network
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
