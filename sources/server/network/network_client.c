/*
** client.c for battletrantor in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 14 11:02:01 2009 Sebastien Rannou
** Last update Sun Aug  9 14:38:25 2009 
*/

#include <sys/select.h>

#include "shortcuts.h"
#include "lists.h"
#include "network.h"
#include "errors.h"
#include "log.h"
#include "server_log.h"

#include <stdlib.h>
#include <stdio.h>

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
      LOG(LOG_CLIENT_KICK_DEF, client->id);
    }
  else
    {
      LOG(LOG_CLIENT_KICK, client->id, message);
    }
  client->state |= CLIENT_KICKED; /* it's a smiley \0/ */
  return (SUCCESS);
}
