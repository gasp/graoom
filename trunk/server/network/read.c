/*
** network.c for graoom in /usr/home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 17:08:02 2009 Sebastien Rannou
** Last update Sat Jul 18 22:54:38 2009 sebastien rannou
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"
#include "log.h"
#include "client.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define	NET_READ_SIZE	1024
#define	NET_WRITE_SIZE	1024

/**!
 * @author	rannou_s
 * Store data read from socket, and call a function when the content
 * from a query is entierely fetched
 */

static __inline int
network_read_from_client_store(server_t *server, network_client_t *client,
			       char *buffer)
{
  char			*ptr;
  int			len;
  int			off;

  if (server == NULL || client == NULL || buffer == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
  len = strlen(buffer);
  if ((len + client->ibuff.offset) > IBUFF_SIZE)
    {
      client_kick(client, CLI_KICK_OVERFLOW);
      return (ERROR);
    }
  memmove(&client->ibuff.buffer[client->ibuff.offset], buffer, len);
  client->ibuff.offset += len;
  if ((ptr = strchr(buffer, '\n')) != NULL)
    {
      *ptr = '\0';
      LOG("executing command %s", buffer);
      off = (buffer + IBUFF_SIZE) - ptr;
      memmove(buffer, ptr + 1, off);
      client->ibuff.offset = off;
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * read data from a socket
 */

int
network_read_from_client(server_t *server, network_client_t *client)
{
  char			buffer[NET_READ_SIZE + 1];
  int			nb_read;

  if (server == NULL || client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  nb_read = read(client->sock, buffer, NET_READ_SIZE);
  if (nb_read == ERROR || nb_read < 0)
    {
      ERR_RAISE(EC_SYS_READ, strerror(errno));
      client_kick(client, CLI_KICK_READ_ERR);
      return (ERROR);
    }
  else if (nb_read == 0)
    {
      client_kick(client, CLI_KICK_CLOSED);
      return (SUCCESS);
    }
  buffer[nb_read] = '\0';
  return (network_read_from_client_store(server, client, buffer));
}