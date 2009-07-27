/*
** graphic_tools.c for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 26 11:42:06 2009 sebastien rannou
** Last update Mon Jul 27 13:11:26 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "coor.h"
#include "font.h"
#include "lists.h"
#include "shortcuts.h"
#include "client.h"
#include "graphic.h"
#include "errors.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * Let's switch to 2D mode
 */

int
graphic_set_2d(graphic_t *graphic)
{
  if (graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WX, WY, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's switch to 3D mode
 */

int
graphic_set_3d(graphic_t *graphic)
{
  if (graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);      
    }
  return (SUCCESS);
}
