/*
** graphic_3d.c for graoom in /home/rannou_s/Work/graoom/client
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 29 13:20:13 2009 sebastien rannou
** Last update Fri Aug 14 22:11:34 2009 
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

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOV, (double) WX / WY, 1, 1000);
  gluLookAt(1.5, 1.5, 5, 0, 0, 0, 0, 1, 0);

  glBegin(GL_QUADS);
  {
    glColor3ub(255,0,0);
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);

    glColor3ub(0,255,0);
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);

    /* Let's restore colors */
    glColor3ub(255, 255, 255);

  }
  glEnd();

  return (SUCCESS);
}
