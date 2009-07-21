/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Wed Jul 22 00:19:51 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"
#include "coor.h"

#include <stdlib.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>

#include "graphic.h"

/**!
 * @author	rannou_s
 * Let's leave SDL
 */

static __inline int
graphic_cleaner_sdl(client_t *client, graphic_t *graphic)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  TTF_Quit();
  SDL_Quit();
  graphic = graphic; /* unused param? */
  return (SUCCESS);
}

/**!
 * @author	rannou_S
 * Cleans window's structure
 */

static __inline int
graphic_cleaner_window(window_t *window)
{
  if (window == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (window->title != NULL)
    free(window->title);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's clean graphic's structure
 * When an error occurs in a part of the cleaner, we continue to unload
 * everything, let's forget it :(
 * note: graphic == NULL is not a mistake as the parser may fail.
 */

int
graphic_cleaner(client_t *client, graphic_t *graphic) 
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic != NULL)
    {
      graphic_cleaner_window(&graphic->window);
    }
  graphic_cleaner_sdl(client, graphic);
  return (SUCCESS);
}
