/*
** textures.h for battletrantor in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 23:55:25 2009 sebastien rannou
** Last update Fri Jul 24 20:51:19 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_TEXTURES_H
#define	GRAOOM_C_TEXTURES_H

SDL_Surface *	/* Loads an image */
graphic_load_image(char *path);

int		/* Convert an image to a gl texture */
graphic_surface_to_gl(SDL_Surface *surface, GLuint *texture);

void		/* Destroys a gl texture */
graphic_destroy_gl_texture(GLuint id);

#endif /* GRAOOM_C_TEXTURES_H */
