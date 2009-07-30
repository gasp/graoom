/*
** event.h for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 22 14:40:25 2009 sebastien rannou
** Last update Wed Jul 29 21:08:47 2009 sebastien rannou
*/

#ifndef	GRAOOM_CLIENT_EVENT_H
#define	GRAOOM_CLIENT_EVENT_H

typedef struct		event_s		/* main thread's structure */
{
  list_t		*events;	/* list of binded events */
  SDL_Event		sdl_event;	/* to be polled */
}			event_t;

typedef struct		event_entry_s	/* associates an event with an action */
{
  int			type;
  int			code;
  int			(*action)(client_t *client, event_t *event);  
}			event_entry_t;

int	/* leave the client */
event_leave(client_t *client, event_t *event);

int	/* toggles the console */
event_console_toggle(client_t *client, event_t *event);

int	/* move to left */
event_move_left(client_t *client, event_t *event);

#endif /* GRAOOM_CLIENT_EVENT_H */
