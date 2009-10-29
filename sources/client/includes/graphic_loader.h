/*
** graphic_loader.h for battletrantor in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 16:39:54 2009 sebastien rannou
** Last update Wed Jul 29 20:43:36 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_LOADER_H
#define	GRAOOM_C_LOADER_H

int	/* main thread's loop */
graphic_thread(void *holder);

void *	/* let's load configuration from settings.ini */
graphic_parser(client_t *client, ini_section_t *section);

int	/* let's init SDL/OpenGL (window creation, ..) */
graphic_init(client_t *client, void *graphic);

int	/* let's clean this module */
graphic_cleaner(client_t *client, void *graphic) ;

#endif /* GRAOOM_C_LOADER_H */
