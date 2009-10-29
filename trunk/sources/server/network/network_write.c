/*
** write.c for battletrantor in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 10:24:32 2009 sebastien rannou
** Last update Fri Aug 14 22:08:04 2009 
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"
#include "client.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

/**!
 * @author	rannou_s
 * Performs sending of information to a client
 * If there's something to read on its socket, we do not send
 * anything (as there's a probability that this client is disconnect) so
 * as to avoid writing on a dead socket.
 */

int
network_client_send(server_t *server, network_client_t *client)
{
  int		res;

  if (server == NULL || client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  res = send(client->sock, client->obuff.buffer, client->obuff.offset, 0);
  if (res == -1)
    {
      ERR_RAISE(EC_SYS_SEND, strerror(errno));
      return (ERROR);
    }
  if (res > 0)
    {
      memmove(client->obuff.buffer, &client->obuff.buffer[res], 
	      IBUFF_SIZE - res);
      client->obuff.offset -= res;
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Send a message to the client by adding data to it's output
 * buffer, we use varargs so as not to waste time playing with
 * snprintf each time we need to send something...
 * Do not perform the sending, only bufferize what we need to send
 * Here's a limit of that system: if we need to send a lot of data to a client,
 * we won't be able to send more than IBUFF_SIZE (else the client will be kicked)
 */

int
network_client_write(network_client_t *client, char *fmt, ...)
{
  int			len;
  char			buffer[IBUFF_SIZE + 1];
  va_list		ap;

  if (client == NULL || fmt == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  va_start(ap, fmt);
  vsnprintf(buffer, IBUFF_SIZE, fmt, ap);  
  va_end(ap);
  len = strlen(buffer);
  if ((client->obuff.offset + len >= IBUFF_SIZE))
    {
      client_kick(client, CLI_KICK_OVERFLOW);
      return (ERROR);
    }
  strcpy(&client->obuff.buffer[client->obuff.offset], buffer);
  client->obuff.offset += len;
  return (SUCCESS);
}
