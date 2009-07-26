/*
** graphic_color.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 26 14:40:55 2009 sebastien rannou
** Last update Sun Jul 26 18:07:36 2009 sebastien rannou
*/

#ifndef		_BSD_SOURCE
#define		_BSD_SOURCE	/* strdup() on linux */
#endif

#include <SDL/SDL.h>

#include "lists.h"
#include "ini.h"
#include "coor.h"
#include "shortcuts.h"
#include "errors.h"
#include "font.h"
#include "log.h"
#include "log_client.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define	COLORS_INI_FILE	"internals/colors.ini"
#define INI_COLOR_RED	"red"
#define INI_COLOR_BLUE	"blue"
#define INI_COLOR_GREEN	"green"

typedef struct		color_internal_s
{
  SDL_Color		color;
  char			*name;
}			color_internal_t;

static list_t *	/* list of loaded colors */
global_colors = NULL;

/**!
 * @author	rannou_s
 * Let's free a color
 */

void
graphic_free_color(void *data)
{
  color_internal_t *color = data;

  if (color)
    if (color->name)
      free(color->name);
  free(color);
}

/**!
 * @author	rannou_s
 * retrieves a color, trim it if it's out of range
 */

static __inline int
graphic_load_colors_create_getval(ini_section_t *section, char *request)
{
  int			result;
  char			*value;

  value = ini_retrieve_entry_from_section(section, request);
  if (value == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, request, COLORS_INI_FILE);
      return (ERROR);
    }
  result = atoi(value);
  /* Would be great to raise an error here ? */
  if (result < 0)
    result = 0;
  else if (result > 255)
    result = 255;
  return (result);
}

/**!
 * @author		rannou_s
 * Creates a new color, check it and push it to global_colors
 */

static __inline int
graphic_load_colors_create(ini_section_t *section)
{
  color_internal_t		*new_color;
  int				r, g, b;

  if (section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  r = graphic_load_colors_create_getval(section, INI_COLOR_RED);
  g = graphic_load_colors_create_getval(section, INI_COLOR_GREEN);
  b = graphic_load_colors_create_getval(section, INI_COLOR_BLUE);
  if (r == ERROR || g == ERROR || b == ERROR)
    return (ERROR);
  if ((new_color = malloc(sizeof(*new_color))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  memset(new_color, 0, sizeof(new_color));
  if ((new_color->name = strdup(section->name)) == NULL)
    {
      free(new_color);
      ERR_RAISE(EC_SYS_STRDUP, strerror(errno)); /* assuming errno is set */
      return (ERROR);
    }
  new_color->color.r = r;
  new_color->color.g = g;
  new_color->color.b = b;
  if (list_push(&global_colors, new_color) == ERROR)
    {
      graphic_free_color(new_color);
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's load colors from COLORS_INI_FILE
 * Each section in ini file describes a new color which will take section's name
 * as color's name:
 *	[red]
 *	red = 255
 *	blue = 0
 *	green = 0
 * will create a color named red
 */

int
graphic_load_colors(void)
{
  ini_t		*config;
  list_t	*cur;

  LOG(GRAPHIC_LOADING_COLORS);
  if ((config = ini_parse_file(COLORS_INI_FILE)) == NULL)
    {
      ERR_RAISE(EC_INI_FILE, COLORS_INI_FILE);
      return (ERROR);
    }
  for (cur = config->sections_is; cur != NULL; cur = cur->li_next)
    {
      if (cur->data != NULL)
	{
	  if (graphic_load_colors_create(cur->data) == ERROR)
	    {
	      return (ERROR);
	    }
	}
    }
  ini_free_main(config);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's free what was allocated by this file
 */

void
graphic_clean_colors(void)
{
  list_free(&global_colors, &graphic_free_color);
}

/**!
 * @author	rannou_s
 * Let's give a way to retrieve colors
 */

SDL_Color *
graphic_colors_get(char *name)
{
  list_t		*cur;
  color_internal_t	*color;

  for (cur = global_colors; cur != NULL; cur = cur->li_next)
    {
      color = (color_internal_t *) cur->data;
      if (color != NULL)
	{
	  if (strcasecmp(color->name, name) == 0)
	    {
	      return (&color->color);
	    }
	}
    }
  return (NULL);
}
