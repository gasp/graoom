/*
** graphic_texture.h for graoom in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 29 20:40:43 2009 sebastien rannou
** Last update Wed Jul 29 20:44:27 2009 sebastien rannou
*/

#ifndef GRAOOM_C_TEXTURE_H
#define GRAOOM_C_TEXTURE_H

int		/* Let's load a texture */
graphic_load_texture(char *path, char *name);

int		/* Converts a surface to an opengl texture */
graphic_surface_to_gl(SDL_Surface *surface, GLuint *texture_id);

SDL_Surface *	/* Returns a SDL_image from a file */
graphic_load_image(char *path);

int		/* Loads each texture defined in texture.ini */
graphic_load_textures(void);

int		/* Cleans up every loaded textures */
graphic_clean_textures(void);

#endif /* GRAOOM_C_TEXTURE_H */
