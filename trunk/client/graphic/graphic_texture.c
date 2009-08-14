/*
** graphic_texture.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 19:55:08 2009 sebastien rannou
** Last update Wed Aug  5 02:31:49 2009 
*/

#ifndef	_BSD_SOURCE	/* strdup() */
#define	_BSD_SOURCE
#endif

#include <SDL/SDL_image.h>
#include <GL/gl.h>

#include "coor.h"
#include "shortcuts.h"
#include "lists.h"
#include "ini.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define		TEXTURES_INI_FILE	"internals/texture.ini"
#define		INI_PATH		"path"

typedef struct	internal_texture_s
{
  char		*name;
  SDL_Surface	*surface;
  GLuint	id;
}		internal_texture_t;

list_t *
global_textures;

/**!
 * @author	rannou_s
 * Let's load an image
 */

SDL_Surface *
graphic_load_image(char *path)
{
  SDL_Surface		*image;

  if (path == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (NULL);
    }
  if ((image = IMG_Load(path)) == NULL)
    {
      ERR_RAISE(EC_SDL_LOAD_IMG, path, SDL_GetError());
      return (NULL);
    }
  return (image);
}
/**!
 * @author	rannou_s
 * Bind the converted surface to the glTexture, create it if it
 * doesn't exists yet.
 */

static  int
graphic_surface_to_gl_create(SDL_Surface *converted, GLuint *textid)
{
  if (converted == NULL || textid == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if (*textid == 0)
    {
      glGenTextures(1, textid);
    }
  glBindTexture(GL_TEXTURE_2D, *textid);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D,
	       0,
	       GL_RGBA,
	       converted->w, converted->h, 0,
	       GL_RGBA,
	       GL_UNSIGNED_BYTE,
	       converted->pixels);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's convert an SDL_Image to an opengl one
 * When the texture doesn't exists, let's create it
 */

#define	IS_END	(SDL_BYTEORDER == SDL_BIG_ENDIAN)

int
graphic_surface_to_gl(SDL_Surface *surface, GLuint *texture_id)
{
  SDL_Surface		*tmp;
  SDL_PixelFormat	format;
  int			result;

  if (surface == NULL || texture_id == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  memset(&format, 0, sizeof(format));
  format = *surface->format;
  format.BytesPerPixel = 4;
  format.Rmask = IS_END ? 0xff000000 : 0x000000ff;
  format.Gmask = IS_END ? 0x00ff0000 : 0x0000ff00;
  format.Rmask = IS_END ? 0x0000ff00 : 0x00ff0000;
  format.Amask = IS_END ? 0x000000ff : 0xff000000;
  if ((tmp = SDL_ConvertSurface(surface, &format, SDL_SWSURFACE)) == NULL)
    {
      ERR_RAISE(EC_SDL_CREATE_SURFACE, SDL_GetError());
      return (ERROR);
    }
  result = graphic_surface_to_gl_create(tmp, texture_id);
  SDL_FreeSurface(tmp);
  return (result);
}

/**!
 * @author	rannou_s
 * Let's destroy an openGL texture
 */

void
graphic_destroy_gl_texture(GLuint id)
{
  glDeleteTextures(1, &id);
}

/**!
 * @author	rannou_s
 * Let's destroy an internal texture
 */

void
graphic_clean_texture(void *ptr)
{
  internal_texture_t		*texture = ptr;

  if (texture != NULL)
    {
      graphic_destroy_gl_texture(texture->id);
      SDL_FreeSurface(texture->surface);
      free(texture->name);
      free(texture);
    }
}

/**!
 * @author	rannou_s
 * Let's create a new texture, load it in SDL + OpenGL
 * and push it to the global list
 */

int
graphic_load_texture(char *path, char *name)
{
  internal_texture_t	*new;
  SDL_Surface		*image;

  if (path == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  image = graphic_load_image(path);
  if (image == NULL)
    {
      return (ERROR);
    }
  if ((new = malloc(sizeof(*new))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      graphic_clean_texture(new);
      return (ERROR);
    }
  memset(new, 0, sizeof(*new));
  new->surface = image;
  if (graphic_surface_to_gl(new->surface, &new->id) == ERROR)
    {
      graphic_clean_texture(new);
      return (ERROR);
    }
  if ((new->name = strdup(name)) == NULL)
    {
      graphic_clean_texture(new);
      ERR_RAISE(EC_SYS_STRDUP, strerror(errno)); /* assuming errno is set */
      return (ERROR);
    }
  if (list_push(&global_textures, new) == ERROR)
    {
      graphic_clean_texture(new);
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's fetch texture's properties
 */

static  int
graphic_load_texture_create(ini_t *config, ini_section_t *section)
{
  char			*path;

  if (config == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  path = ini_retrieve_entry_from_section(section, INI_PATH);
  if (path == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, INI_PATH, config->name);
      return (ERROR);
    }
  return (graphic_load_texture(path, section->name));
}

/**!
 * @author	rannou_s
 *  Main entry of the loader for textures
 */

int
graphic_load_textures(void)
{
  ini_t		*config;
  list_t	*cur;
  
  LOG(GRAPHIC_LOADING_TEXTURES);
  if ((config = ini_parse_file(TEXTURES_INI_FILE)) == NULL)
    {
      ERR_RAISE(EC_INI_FILE, TEXTURES_INI_FILE);
      return (ERROR);
    }
  for (cur = config->sections_is; cur != NULL; cur = cur->li_next)
    {
      if (cur->data != NULL)
	{
	  if (graphic_load_texture_create(config, cur->data) == ERROR)
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
 * And finnaly, the cleaner that cleans up each texture
 */

int
graphic_clean_textures(void)
{
  return (list_free(&global_textures, &graphic_clean_texture));
}
