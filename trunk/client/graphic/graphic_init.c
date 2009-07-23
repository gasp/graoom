/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Thu Jul 23 12:32:44 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"
#include "coor.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "graphic.h"
#include "graphic_font.h"

#define	WIN	(&graphic->window)	/* shortcut */

/**!
 * @author	rannou_s
 * Initialize SDL video (window, screen2d, ...)
 */

#define	SDL_BPP		32
#define	SDL_VIDEO_FLAGS	SDL_HWSURFACE | SDL_DOUBLEBUF	/* openGL? */

static __inline int
graphic_init_sdl_video(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == ERROR)
    {
      ERR_RAISE(EC_SDL_INIT, SDL_GetError());
      return (ERROR);
    }
  WIN->screen = SDL_SetVideoMode(WIN->width, WIN->height, 
				 SDL_BPP, SDL_VIDEO_FLAGS);
  if (WIN->screen == NULL)
    {
      ERR_RAISE(EC_SDL_SETVIDEO, SDL_GetError());
      return (ERROR);
    }
  SDL_WM_SetCaption(WIN->title, NULL); /* void function? :( too bad */
  if ((graphic->opengl.screen2d = 
       SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_HWSURFACE,
			    WIN->width, WIN->height, SDL_BPP, 
			    0, 0, 0, 0)) == NULL)
    {
      ERR_RAISE(EC_SDL_CREATE_SURFACE, SDL_GetError());
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's initialize SDL!
 * At that moment we force BPP to be 32, don't know if it can be
 * a good idea to allow setting it to 16/24, will have to make some searches
 */

static __inline int
graphic_init_sdl(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic_init_sdl_video(client, graphic) == ERROR)
    return (ERROR);
  if (TTF_Init() == ERROR)
    {
      ERR_RAISE(EC_SDL_TTF_INIT, TTF_GetError());
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialization of everything related to graphic's thread
 */

int
graphic_init(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic_init_sdl(client, graphic) == ERROR)
    {
      return (ERROR);
    }
  if (graphic_load_ttf() == ERROR)
    {
      return (ERROR);
    }
  return (SUCCESS);
}
