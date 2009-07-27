/*
** font.h for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 24 18:44:10 2009 sebastien rannou
** Last update Mon Jul 27 13:06:20 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_FONT_H
#define	GRAOOM_C_FONT_H

typedef struct		font_s		/* font's structure */
{
  int			font_id;	/* font's id */
  i2_t			pos;		/* font's position (2d) */
  SDL_Color		*color;		/* font's color */
}			font_t;

int	/* Let's blit a text to a surface */
graphic_text_to_surface(SDL_Surface *surface, font_t *font, char *fmt, ...);

int	/* Returns id of a font */
graphic_font_getid(char *name);

#define	FONT_2D_INFO	"default"

#endif /* GRAOOM_C_FONT_H */
