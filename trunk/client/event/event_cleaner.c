
/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Fri Jul 24 16:30:27 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"
#include "log.h"

#include <stdlib.h>

#include "event.h"

/**!
 * @author	rannou_s
 * Let's clean event's structure
 * event == NULL is not an error
 */

int
event_cleaner(client_t *client, event_t *event)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (event != NULL)
    {
      list_free(&event->events, &free);
    }
  return (SUCCESS);
}
