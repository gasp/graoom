/*
** event_thread.c for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 01:25:00 2009 sebastien rannou
** Last update Fri Jul 24 01:27:56 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "client.h"
#include "shortcuts.h"
#include "errors.h"

/**!
 * @author	rannou_s
 * main loop of network's thread
 */

#define	NETWORK_DELAY	50

int
network_thread(client_thread_t *holder)
{
  if (holder == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  SDL_mutexP(holder->client->mutex);
  while (holder->client->state == CLIENT_STATE_ON)
    {
      SDL_mutexV(holder->client->mutex);
      SDL_Delay(NETWORK_DELAY);
      SDL_mutexP(holder->client->mutex);
    }
  holder->client->launched_threads--;
  SDL_mutexV(holder->client->mutex);
  free(holder);
  return (SUCCESS);
}
