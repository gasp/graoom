/*
** event_thread.c for battletrantor in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 01:25:00 2009 sebastien rannou
** Last update Sat Aug  8 13:41:31 2009 
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
  int		status;

  if (holder == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  status = CLIENT_STATE_ON;
  while (status == CLIENT_STATE_ON)
    {
      SDL_mutexP(holder->client->mutex);
      status = holder->client->state;
      SDL_mutexV(holder->client->mutex);
      SDL_Delay(NETWORK_DELAY);
    }
  holder->client->launched_threads--;
  SDL_mutexV(holder->client->mutex);
  free(holder);
  return (SUCCESS);
}
