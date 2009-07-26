/*
** graphic_texture.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 19:55:08 2009 sebastien rannou
** Last update Sun Jul 26 12:26:13 2009 sebastien rannou
*/

#include <SDL/SDL_image.h>
#include <GL/gl.h>

#include "coor.h"
#include "shortcuts.h"
#include "lists.h"
#include "errors.h"

#include <stdlib.h>

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
 * quick shortcut to get the first number power of two just after input
 */

static __inline int
powt(int input)
{
  int value;

  for (value = 1; value < input; value <<= 1)
    ;
  return (value);
}

/**!
 * @author	rannou_s
 * Bind the converted surface to the glTexture, create it if it
 * doesn't exists yet.
 */

static __inline int
graphic_surface_to_gl_create(SDL_Surface *converted, GLuint *textid)
{
  if (converted == NULL || textid == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if (*textid == 0)
    glGenTextures(1, textid);
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
 * Function taken from the excellent:
 * http://twomix.devolution.com/pipermail/sdl/2002-September/049078.html
 */

#if		SDL_BYTEORDER == SDL_LIL_ENDIAN
# define	CMASK	0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
#else
#define
# define	CMASK	0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
#endif

int
graphic_surface_to_gl(SDL_Surface *surface, GLuint *texture_id)
{
  SDL_Surface		*new;
  SDL_Rect		area;
  Uint32		saved_flags;
  Uint8			saved_alpha;
  int			result;

  if (surface == NULL || texture_id == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if ((new = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, 
				  surface->h, 32, CMASK)) == NULL)
    {
      ERR_RAISE(EC_SDL_CREATE_SURFACE, SDL_GetError());
      return (ERROR);
    }
  saved_flags = surface->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
  saved_alpha = surface->format->alpha;
  if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
    SDL_SetAlpha(surface, 0, 0);
  memset(&area, 0, sizeof(area));
  area.w = surface->w;
  area.h = surface->h;
  SDL_BlitSurface(surface, &area, new, &area);
  if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
    SDL_SetAlpha(surface, saved_flags, saved_alpha);
  result = graphic_surface_to_gl_create(new, texture_id);
  SDL_FreeSurface(new);
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
