/*
** graphic_2d.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 19:48:00 2009 sebastien rannou
** Last update Wed Jul 29 14:05:25 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "SDL_console.h"
#include "coor.h"
#include "font.h"
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

#define		FPSBOX_STRING	"%d FPS"

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
  graphic_text_to_surface(graphic->opengl.screen2d, &graphic->fpsbox.font,
			  FPSBOX_STRING, client->time.current_fps);
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
 * Let's draw the console :)
 */

static __inline int
graphic_2d_draw_console(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      threads_leave(client);
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  CON_DrawConsole(graphic->console);
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
  graphic_2d_draw_fpsbox(client, graphic);
  graphic_2d_draw_console(client, graphic);
  if (graphic_surface_to_gl(graphic->opengl.screen2d, 
			    &graphic->opengl.screen2d_id) == ERROR)
    {
      ERR_RAISE(EC_GL_CONVERT_TEX);
      return (ERROR);
    }
  graphic_2d_draw_screen(graphic, graphic->opengl.screen2d_id);
  return (SUCCESS);
}
