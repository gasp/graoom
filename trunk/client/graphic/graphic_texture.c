/*
** graphic_texture.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 19:55:08 2009 sebastien rannou
** Last update Fri Jul 24 00:19:09 2009 sebastien rannou
*/

#include <SDL/SDL_image.h>
#include <GL/gl.h>

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
 * Let's convert an SDL_Image to an opengl one
 * @todo	handle BIG_ENDIAN/LITTLE_ENDIAN by reverting GL_RGBA flag
 */

GLuint
graphic_surface_to_gl(SDL_Surface *surface)
{
  GLuint			texture;
  
  if (surface == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w, 
	       surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
  return (texture);
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
