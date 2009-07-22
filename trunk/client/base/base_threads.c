/*
** base_thread.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul 22 23:38:40 2009 sebastien rannou
** Last update Thu Jul 23 00:39:54 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "shortcuts.h"
#include "client.h"
#include "errors.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * Destroys created mutex
 */

int
threads_clean(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (client->mutex != NULL)
    {
      SDL_DestroyMutex(client->mutex);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialize the mutex
 */

int
threads_init(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((client->mutex = SDL_CreateMutex()) == NULL)
    {
      ERR_RAISE(EC_SDL_CREATEMUTEX, SDL_GetError());
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Change client's state so as to leave properly launched threads
 */

int
threads_leave(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  SDL_LockMutex(client->mutex);
  client->state = CLIENT_STATE_OFF;
  SDL_UnlockMutex(client->mutex);
  return (SUCCESS);
}
