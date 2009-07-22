
/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Wed Jul 22 21:58:41 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"

#include <stdlib.h>
#include <SDL/SDL.h>

#include "event.h"

/**!
 * @author	rannou_s
 * Let's clean event's structure
 * event == NULL is not an error
 */

int
event_cleaner(client_t *client, event_t *event)
{
  list_t		*cur;

  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (event != NULL)
    {
      list_free(&event->events, NULL);
    }
  return (SUCCESS);
}
