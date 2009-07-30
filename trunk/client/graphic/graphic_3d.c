/*
** graphic_3d.c for graoom in /home/rannou_s/Work/graoom/client
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 29 13:20:13 2009 sebastien rannou
** Last update Thu Jul 30 12:36:07 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "coor.h"
#include "shortcuts.h"
#include "lists.h"
#include "font.h"
#include "errors.h"
#include "client.h"
#include "graphic.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * Let's draw the world
 */

static __inline int
graphic_draw_world(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  /* Temporary code to test the camera */
  {
    GLUquadric* params = gluNewQuadric();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    gluQuadricTexture(params,GL_TRUE);
    gluSphere(params,1,20,20);
    gluDeleteQuadric(params);
  }
  /* /Temporary code to test the camera */
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's draw that trackball camera (simpler than freefly)
 */

static __inline int
graphic_draw_camera(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(graphic->window.fov, (double) WX / WY, 1, 1000);
  gluLookAt(graphic->camera.distance, 0, 0, 0, 0, 0, 0, 1, 0);
  /* Let's rotate the hole scene */
  glRotated(CR->y, 0, 1, 0);
  glRotated(CR->z, 0, 0, 1);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Main entry of 3d calculs
 * In order of calls:
 * -> draws the world
 * -> draws the characters
 * -> puts the camera
 */

int
graphic_3d_draw(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  graphic_draw_world(client, graphic);
  graphic_draw_camera(client, graphic);
  return (SUCCESS);
}
