/*
** server.c for graoom in /home/rannou_s/Work/graoom/server/cmd
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 13:35:09 2009 sebastien rannou
** Last update Sun Aug  9 14:36:16 2009 
*/

#include <sys/select.h>

#include "shortcuts.h"
#include "lists.h"
#include "errors.h"
#include "server.h"
#include "network.h"
#include "cmd.h"
#include "protocol.h"
#include "game.h"

#include <stdlib.h>

/**!
 * @author	rannous_s
 * Sends informations about the map
 */

int
cmd_map(server_t *server, network_t *network, network_client_t *client)
{
  game_t		*game;

  if (server == NULL || network == NULL || client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  game = server->holder.game;
  if (game != NULL)
    {
      network_client_write(client, CMD_CON_MAP, game->map.name);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Send connection informations to the client
 */

int
cmd_welcome(server_t *server, network_t *network, network_client_t *client)
{
  if (server == NULL || network == NULL || client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  network_client_write(client, CMD_WELCOME_MSG, server->name);
  return (SUCCESS);
}
