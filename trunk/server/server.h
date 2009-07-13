/*
** server.h for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 23:27:43 2009 sebastien rannou
** Last update Mon Jul 13 10:37:21 2009 Sebastien Rannou
*/

#ifndef	GRAOOM_SERVER_H
#define	GRAOOM_SERVER_H

typedef struct		server_s	/* main structure of the program */
{
  network_t		network;	/* network layer */
}			server_t;

int	/* let's load each module */
loader(server_t *server);

int	/* let's clean previously loaded modules */
cleaner(server_t *server);

#endif /* GRAOOM_SERVER_H */
