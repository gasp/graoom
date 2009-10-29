/*
** event.h for battletrantor in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 22 14:40:25 2009 sebastien rannou
** Last update Fri Oct  2 10:36:36 2009 sebastien rannou
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
  int			(*action)(client_t *client);
}			event_entry_t;

int	/* leave the client */
event_leave(client_t *client);

int	/* toggles the console */
event_console_toggle(client_t *client);

int	/* move to left */
event_move_left(client_t *client);

int	/* move to right */
event_move_right(client_t *client);

int	/* move forward */
event_move_forward(client_t *client);

int	/* move backward */
event_move_back(client_t *client);

int	/* for sdl_console */
console_event_init(client_t *client);

char *	/* for sdl_console */
console_tab_handler(char *command);

int	/* mouse's moving dude! */
event_mouse_move(client_t *client);

#endif /* GRAOOM_CLIENT_EVENT_H */
