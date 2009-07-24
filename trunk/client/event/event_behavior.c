/*
** event_behavior.c for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 14:45:25 2009 sebastien rannou
** Last update Fri Jul 24 01:36:48 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "event.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"

/**!
 * Events that change the behavior of the client
 */

/**!
 * @author	rannou_s
 * Change client's state
 */

int
event_leave(client_t *client, event_t *event)
{
  if (client == NULL || event == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  LOG(LOG_LEAVE);
  client->state = CLIENT_STATE_OFF;
  return (SUCCESS);
}
