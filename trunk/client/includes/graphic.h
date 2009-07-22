/*
** graphic.h for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 12:35:08 2009 sebastien rannou
** Last update Tue Jul 21 21:55:30 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_GRAPHIC_H
#define	GRAOOM_C_GRAPHIC_H

typedef struct		texture_s	/* texture SDL/OpenGL */
{
  SDL_Surface		*surface;	/* SDL  */
  GLuint		id;		/* Opengl's ID */
}			texture_t;

typedef struct		window_s	/* data concerning the window */
{
  int			width;		/* window's width */
  int			height;		/* window's height */
  char			*title;		/* window's title */
  SDL_Surface		*screen;	/* screen's surface */
}			window_t;

typedef struct		opengl_s
{
  SDL_Surface		*screen2d;	/* blitted each frame as '2d' screen */
}			opengl_t;

#define	BUF_LOAD	64

typedef struct		loading_s	/* info here are blitted on screen2d */
{
  texture_t		*background;	/* background's image */
  char			text[BUF_LOAD];	/* text to display */
  i2_t			text_pos;	/* text's position */
  int			text_font;	/* text's font (id) */
}			loading_t;

typedef struct		graphic_s	/* main structure for gfx module */
{
  list_t		*textures;	/* list of loaded textures */
  loading_t		*loading;	/* only used during loading */
  window_t		window;		/* data about window */
  opengl_t		opengl;		/* opengl internals */
}			graphic_t;

#endif /* GRAOOM_C_GRAPHIC_H */