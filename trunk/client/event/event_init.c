/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Wed Jul 22 21:21:50 2009 sebastien rannou
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
 * Initialization of event's
 * Does nothing for the moment
 */

int
event_init(client_t *client, event_t *event)
{
  if (client == NULL || event == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  return (SUCCESS);
}
