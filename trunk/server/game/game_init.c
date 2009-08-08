/*
** init.c for graoom in /home/rannou_s/Work/graoom/server/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 21:37:06 2009 sebastien rannou
** Last update Sat Aug  8 14:40:16 2009 
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
game_initialize(server_t *server, game_t *game)
{
  if (server == NULL || game == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's clean up everything
 */

int
game_clean(server_t *server, game_t *game)
{
  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (game == NULL)
    {
      return (ERROR);
    }
  return (SUCCESS);
}
