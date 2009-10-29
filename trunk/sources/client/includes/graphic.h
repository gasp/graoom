/*
** graphic.h for battletrantor in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 12:35:08 2009 sebastien rannou
** Last update Fri Oct  2 15:13:30 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_GRAPHIC_H
#define	GRAOOM_C_GRAPHIC_H

/**!
 * @author	rannou_s
 * Some shortcuts
 */

#define	FOV		(graphic->window.fov)
#define	WX		(graphic->window.width)
#define	WY		(graphic->window.height)

/**!
 * Shortcuts for camera
 */

#define	CR		(&graphic->camera.rotation)
#define	CP		(&graphic->camera.position)
#define	CLAT		(&graphic->camera.vector_lat)
#define	CDIR		(&graphic->camera.vector_dir)
#define	CTHETA		(graphic->camera.theta)
#define	CPHI		(graphic->camera.phi)

#define	CAMSPEED	0.05
#define	CAMSPEEDROT	0.1

typedef struct		texture_s	/* texture SDL/OpenGL */
{
  SDL_Surface		*surface;	/* SDL  */
  GLuint		id;		/* Opengl's ID */
}			texture_t;

typedef struct		opengl_s	/* opengl data */
{
  SDL_Surface		*screen2d;	/* blitted each time on screen */
  GLuint		screen2d_id;	/* opengl's ID of screen2d */
}			opengl_t;

typedef struct		window_s	/* data concerning the window */
{
  int			width;		/* window's width */
  int			height;		/* window's height */
  int			fov;		/* opengl's fov */
  char			*title;		/* window's title */
  SDL_Surface		*screen;	/* screen's surface */
}			window_t;

typedef struct		fpsbox_s	/* box that displays informations */
{
  int			state;		/* on/off */
  font_t		font;		/* font to display */
}			fpsbox_t;

enum			CAMERA_MODE
  {
    CAM_FREELOOK_MODE,	/* default mode */
    CAM_INEYES_MODE
  };

typedef struct		camera_s	/* trackball camera */
{
  d3_t			position;	/* x,y,z */
  d3_t			rotation;	/* x,y,z */
  d3_t			vector_lat;	/* lateral vector */
  d3_t			vector_dir;	/* direction vector */
  double		theta;		/* used for freelook */
  double		phi;		/* same */
  int			mode;		/* freelook, ineyes, ...?! */
}			camera_t;

typedef struct		graphic_s	/* main structure for gfx module */
{
  opengl_t		opengl;		/* opengl related */
  list_t *		textures;	/* list of loaded textures */
  window_t		window;		/* window related */
  fpsbox_t		fpsbox;		/* fps box that display infos  */
  void			*console;	/* sdl_console's structure */
  camera_t		camera;		/* camera's structure */
}			graphic_t;

int
graphic_3d_draw(client_t *client, graphic_t *graphic);

int
graphic_2d_draw(client_t *client, graphic_t *graphic);

int
graphic_set_2d(graphic_t *graphic);

GLuint
graphic_get_texture(const char *name);

SDL_Surface *
graphic_get_texture_sdl(const char *name);

/**!
 * Returns the value of a pixel
 */

static __inline 
Uint32 SDL_GetPixel32(SDL_Surface *surface, Uint16 x, Uint16 y)
{
  Uint8 *p;

  if (surface)
    {
      p =  (Uint8*) surface->pixels + y * surface->pitch;
      p += x * ((Uint8) surface->format->BytesPerPixel);
    }
  /* Undefined behavior else */
  return ((Uint32) *p);
}

#endif /* GRAOOM_C_GRAPHIC_H */
