/*
** event_behavior.c for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 14:45:25 2009 sebastien rannou
** Last update Wed Jul 29 01:19:46 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "coor.h"
#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "SDL_console.h"
#include "event.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"
#include "font.h"
#include "graphic.h"

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

/**!
 * @author	rannou_s
 * Switch the console mode
 */

int
event_console_toggle(client_t *client, event_t *event)
{
  graphic_t			*graphic;

  if (client == NULL || event == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  graphic = client->graphic;
  CON_Show(graphic->console);
  return (SUCCESS);
}
