/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Thu Jul 23 18:39:13 2009 sebastien rannou
*/

#ifndef	_BSD_SOURCE	/* strdup on linux */
#define	_BSD_SOURCE
#endif

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"
#include "ini.h"
#include "coor.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "graphic.h"

#define	CLIENT_X_VAL	"window_width"
#define	CLIENT_Y_VAL	"window_height"
#define	CLIENT_NAME_VAL	"window_title"
#define	CLIENT_MAX_FPS	"max_fps"

/**!
 * @author	rannou_s
 * Fetch information about window resolution
 */

static __inline int
graphic_parser_fetch_winsize(graphic_t *graphic, ini_section_t *section)
{
  char		*entry;

  if (graphic == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((entry = ini_retrieve_entry_from_section(section, CLIENT_X_VAL)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, CLIENT_X_VAL, section->name);
      return (ERROR);
    }
  if ((graphic->window.width = atoi(entry)) <= 0)
    {
      ERR_RAISE(EC_LOADER_GFX_WINX, graphic->window.width);
      return (ERROR);
    }
  if ((entry = ini_retrieve_entry_from_section(section, CLIENT_Y_VAL)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, CLIENT_Y_VAL, section->name);
      return (ERROR);
    }
  if ((graphic->window.height = atoi(entry)) <= 0)
    {
      ERR_RAISE(EC_LOADER_GFX_WINY, graphic->window.height);
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Check the resolution ration, just add a new rank
 * in allowed_format_t to allow another ratio :)
 */

typedef struct	allowed_format_s
{
  int		x;
  int		y;
}		allowed_format_t;

static allowed_format_t
global_formats[] = 
  {
    {4,		3},	/* 4/3 (800*600)*/
    {16,	9},	/* 16/9 */
    {0,	0}		/* End of array */
  };

static __inline int
graphic_parser_check_winsize(graphic_t *graphic)
{
  int		i;
  int		wx;
  int		wy;
  int		match;

  if (graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  match = 0;
  for (i = 0; global_formats[i].x != 0; i++)
    {
      wx = global_formats[i].y * graphic->window.width;
      wy = global_formats[i].x * graphic->window.height;
      if (wx == wy)
	match++;
    }
  if (match == 0)
    {
      ERR_RAISE(EC_LOADER_GFX_RATIO, 
		graphic->window.width,
		graphic->window.height);
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Fetch data concerning window (title, resolution, ...)
 */

static __inline int
graphic_parser_fetch_window(graphic_t *graphic, ini_section_t *section)
{
  char			*entry;

  if (graphic == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if (graphic_parser_fetch_winsize(graphic, section) == ERROR)
    return (ERROR);
  if (graphic_parser_check_winsize(graphic) == ERROR)
    return (ERROR);
  if ((entry = 
       ini_retrieve_entry_from_section(section, CLIENT_NAME_VAL)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, CLIENT_NAME_VAL, section->name);
      return (ERROR);
    }
  if ((graphic->window.title = strdup(entry)) == NULL)
    {
      ERR_RAISE(EC_SYS_STRDUP, strerror(errno)); /* assuming errno is set */
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's fetch max_fps value
 */

static __inline int
graphic_parser_fetch_gfx(client_t *client, graphic_t *graphic, 
			 ini_section_t *section)
{
  char			*value;
  int			fps;

  if (client == NULL || graphic == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((value = ini_retrieve_entry_from_section(section, CLIENT_MAX_FPS)) 
      == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, CLIENT_MAX_FPS, section->name);
      return (ERROR);
    }
  fps = atoi(value);
  if (fps <= 0)
    {
      ERR_RAISE(EC_LOADER_GFX_MAXFPS, fps);
      return (ERROR);
    }
  client->time.max_fps = fps;
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * let's fetch data from settings.ini (section graphic) to add
 * some informations into graphic's structure
 */

static __inline int
graphic_parser_fetch(client_t *client, graphic_t *graphic, 
		     ini_section_t *section)
{
  if (graphic == NULL || section == NULL || client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic_parser_fetch_window(graphic, section) == ERROR)
    return (ERROR);
  if (graphic_parser_fetch_gfx(client, graphic, section) == ERROR)
    return (ERROR);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialization of graphic's module
 * Allocates graphic structure and initialize its content
 */

void *
graphic_parser(client_t *client, ini_section_t *section)
{
  graphic_t		*graphic;

  if (client == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (NULL);
    }
  if ((graphic = malloc(sizeof(*graphic))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (NULL);
    }
  memset(graphic, 0, sizeof(*graphic));
  if (graphic_parser_fetch(client, graphic, section) == ERROR)
    {
      free(graphic);
      return (NULL);
    }
  client->graphic = graphic;
  return (graphic);
}
