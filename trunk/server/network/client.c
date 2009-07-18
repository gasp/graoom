/*
** client.c for graoom in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 14 11:02:01 2009 Sebastien Rannou
** Last update Sun Jul 19 00:19:44 2009 sebastien rannou
*/

#include <sys/select.h>

#include "shortcuts.h"
#include "lists.h"
#include "network.h"
#include "errors.h"
#include "log.h"

#include <stdlib.h>
#include <stdarg.h>

/**!
 * @author	rannou_s
 * changes client's state and prints a message info
 * message should never be NULL but as this is a minor
 * mistake, that has no incidence, we ignore it
 */

int
client_kick(network_client_t *client, char *message)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if (message == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      LOG("kicking client [%d]: unknow reason", client->id);
    }
  else
    {
      LOG("kicking client [%d]: %s", client->id, message);
    }
  client->state |= CLIENT_KICKED;
  return (SUCCESS);
}
