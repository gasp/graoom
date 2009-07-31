/*
** event_thread.c for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 01:25:00 2009 sebastien rannou
** Last update Sat Aug  1 01:59:22 2009 
*/

#include <SDL/SDL.h>

#include "errors.h"
#include "lists.h"
#include "client.h"
#include "SDL_console.h"
#include "event.h"
#include "shortcuts.h"
#include "log.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * Let's catch events and call the associated binded function
 */

static __inline int
event_thread_poll(client_t *client, event_t *event)
{
  list_t		*cur;
  event_entry_t		*entry;

  if (client == NULL || event == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  memset(&event->sdl_event, 0, sizeof(event->sdl_event));
  while (SDL_PollEvent(&event->sdl_event))
    {
      if (CON_Events(&event->sdl_event))
	{
	  for (cur = event->events; cur != NULL; cur = cur->li_next)
	    {
	      entry = (event_entry_t *) cur->data;
	      if (entry != NULL &&
		  event->sdl_event.type == entry->type)
		{
		  if (event->sdl_event.type == SDL_KEYDOWN &&
		      (int) event->sdl_event.key.keysym.sym == entry->code)
		    {
		      entry->action(client);
		    }
		}
	    }
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * main loop of event's thread
 * if we are in console mode, let's call the sdl_console lib
 * (which treat internally events)
 */

#define	EVENT_DELAY	50

int
event_thread(client_thread_t *holder)
{
  if (holder == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  SDL_mutexP(holder->client->mutex);
  while (holder->client->state == CLIENT_STATE_ON)
    {
      event_thread_poll(holder->client, holder->data);
      SDL_mutexV(holder->client->mutex);
      SDL_Delay(EVENT_DELAY);
      SDL_mutexP(holder->client->mutex);
    }
  holder->client->launched_threads--;
  SDL_mutexV(holder->client->mutex);
  free(holder);
  return (SUCCESS);
}
