/*
** graphic_2d.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 19:48:00 2009 sebastien rannou
** Last update Fri Jul 24 00:14:28 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "lists.h"
#include "errors.h"
#include "client.h"
#include "graphic.h"
#include "shortcuts.h"
#include "threads.h"
#include "texture.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * Kind of SDL blit on screen equivalent:
 * we blit the screen2d surface on a square surface that
 * simulates a screen.
 * This function is called on frame generation.
 *
 * This system allows to use SDL as if we were in a SDL context,
 * just blitting everything on a screen without having to worry
 * about anything else.
 */

int
graphic_2d_draw(client_t *client, graphic_t *graphic)
{
  GLint			texture;

  if (client == NULL || graphic == NULL)
    {
      threads_leave(client);
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((texture = graphic_surface_to_gl(graphic->opengl.screen2d)) == ERROR)
    {
      ERR_RAISE(EC_GL_CONVERT_TEX);
      return (ERROR);
    }
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  {
    glTexCoord2d(0, 0);
    glVertex2f(0, 0);
    glTexCoord2d(1, 0);
    glVertex2f(WX, 0);
    glTexCoord2d(1, 1);
    glVertex2f(WX, WY);
    glTexCoord2d(0, 1);
    glVertex2f(0, WY);
  }
  glEnd();
  graphic_destroy_gl_texture(texture);
  return (SUCCESS);
}
