/*
** loader.h for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 18:50:24 2009 sebastien rannou
** Last update Wed Jul 22 00:32:48 2009 sebastien rannou
*/

#ifndef GRAOOM_C_LOADER_H
#define GRAOOM_C_LOADER_H

int	/* let's load each module */
loader(client_t *client);

int	/* let's clean each module */
cleaner(client_t *client);

int	/* let's launch each threads */
launcher(client_t *client);

#endif /* GRAOOM_C_LOADER_H */
