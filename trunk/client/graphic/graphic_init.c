/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Sat Aug  1 02:15:07 2009 
*/

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>

#include "coor.h"
#include "font.h"
#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "SDL_console.h"
#include "graphic.h"
#include "graphic_font.h"
#include "graphic_colors.h"
#include "graphic_texture.h"
#include "event.h"

#define	WIN		(&graphic->window)	/* shortcut */

#define	SDL_BPP		32
#define	SDL_VIDEO_FLAGS	SDL_OPENGL

/**!
 * @author	rannou_s
 * Initialize screens and 2d buffer
 */

static __inline int
graphic_init_video_screen(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
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
       SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_SWSURFACE,
			    WIN->width, WIN->height, SDL_BPP, 
			    0, 0, 0, 255)) == NULL)
    {
      ERR_RAISE(EC_SDL_CREATE_SURFACE, SDL_GetError());
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialize video (SDL/OpenGL)
 */

static __inline int
graphic_init_video(client_t *client, graphic_t *graphic)
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
  if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == ERROR)
    {
      ERR_RAISE(EC_SDL_INIT, SDL_GetError());
      return (ERROR);
    }
  return (graphic_init_video_screen(client, graphic));
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
  if (graphic_init_video(client, graphic) == ERROR)
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
 * Let's initialize the fpsbox
 */

#define	FPSBOX_MARGIN	10

static __inline int
graphic_init_fpsbox(client_t *client, graphic_t *graphic)
{
  SDL_Color		*color;
  int			font_id;

  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic->fpsbox.state == OFF)
    return (SUCCESS);
    color = graphic_colors_get(COL_2D_INFO);
  if (color == NULL)
    {
      ERR_RAISE(EC_LOADER_COLOR_UNKNOWN, COL_2D_INFO);
      return (ERROR);
    }
  if ((font_id = graphic_font_getid(FONT_2D_INFO)) == ERROR)
    {
      ERR_RAISE(EC_SDL_TTF_GET, FONT_2D_INFO);
      return (ERROR);
    }
  graphic->fpsbox.font.color = color;
  graphic->fpsbox.font.font_id = font_id;
  graphic->fpsbox.font.pos.x = FPSBOX_MARGIN;
  graphic->fpsbox.font.pos.y = FPSBOX_MARGIN;
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's initialize the console
 * @todo	link this defines with a nice .ini file
 */

#define		FONT	"internals/fonts/ConsoleFont.bmp"
#define		BG	"internals/textures/console.png"
#define		LINES	100
#define		PROMPT	"> "

/* don't want to create one header file for one prototype */
void
console_command_handler(ConsoleInformation *console, char *command);

static __inline int
graphic_init_console(client_t *client, graphic_t *graphic)
{
  SDL_Rect			rect;

  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  memset(&rect, 0, sizeof(rect));
  rect.w = WX;
  rect.x = 0;
  rect.y = 0;
  rect.h = WY / 2;
  graphic->console = CON_Init(FONT, graphic->opengl.screen2d, LINES, rect);
  if (graphic->console == NULL)
    {
      ERR_RAISE(EC_SDL_CONSOLE_INI);
      return (ERROR);
    }
  CON_SetHideKey(graphic->console, SDLK_BACKQUOTE);
  CON_SetPrompt(graphic->console, PROMPT);
  CON_Topmost(graphic->console);
  CON_Background(graphic->console, BG, 0, 0);
  CON_SetExecuteFunction(graphic->console, &console_command_handler);
  CON_SetTabCompletion(graphic->console, &console_tab_handler);
  console_event_init(client);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialize camera's positions
 */

static __inline int
graphic_init_camera(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  graphic->camera.distance = 5;
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
    return (ERROR);
  if (graphic_load_ttf() == ERROR)
    return (ERROR);
  if (graphic_load_colors() == ERROR)
    return (ERROR);
  if (graphic_load_textures() == ERROR)
    return (ERROR);
  if (graphic_init_fpsbox(client, graphic) == ERROR)
    return (ERROR);
  if (graphic_init_console(client, graphic) == ERROR)
    return (ERROR);
  if (graphic_init_camera(client, graphic) == ERROR)
    return (ERROR);
  return (SUCCESS);
}
