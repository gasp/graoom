/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Wed Jul 29 20:45:43 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "errors.h"
#include "coor.h"
#include "log.h"

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>

#include "font.h"
#include "client.h"
#include "graphic.h"
#include "graphic_font.h"
#include "graphic_colors.h"
#include "graphic_texture.h"
#include "SDL_console.h"

/**!
 * @author	rannou_s
 * Let's leave SDL
 */

static  int
graphic_cleaner_sdl(client_t *client, graphic_t *graphic)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic != NULL)
    {
      if (graphic->opengl.screen2d != NULL)
	SDL_FreeSurface(graphic->opengl.screen2d);
    }
  TTF_Quit();
  SDL_Quit();
  return (SUCCESS);
}

/**!
 * @author	rannou_S
 * Cleans window's structure and console
 */

static  int
graphic_cleaner_main(graphic_t *graphic)
{
  if (graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic->window.title != NULL)
    {
      free(graphic->window.title);
    }
  if (graphic->console != NULL)
    {
      CON_Destroy(graphic->console);
    }
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
    graphic_cleaner_main(graphic);
  graphic_clean_ttf();
  graphic_clean_colors();
  graphic_clean_textures();
  graphic_cleaner_sdl(client, graphic);
  return (SUCCESS);
}
