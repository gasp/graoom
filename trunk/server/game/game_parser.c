/*
** network_parser.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 19:32:01 2009 sebastien rannou
** Last update Sun Aug  9 14:49:37 2009 
*/

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"
#include "errors.h"
#include "game.h"
#include "server.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**!
 * These defines are related to key's value 
 * on configuration file
 */

#define	LOADER_GAME_MAP		"map"
#define	LOADER_MAP_DIR		"internals/maps/"

/**!
 * @author	rannou_s
 * Let's load a map
 */

static __inline int
game_parser_map(game_t *game, ini_section_t *sec)
{
  char			*map;
  int			len;

  if ((map = ini_retrieve_entry_from_section(sec, LOADER_GAME_MAP)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, LOADER_GAME_MAP, sec->name);
      return (ERROR);
    }
  if ((len = strlen(map)) > MAP_LEN)
    {
      ERR_RAISE(EC_GAME_MAPLEN, len, MAP_LEN);
      return (ERROR);
    }
  strcpy(game->map.name, map);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Loads game's related settings
 */

void *
game_parser(server_t *server, ini_section_t *conf)
{
  game_t	*game;

  if (server == NULL || conf == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (NULL);
    }
  if ((game = malloc(sizeof(*game))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (NULL);
    }
  if (ERROR == game_parser_map(game, conf))
    {
      free(game);
      return (NULL);
    }
  server->holder.game = game;
  return (game);
}
