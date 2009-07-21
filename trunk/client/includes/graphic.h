/*
** graphic.h for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 12:35:08 2009 sebastien rannou
** Last update Tue Jul 21 16:21:00 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_GRAPHIC_H
#define	GRAOOM_C_GRAPHIC_H

typedef struct		window_s	/* data concerning the window */
{
  int			width;		/* window's width */
  int			height;		/* window's height */
  char			*title;		/* window's title */
  SDL_Surface		*screen;	/* screen's surface */
}			window_t;

typedef struct		graphic_s	/* main structure for gfx module */
{
  window_t		window;		/* data about window */
}			graphic_t;

#endif /* GRAOOM_C_GRAPHIC_H */
