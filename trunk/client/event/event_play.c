/*
** event_play.c for graoom in /home/rannou_s/Work/graoom/client
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 29 21:06:06 2009 sebastien rannou
** Last update Wed Jul 29 23:39:29 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "coor.h"
#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "event.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"
#include "font.h"
#include "graphic.h"

/**!
 * @author	rannou_s
 * These functions defines ingame actions
 */

/**!
 * @author	rannou_s
 * Let's straff on the left
 */

int
event_move_left(client_t *client, event_t *event)
{
  graphic_t		*graphic;

  if (client == NULL || event == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  graphic = client->graphic;
  CR->z++;
  return (SUCCESS);
}

