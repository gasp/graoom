/*
** client.h<2> for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 18:20:31 2009 sebastien rannou
** Last update Wed Jul 29 13:19:38 2009 sebastien rannou
*/

#ifndef GRAOOM_C_CLIENT_H
#define GRAOOM_C_CLIENT_H

#define	CLIENT_STATE_ON		0
#define	CLIENT_STATE_OFF	1

#define	CLIENT_NAME_LEN		256

typedef struct		client_time_s		/* used to have a fixed FPS */
{
  int			max_fps;		/* maximum number of FPS */
  int			current_fps;		/* current FPS */
  int			virtual_max_fps;	/* max FPS without raming */
  Uint32		loop_start;		/* before calculs */
  Uint32		loop_end;		/* after blit and flip,
						   before sleep */
}			client_time_t;

typedef struct		client_s		/* main structure */
{
  client_time_t		time;			/* timers are stored here */
  int			launched_threads;	/* number of threads */
  SDL_mutex		*mutex;			/* client's mutex */
  void			*graphic;		/* hash on graphic's struct */
  char			name[CLIENT_NAME_LEN];	/* client's name */
  int			state;			/* client's state */
}			client_t;

typedef struct		client_thread_s		/* parameter for each thread */
{
  client_t		*client;		/* main structure */
  void			*data;			/* internal struct */
}			client_thread_t;

#endif /* GRAOOM_C_CLIENT_H */
