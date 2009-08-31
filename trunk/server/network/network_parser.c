/*
** network_parser.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 19:32:01 2009 sebastien rannou
** Last update Fri Aug 14 22:07:49 2009 
*/

#include <sys/select.h>

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"
#include "errors.h"
#include "network.h"
#include "server.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**!
 * These defines are related to key's value 
 * on configuration file
 */

#define	LOADER_NET_PORT		"port"
#define	LOADER_NET_NAME		"name"
#define	LOADER_NET_MAX		"max_connection"

/**!
 * @author	rannou_s
 * retrieve the maximum number of connection
 * according to three values:
 * ->	FD_SETSIZE
 * ->	user's config
 * We use the smallest of these two values
 */

static int
loader_parser_network_max_con(network_t *network, ini_section_t *conf)
{
  char		*value;
  int		max;

  max = FD_SETSIZE;
  if ((value = ini_retrieve_entry_from_section(conf, LOADER_NET_MAX)) != NULL)
    {
      max = MIN(atoi(value), max);
    }
  if (!(max > 0))
    {
      ERR_RAISE(EC_LOADER_MAX);
      return (ERROR);
    }
  network->configuration.num_max_connection = max;
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Loads network's related settings
 * Here we fetch the maximal number of connection the server can handle
 * with FD_SETSIZE or getrlimit
 */

int
network_parser(server_t *server, ini_section_t *conf)
{
  char		*value;
  network_t	*network;
  int		num;

  if (server == NULL || conf == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if ((network = malloc(sizeof(*network))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  if (!(value = ini_retrieve_entry_from_section(conf, LOADER_NET_PORT)))
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, LOADER_NET_PORT, conf->name);
      free(network);
      return (ERROR);
    }
  num = atoi(value);
  if (!(num > 0 && num < 65536))
    {
      ERR_RAISE(EC_LOADER_PORT, num);
      free(network);
      return (ERROR);
    }
  network->configuration.port = num;
  if (!(value = ini_retrieve_entry_from_section(conf, LOADER_NET_NAME)))
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, LOADER_NET_NAME, conf->name);
      free(network);
      return (ERROR);
    }
  strncpy(server->name, value, MIN(strlen(value), SERVER_NAME_LEN));
  if (loader_parser_network_max_con(network, conf) == ERROR)
    {
      free(network);
      return (ERROR);
    }
  server->holder.network = network;
  return (SUCCESS);
}
