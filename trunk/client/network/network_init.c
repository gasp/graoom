/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Thu Jul 23 00:57:10 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <SDL/SDL_net.h>

#include "network.h"

/**!
 * @author	rannou_s
 * Initialization of the connection with the server
 * Simply opens a TCP socket with the help of SDL_Net
 */

int
network_init(client_t *client, network_t *network)
{
  if (client == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (SDLNet_ResolveHost(&network->ip, network->host, network->port) == ERROR)
    {
      ERR_RAISE(EC_SDL_NET_RESOLVE, network->host, 
		network->port, SDLNet_GetError());
      return (ERROR);
    }
  if ((network->sock = SDLNet_TCP_Open(&network->ip)) == NULL)
    {
      ERR_RAISE(EC_SDL_NET_OPEN, SDLNet_GetError());
      return (ERROR);
    }
  return (SUCCESS);
}
