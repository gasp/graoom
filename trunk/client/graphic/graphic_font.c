/*
** graphic_font.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 20:49:35 2009 sebastien rannou
** Last update Wed Jul 22 00:49:28 2009 sebastien rannou
*/

/**!
 * @author	rannou_s
 * This part of the graphic module works independantly
 * It can easily be integrated into other projects
 */

#include "lists.h"
#include "shortcuts.h"
#include "ini.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE	/* strdup() on linux */
#endif

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <SDL/SDL_ttf.h>

#define	FONT_INI_FILE	"internals/font.ini"
#define	INI_SEC_SIZE	"size"
#define	INI_SEC_PATH	"path"

typedef struct		font_s		/* font's structure */
{
  char			*name;		/* font's name (unique) */
  char			*path;
  TTF_Font		*font;		/* font itself */
  int			size;		/* font's size */
}			font_t;

static list_t *	/* list of loaded fonts */
global_fonts = NULL;

/**!
 * @author	rannou_s
 * Close a font, and unallocates memory
 * Not a static __inline because called on the lib (free_list)
 */

void
graphic_clean_font(void *data)
{
  font_t	*font = (font_t *) data;

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

static __inline int
graphic_load_ttf_create_init(ini_t *ini, ini_section_t *section, 
			     font_t *new_elem)
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

static __inline int
graphic_load_ttf_create_load(ini_t *ini, ini_section_t *section,
			     font_t *font)
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
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Load's a font from a section entry
 * Intilialize font's parameters, create a new entry.
 */

static __inline int
graphic_load_ttf_create(ini_t *ini, ini_section_t *section)
{
  font_t		*new_elem;

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
	  graphic_load_ttf_create(config, cur->data);
	}
    }
  ini_free_main(config);
  return (SUCCESS);
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
