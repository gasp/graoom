/*
** event_loader.h for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 22 21:20:45 2009 sebastien rannou
** Last update Wed Jul 22 21:32:35 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_EVENT_H
#define	GRAOOM_C_EVENT_H

void *	/* let's fetch client's configuration */
event_parser(client_t *client, ini_section_t *section);

int	/* let's load event's thread */
event_init(client_t *client, void *event);

int	/* let's clean event's thread */
event_cleaner(client_t *client, void *event);

#endif /* GRAOOM_C_EVENT_H */
