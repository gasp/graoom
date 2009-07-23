/*
** graphic.h for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 12:35:08 2009 sebastien rannou
** Last update Fri Jul 24 00:15:15 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_GRAPHIC_H
#define	GRAOOM_C_GRAPHIC_H

/**!
 * @author	rannou_s
 * Some shortcuts
 */

#define	WX		(graphic->window.width)
#define	WY		(graphic->window.height)

typedef struct		texture_s	/* texture SDL/OpenGL */
{
  SDL_Surface		*surface;	/* SDL  */
  GLuint		id;		/* Opengl's ID */
}			texture_t;

typedef struct		opengl_s	/* opengl data */
{
  SDL_Surface		*screen2d;	/* blitted each time on screen */
}			opengl_t;

typedef struct		window_s	/* data concerning the window */
{
  int			width;		/* window's width */
  int			height;		/* window's height */
  char			*title;		/* window's title */
  SDL_Surface		*screen;	/* screen's surface */
}			window_t;

typedef struct		graphic_s	/* main structure for gfx module */
{
  opengl_t		opengl;		/* opengl related */
  list_t		*textures;	/* list of loaded textures */
  window_t		window;		/* window related */
}			graphic_t;

#endif /* GRAOOM_C_GRAPHIC_H */
