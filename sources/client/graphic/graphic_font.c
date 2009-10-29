/*
** graphic_font.c for battletrantor in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 20:49:35 2009 sebastien rannou
** Last update Thu Oct  1 17:38:20 2009 sebastien rannou
*/

/**!
 * @author	rannou_s
 * This part of the graphic module works independantly
 * It can easily be integrated into other projects
 */

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE	/* strdup() on linux */
#endif

#include <SDL/SDL_ttf.h>

#include "coor.h"
#include "lists.h"
#include "shortcuts.h"
#include "ini.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"
#include "font.h"

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#define	FONT_INI_FILE	"internals/font.ini"
#define	INI_SEC_SIZE	"size"
#define	INI_SEC_PATH	"path"

typedef struct		font_internal_s	/* font's structure */
{
  char			*name;		/* font's name (unique) */
  char			*path;		/* font's path */
  TTF_Font		*font;		/* font itself */
  int			size;		/* font's size */
  int			id;		/* font's id */
}			font_internal_t;

static list_t *	/* list of loaded fonts */
global_fonts = NULL;

/**!
 * @author	rannou_s
 * Close a font, and unallocates memory
 * Not a static  because called on the lib (free_list)
 */

void
graphic_clean_font(void *data)
{
  font_internal_t	*font = (font_internal_t *) data;

  if (font == NULL)
    return;
  free(font->name);
  free(font->path);
  TTF_CloseFont(font->font);
  free(font);
}

/**!
 * @author	rannou_s
 * Can seem to be long but only affect values to new_elem
 * from section's content, also check if the size is correct.
 */

static  int
graphic_load_ttf_create_init(ini_t *ini, ini_section_t *section, 
			     font_internal_t *new_elem)
{
  char			*value;

  if (section == NULL || new_elem == NULL || ini == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if ((value = ini_retrieve_entry_from_section(section, INI_SEC_SIZE)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, section->name, INI_SEC_SIZE);
      return (ERROR);
    }
  if ((new_elem->size = atoi(value)) < 0)
    {
      ERR_RAISE(EC_SDL_TTF_INVALID_SIZE, new_elem->size, 
		ini->name, section->name);
      return (ERROR);
    }
  if ((value = ini_retrieve_entry_from_section(section, INI_SEC_PATH)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, section->name, INI_SEC_PATH);
      return (ERROR);
    }
  if ((new_elem->path = strdup(value)) == NULL)
    {
      ERR_RAISE(EC_SYS_STRDUP, strerror(errno)); /* assuming errno is set */
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Load a font with TTF_OpenFont, and push it to the list
 */

static  int
graphic_load_ttf_create_load(ini_t *ini, ini_section_t *section,
			     font_internal_t *font)
{
  if (ini == NULL || section == NULL || font == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic_load_ttf_create_init(ini, section, font) == ERROR)
    {
      return (ERROR);
    }
  if ((font->font = TTF_OpenFont(font->path, font->size)) == NULL)
    {
      ERR_RAISE(EC_SDL_TTF_OPEN, font->path, TTF_GetError());
      return (ERROR);
    }
  if (list_push(&global_fonts, font) == ERROR)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  font->id = global_fonts->li_info->nb_elements;
  LOG(GRAPHIC_LOADING_FONT_OK, font->path);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Load's a font from a section entry
 * Intilialize font's parameters, create a new entry.
 */

static  int
graphic_load_ttf_create(ini_t *ini, ini_section_t *section)
{
  font_internal_t		*new_elem;

  if (ini == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((new_elem = malloc(sizeof(*new_elem))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  memset(new_elem, 0, sizeof(*new_elem));
  if ((new_elem->name = strdup(section->name)) == NULL)
    {
      free(new_elem->path);
      ERR_RAISE(EC_SYS_STRDUP, strerror(errno)); /* assuming errno is set */
      return (ERROR);
    }
  if (graphic_load_ttf_create_load(ini, section, new_elem) == ERROR)
    {
      graphic_clean_font(new_elem);
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's load fonts from FONT_INI_FILE
 */

int
graphic_load_ttf(void)
{
  ini_t		*config;
  list_t	*cur;

  LOG(GRAPHIC_LOADING_FONT);
  if ((config = ini_parse_file(FONT_INI_FILE)) == NULL)
    {
      ERR_RAISE(EC_INI_FILE, FONT_INI_FILE);
      return (ERROR);
    }
  for (cur = config->sections_is; cur != NULL; cur = cur->li_next)
    {
      if (cur->data != NULL)
	{
	  if (graphic_load_ttf_create(config, cur->data) == ERROR)
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
 * Returns an ID from a font name
 */

int
graphic_font_getid(char *name)
{
  list_t		*cur;
  font_internal_t	*font;

  for (cur = global_fonts; cur != NULL; cur = cur->li_next)
    {
      font = (font_internal_t *) cur->data;
      if (font != NULL)
	{
	  if (strcmp(font->name, name) == 0)
	    {
	      return (font->id);
	    }
	}
    }
  ERR_RAISE(EC_SDL_TTF_GET, name);
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Returns a font according to an id
 * If nothing was found, the first loaded font is returned,
 * if no font was loaded, we return ERROR and raise an error
 */

TTF_Font *
graphic_font_retrieve(int id)
{
  font_internal_t	*font;
  list_t		*cur;
  TTF_Font		*default_font = NULL;

  for (cur = global_fonts; cur != NULL; cur = cur->li_next)
    {
      font = (font_internal_t *) cur->data;
      if (font->id == id)
	{
	  return (font->font);
	}
      if (default_font == NULL)
	{
	  default_font = font->font;
	}
    }
  if (default_font == NULL)
    {
      ERR_RAISE(EC_SDL_TTF_NOT_FOUND, id);
      return (NULL);
    }
  return (default_font);
}

/**!
 * @author	rannou_s
 * Let's clean loaded fonts (wow, what an amazing function)
 */

int
graphic_clean_ttf(void)
{
  return (list_free(&global_fonts, &graphic_clean_font));
}

/**!
 * @author	rannou_s
 * Let's draw a string on a surface with some varargs
 * We use a temporary surface from TTF_Font (would be great to blit directly on
 * our Surface, but haven't find anything that does it)
 */

#define			PRINT_BUFF_SIZE	512

int
graphic_text_to_surface(SDL_Surface *surface, font_t *font, char *fmt, ...)
{
  SDL_Rect		rect;
  SDL_Surface		*tmp;
  TTF_Font		*ttf_font;
  char			buffer[PRINT_BUFF_SIZE];
  va_list		ap;

  if (surface == NULL || font == NULL || fmt == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  va_start(ap, fmt);
  vsnprintf(buffer, PRINT_BUFF_SIZE, fmt, ap);
  va_end(ap);
  if ((ttf_font = graphic_font_retrieve(font->font_id)) == NULL)
    return (ERROR);
  if ((tmp = TTF_RenderText_Blended(ttf_font, buffer, *font->color)) == NULL)
    {
      ERR_RAISE(EC_SDL_TTF_RENDER, TTF_GetError());
      return (ERROR);
    }
  rect.x = font->pos.x;
  rect.y = font->pos.y;
  SDL_BlitSurface(tmp, NULL, surface, &rect);
  SDL_FreeSurface(tmp);
  return (SUCCESS);
}
