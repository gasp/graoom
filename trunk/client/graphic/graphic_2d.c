/*
** graphic_2d.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 19:48:00 2009 sebastien rannou
** Last update Sun Jul 26 13:05:20 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "coor.h"
#include "lists.h"
#include "errors.h"
#include "client.h"
#include "graphic.h"
#include "shortcuts.h"
#include "threads.h"
#include "textures.h"
#include "font.h"
#include "log.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * Displays some informations about the current state (FPS, ...)
 * @todo	add a flag in settings.ini to activate/desactive this function
 */

int
graphic_2d_draw_fpsbox(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      threads_leave(client);
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (graphic->fpsbox.state == OFF)
    {
      return (SUCCESS);
    }
  
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's draw the screen and put the converted SDL_Surface on it
 * We reload the matrice to have a clean workspace, we use glOrtho
 * so as to have something like :
 *
 * (1,0) ***************************************** (1,1)
 *       *                                       *
 *       *                                       *
 *       *                                       *
 *       *                                       *
 *       *                                       *
 *       *                                       *
 *       *                                       *
 *       *                                       *
 *       *                                       *
 * (0,0) ***************************************** (0,1)
 *
 * It's a quick way to easily bind a texture on a screen.
 */

static __inline int
graphic_2d_draw_screen(graphic_t *graphic, GLuint texture)
{
  if (graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
  graphic_set_2d(graphic);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBegin(GL_QUADS);
  {
    glTexCoord2d(0.0, 1.0);
    glVertex2d(0, WY);

    glTexCoord2d(1.0, 1.0);
    glVertex2d(WX, WY);

    glTexCoord2d(1.0, 0.0);
    glVertex2d(WX, 0);

    glTexCoord2d(0.0, 0.0);
    glVertex2d(0, 0);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  return (SUCCESS);
}

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
  if (client == NULL || graphic == NULL)
    {
      threads_leave(client);
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  SDL_FillRect(graphic->opengl.screen2d, NULL, 
	       SDL_MapRGB(graphic->opengl.screen2d->format, 255, 0, 0));
  graphic_2d_draw_fpsbox(client, graphic);
  if (graphic_surface_to_gl(graphic->opengl.screen2d, 
			    &graphic->opengl.screen2d_id) == ERROR)
    {
      ERR_RAISE(EC_GL_CONVERT_TEX);
      return (ERROR);
    }
  graphic_2d_draw_screen(graphic, graphic->opengl.screen2d_id);
  return (SUCCESS);
}
