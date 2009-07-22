/*
** event.h for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 22 14:40:25 2009 sebastien rannou
** Last update Wed Jul 22 19:17:25 2009 sebastien rannou
*/

#ifndef	GRAOOM_CLIENT_EVENT_H
#define	GRAOOM_CLIENT_EVENT_H

typedef struct		event_s		/* main thread's structure */
{
  list_t		*events;
}			event_t;

typedef struct		event_entry_s	/* associates an event with an action */
{
  int			type;
  int			code;
  int			(*action)(client_t *client, event_t *event);  
}			event_entry_t;

#endif /* GRAOOM_CLIENT_EVENT_H */
