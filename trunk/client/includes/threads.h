/*
** threads.h for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 22 23:49:02 2009 sebastien rannou
** Last update Thu Jul 23 00:09:10 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_THREAD_H
#define	GRAOOM_C_THREAD_H

int	/* intialize mutex */
threads_init(client_t *client);

int	/* changes client's state */
threads_leave(client_t *client);

int	/* clean created mutex */
threads_clean(client_t *client);

#endif /* GRAOOM_C_THREAD_H */
