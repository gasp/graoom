/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Mon Jul 20 23:24:53 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"

#include <stdlib.h>
#include <SDL/SDL_net.h>

#include "network.h"

/**!
 * @author	rannou_s
 * Let's clean network's structure
 */

int
network_cleaner(client_t *client, network_t *network)
{
  if (client == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (network->sock != NULL)
    SDLNet_TCP_Close(network->sock);
  if (network->host != NULL)
    free(network->host);
  return (SUCCESS);
}
