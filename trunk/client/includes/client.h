/*
** client.h<2> for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 18:20:31 2009 sebastien rannou
** Last update Sun Jul 19 18:40:45 2009 sebastien rannou
*/

#ifndef GRAOOM_C_CLIENT_H
#define GRAOOM_C_CLIENT_H

#define	CLIENT_NAME_LEN	256

typedef struct		client_s		/* main structure */
{
  char			name[CLIENT_NAME_LEN];	/* client's name */
  int			state;			/* client's state */
}			client_t;

#endif /* GRAOOM_C_CLIENT_H */
