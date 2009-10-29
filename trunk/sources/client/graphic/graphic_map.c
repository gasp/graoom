/*
** map_init.c for BattleTrantor in /home/rannou_s/work/c/BattleTrantor/sources/client/graphic/map
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Oct  2 12:58:47 2009 sebastien rannou
** Last update Wed Oct  7 09:23:06 2009 sebastien rannou
*/

/**!
 * Initialize maps's list
 */

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "coor.h"
#include "font.h"
#include "lists.h"
#include "client.h"
#include "tools.h"
#include "shortcuts.h"
#include "errors.h"
#include "graphic.h"
#include "log.h"
#include "log_client.h"
#include "vector.h"

#include <errno.h>

#include "mdl.h"
#include "graphic_model.h"

#define	MAP_BORDER_X			5
#define	MAP_BORDER_Y			5
#define	DEFAULT_MAP_X			10
#define	DEFAULT_MAP_Y			10
#define	DEFAULT_GROUND_TEXTURE_NAME	"ground"
#define	DEFAULT_HEIGHTMAP_TEXTURE_NAME	"heightmap"
#define	SKY_TEXTURE			"sky"

#define	MODEL_TOWER			"tower"
#define	TOWER_NUMBER			4

static GLuint		/* List's ID */
global_list = 0;

static int		/* Map size X */
global_map_size_x = DEFAULT_MAP_X;

static int		/* Map size Y */
global_map_size_y = DEFAULT_MAP_Y;

static double **	/* contains the heightmap */
global_heightmap = NULL;

static model_instance_t	/* contains data about towers */
global_towers[TOWER_NUMBER];

static GLUquadricObj *	/* contains the sky */
global_sky = NULL;

#define	MX		(global_map_size_x + 2 * MAP_BORDER_X)
#define	MY		(global_map_size_y + 2 * MAP_BORDER_Y)
#define TX		(Uint16) (((x * 100.0) / (MX + 2 * MAP_BORDER_X)) * (surface->w / 100.0))
#define TY		(Uint16) (((y * 100.0) / (MY + 2 * MAP_BORDER_Y)) * (surface->h / 100.0))

/**!
 * Top Left corner (inner)
 */

#define	CORN_IN_UP_LX	(MAP_BORDER_X / 2)
#define	CORN_IN_UP_LY	(MAP_BORDER_Y / 2)

/**!
 * Top Right corner (inner)
 */

#define	CORN_IN_UP_RX	(MAP_BORDER_X + global_map_size_x + (MAP_BORDER_X / 2))
#define	CORN_IN_UP_RY	(MAP_BORDER_X / 2)

/**!
 * Down Left corner (inner)
 */

#define	CORN_IN_DO_RX	(MAP_BORDER_X / 2)
#define	CORN_IN_DO_LY	(MAP_BORDER_Y + global_map_size_y + (MAP_BORDER_Y / 2))

/**!
 * Down Right corner (inner)
 */

#define	CORN_IN_DO_LX	(MAP_BORDER_X + global_map_size_x + (MAP_BORDER_X / 2))
#define	CORN_IN_DO_RY	(MAP_BORDER_Y + global_map_size_y + (MAP_BORDER_Y / 2))

#define H(v)		((double) (v * ((10.0 * ((MX + MY) / 2.0)))) / 20000.0)

/**!
 * Get the height from the heightmap array according to x / y
 * Returns 0 when out of range
 */

static double
map_get_height(int x, int y)
{
  if (global_heightmap != NULL)
    {
      if (x >= 0 && x < MX &&
	  y >= 0 && y < MY)
	{
	  return global_heightmap[x][y];
	}
    }
  return 0.0;
}

/**!
 * Set the heightmap according to the pixel value
 * Set a different level if we are in the border part of the map or not.
 * Set the level to 0 if we are in a 'vertice'
 */

static int
map_initialize_heightmap_setheight(SDL_Surface *surface, int x, int y)
{
  Uint32	pixel;
  Uint8		r[4];

  pixel = SDL_GetPixel32(surface, TX, TY);
  SDL_GetRGBA(pixel, surface->format, &r[0], &r[1], &r[2], &r[3]);
  if (x >= MAP_BORDER_X 
      && y >= MAP_BORDER_Y
      && x <= (MX - MAP_BORDER_X)
      && y <= (MY - MAP_BORDER_Y))
    {
      global_heightmap[x][y] = H(r[0]);
    }
  else
    {
      if (x == 0 || y == 0 || x == MX || y == MY)
	{
	  global_heightmap[x][y] = 0.0;
	}
      else
	{
	  global_heightmap[x][y] = H(r[0]) * 1.5 + 1.5;
	}
    }  
  return SUCCESS;
}

/**!
 * Allocates the heightmap and initialize it with 
 * content extracted from heightmap.jpg
 */

static int
map_initialize_heightmap(void)
{
  int		x, y;
  SDL_Surface *	surface = graphic_get_texture_sdl(DEFAULT_HEIGHTMAP_TEXTURE_NAME);

  if (surface == NULL)
    {
      return ERROR;
    }
  global_heightmap = malloc((MX + 1) * sizeof(*global_heightmap));
  if (global_heightmap == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return ERROR;
    }
  for (x = 0; x < MX; x++)
    {
      global_heightmap[x] = malloc((MY) * sizeof(**global_heightmap));
      if (global_heightmap[x] == NULL)
	{
	  ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
	  free(global_heightmap);
	  global_heightmap = NULL;
	  return ERROR;
	}
      for (y = 0; y < MY; y++)
	if (map_initialize_heightmap_setheight(surface, x, y))
	  return ERROR;
    }
  global_heightmap[x] = NULL;
  return SUCCESS;
}

/**!
 * The heightmap is composed of triangles, each grid is composed of
 * 2 triangles, this fonction draws one of these grids
 */

static void
map_draw_ground_left(int x, int y, double h)
{
  glBegin(GL_TRIANGLES);
  {
    glTexCoord2d(x, y);
    glVertex3d(x, y, h * map_get_height(x, y));

    glTexCoord2d(x + 1, y);
    glVertex3d(x + 1, y, h * map_get_height(x + 1, y));
    
    glTexCoord2d(x, y + 1);
    glVertex3d(x, y + 1, h * map_get_height(x, y + 1));
  }
  glEnd();
}

/**!
 * this fonction draws the others
 */

static void
map_draw_ground_right(int x, int y, double h)
{
  glBegin(GL_TRIANGLES);
  {
    glTexCoord2d(x + 1, y + 1);
    glVertex3d(x + 1, y + 1, h * map_get_height(x + 1, y + 1));
    
    glTexCoord2d(x + 1, y);
    glVertex3d(x + 1, y, h * map_get_height(x + 1, y));
    
    glTexCoord2d(x, y + 1);
    glVertex3d(x, y + 1, h * map_get_height(x, y + 1));
  }
  glEnd();
}

/**!
 * Let's initialize the ground
 * This part of the code only deals with the construction of the heightmap
 */

static int
map_initialize_ground(void)
{
  int		x, y;
  GLuint	ground_texture = graphic_get_texture(DEFAULT_GROUND_TEXTURE_NAME);

  if (ground_texture == (GLuint) ERROR)
    {
      return ERROR;
    }

  glEnable(GL_TEXTURE_2D);
  glColor3ub(255,255,255);
  glBindTexture(GL_TEXTURE_2D, ground_texture);

  for (x = 0; x < MX; x++)
    {
      for (y = 0; y < MY; y++)
	{
	  /**!
	   * We call it with homotheties as we need to get a kind of island 
	   * So 1.0 will be the playground part, -3.0 the roots of the island
	   */
	  map_draw_ground_left(x, y, 1.0);
	  map_draw_ground_right(x, y, 1.0);
	  map_draw_ground_left(x, y, -3.0);
	  map_draw_ground_right(x, y, -3.0);
	}
    }
  glDisable(GL_TEXTURE_2D);
  return SUCCESS;
}

/**!
 * Initialize towers
 */

#define	T1X	CORN_IN_UP_LX
#define	T1Y	CORN_IN_UP_LY

#define	T2X	CORN_IN_UP_RX
#define	T2Y	CORN_IN_UP_RY

#define	T3X	CORN_IN_DO_LX
#define	T3Y	CORN_IN_DO_LY

#define	T4X	CORN_IN_DO_RX
#define	T4Y	CORN_IN_DO_RY

static int
map_initialize_tower(void)
{
  mdl_model_t *		model = graphic_get_model(MODEL_TOWER);;
  int			i;

  if (NULL == model)
    {
      return ERROR;
    }
  glEnable(GL_TEXTURE_2D);
  VECTOR_SET(&global_towers[0].position, T1X, T1Y, map_get_height(T1X, T1Y) - 0.5);
  VECTOR_SET(&global_towers[1].position, T2X, T2Y, map_get_height(T2X, T2Y) - 0.5);
  VECTOR_SET(&global_towers[2].position, T3X, T3Y, map_get_height(T3X, T3Y) - 0.5);
  VECTOR_SET(&global_towers[3].position, T4X, T4Y, map_get_height(T4X, T4Y) - 0.5);
  for (i = 0; i < TOWER_NUMBER; i++)
    {
      global_towers[i].model = model;
      VECTOR_INIT(&global_towers[i].scale, 0.20);
      VECTOR_INIT(&global_towers[i].rotation, 0.0);
      graphic_draw_fixed_model(&global_towers[i]);
    }
  glDisable(GL_TEXTURE_2D);
  return SUCCESS;
}

/**!
 * Initialize the sky
 */

static int
map_initialize_sky(void)
{
  global_sky = gluNewQuadric();
  if (global_sky == NULL)
    {
      ERR_RAISE(EC_GL_NEW_QUAD);
      return ERROR;
    }
  glEnable(GL_TEXTURE_2D);
  {
    gluQuadricTexture(global_sky, GL_TRUE);
    gluQuadricOrientation(global_sky, GLU_INSIDE);
    gluQuadricDrawStyle(global_sky, GLU_LINE);
    glBindTexture(GL_TEXTURE_2D, graphic_get_texture(SKY_TEXTURE));
    gluSphere(global_sky, global_map_size_y * global_map_size_x, 10, 10);
  }
  glDisable(GL_TEXTURE_2D);
  return SUCCESS;
}

/**!
 * Intiialize opengl list for all the world
 */

static int
map_initialize_list(void)
{
  global_list = glGenLists(1);
  glNewList(global_list, GL_COMPILE);
  {
    if (map_initialize_ground() == ERROR)
      {
	return ERROR;
      }
    if (map_initialize_tower() == ERROR)
      {
	return ERROR;
      }
    if (map_initialize_sky() == ERROR)
      {
	return ERROR;
      }
  }
  glEndList();
  return SUCCESS;
}

/**!
 * Main entry of the initializer
 */

int
map_initialize(void)
{
  LOG(MAP_LOADING);
  if (map_initialize_heightmap() == ERROR)
    {
      return ERROR;
    }
  if (map_initialize_list() == ERROR)
    {
      return ERROR;
    }
  return SUCCESS;
}

/**!
 * Draws the map
 */

void
map_draw(void)
{
  glCallList(global_list);
}

/**!
 * Let's clean up what was loaded
 * We reset to NULL/default in order to be able to load
 * a new map after
 */

int
map_destruct(void)
{
  int			x;

  if (global_heightmap != NULL)
    {
      for (x = 0; x < MX; x++)
	{
	  free(global_heightmap[x]);
	}
      free(global_heightmap[x]);
      free(global_heightmap);
      global_heightmap = NULL;
    }
  glDeleteLists(global_list, 1);
  global_list = 0;
  if (global_sky != NULL)
    {
      gluDeleteQuadric(global_sky);
      global_sky = NULL;
    }
  return SUCCESS;
}
