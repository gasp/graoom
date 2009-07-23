/*
** client.h<2> for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 18:20:31 2009 sebastien rannou
** Last update Thu Jul 23 14:54:20 2009 sebastien rannou
*/

#ifndef GRAOOM_C_CLIENT_H
#define GRAOOM_C_CLIENT_H

#define	CLIENT_STATE_ON		0
#define	CLIENT_STATE_OFF	1

#define	CLIENT_NAME_LEN		256

typedef struct		client_s		/* main structure */
{
  SDL_mutex		*mutex;			/* client's mutex */
  char			name[CLIENT_NAME_LEN];	/* client's name */
  int			state;			/* client's state */
  void			*graphic;		/* hash on graphic's struct */
}			client_t;

typedef struct		client_thread_s		/* parameter for each thread */
{
  client_t		*client;		/* main structure */
  void			*data;			/* internal struct */
}			client_thread_t;

#endif /* GRAOOM_C_CLIENT_H */
