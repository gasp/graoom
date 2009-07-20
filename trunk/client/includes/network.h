/*
** networh.h for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:00:23 2009 sebastien rannou
** Last update Mon Jul 20 23:17:56 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_NETWORK_H
#define	GRAOOM_C_NETWORK_H

typedef struct		network_s	/* internals of network's thread */
{
  TCPsocket		sock;		/* SDL_Net's socket */
  IPaddress		ip;		/* SDL_Net's layer for host+port */
  char			*host;		/* host to connect to */
  int			port;		/* port (associated with host) */
}			network_t;

#endif /* GRAOOM_C_NETWORK_H */
