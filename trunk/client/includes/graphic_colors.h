/*
** graphic_colors.h for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 26 15:44:23 2009 sebastien rannou
** Last update Mon Jul 27 13:42:32 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_GRAPHIC_COLORS_H
#define GRAOOM_C_GRAPHIC_COLORS_H

int		/* Let's initialize colors */
graphic_load_colors(void);

void		/* Let's clean colors */
graphic_clean_colors(void);

SDL_Color *	/* Let's get a color */
graphic_colors_get(char *name);

#define	COL_2D_INFO	COL_WHITE

#define	COL_DARKGREY	"darkgrey"
#define	COL_WHITE	"white"

#endif /* GRAOOM_C_GRAPHIC_COLORS_H */
