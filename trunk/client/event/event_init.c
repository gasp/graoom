/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Wed Jul 29 21:02:48 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "coor.h"
#include "font.h"
#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"

#include <stdlib.h>

#include "SDL_console.h"
#include "event.h"
#include "graphic.h"

/**!
 * @author	rannou_s
 * Initialization of event's
 */

#define	KEY_REPEAT		10

int
event_init(client_t *client, event_t *event)
{
  if (client == NULL || event == NULL || client->graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
  return (SUCCESS);
}
