/*
** init.c for battletrantor in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 21:37:06 2009 sebastien rannou
** Last update Sun Aug  9 14:36:51 2009 
*/

#include "shortcuts.h"
#include "server.h"
#include "errors.h"
#include "game.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * initialization of the game:
 * -> get the map, parses it, create associated structures
 */

int
game_initialize(server_t *server)
{
  if (server == NULL || GAME == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's clean up everything
 */

int
game_clean(server_t *server)
{
  if (server == NULL || GAME == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  free(GAME);
  server->holder.game = NULL;
  return (SUCCESS);
}
