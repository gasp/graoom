/*
** graphic_3d.c for battletrantor in /home/rannou_s/Work/graoom/client
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 29 13:20:13 2009 sebastien rannou
** Last update Mon Oct  5 12:53:31 2009 sebastien rannou
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
#include "map.h"

#include <stdlib.h>

#include "mdl.h"

void		RenderFrameItp (int n, float interp, mdl_model_t *mdl);
mdl_model_t *	graphic_get_model(void);

/**!
 * @author	rannou_s
 * Main entry of 3d calculs
 * In order of calls:
 * -> draws the world
 * -> draws the characters
 * -> puts the camera
 */

#define	POVX	(CP->x + CDIR->x)
#define	POVY	(CP->y + CDIR->y)
#define	POVZ	(CP->z + CDIR->z)

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
  gluLookAt(CP->x, CP->y, CP->z, POVX, POVY, POVZ, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  map_draw();

  return (SUCCESS);
}
