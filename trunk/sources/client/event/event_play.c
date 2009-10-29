/*
** event_play.c for battletrantor in /home/rannou_s/Work/graoom/client
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 29 21:06:06 2009 sebastien rannou
** Last update Fri Oct  2 12:49:54 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "coor.h"
#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "event.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"
#include "font.h"
#include "graphic.h"
#include "vector.h"

/**!
 * @author	rannou_s
 * These functions defines ingame actions
 */

/**!
 * @author	rannou_s
 * Let's straff on the left
 */

static void
event_move_left_freelook(graphic_t *graphic)
{
  CP->x += CLAT->x * CAMSPEED;
  CP->y += CLAT->y * CAMSPEED;
  CP->z += CLAT->z * CAMSPEED;  
}

int
event_move_left(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  event_move_left_freelook(client->graphic);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's straff on the right
 */

static void
event_move_right_freelook(graphic_t *graphic)
{
  CP->x -= CLAT->x * CAMSPEED;
  CP->y -= CLAT->y * CAMSPEED;
  CP->z -= CLAT->z * CAMSPEED;  
}

int
event_move_right(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  event_move_right_freelook(client->graphic);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's move forward
 */

static void
event_move_forward_freelook(graphic_t *graphic)
{
  CP->x += CDIR->x * CAMSPEED;
  CP->y += CDIR->y * CAMSPEED;
  CP->z += CDIR->z * CAMSPEED;  
}

int
event_move_forward(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  event_move_forward_freelook(client->graphic);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's move backward
 */

static void
event_move_back_freelook(graphic_t *graphic)
{
  CP->x -= CDIR->x * CAMSPEED;
  CP->y -= CDIR->y * CAMSPEED;
  CP->z -= CDIR->z * CAMSPEED;  
}

int
event_move_back(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  event_move_back_freelook(client->graphic);
  return (SUCCESS);
}

/**!
 * Called to move in freelook mode
 */

static void
event_mouse_move_freelook(graphic_t *graphic)
{
  int		x, y;
  d3_t		vert;

  SDL_GetRelativeMouseState(&x, &y);
  CTHETA = CTHETA - x * CAMSPEEDROT;
  CPHI = MIN(MAX(CPHI - y * CAMSPEEDROT, -89), 89);
  vector_polarize(CDIR, RADIAN(CTHETA), RADIAN(CPHI));
  vert.x = 0;
  vert.y = 0;
  vert.z = 1;
  vector_crossproduct(CLAT, &vert, CDIR);
  vector_normalize(CLAT);
}

int
event_mouse_move(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  event_mouse_move_freelook(client->graphic);
  return (SUCCESS);
}
