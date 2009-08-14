/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Thu Jul 23 00:57:52 2009 sebastien rannou
*/

#ifndef	_BSD_SOURCE	/* strdup on linux */
#define	_BSD_SOURCE
#endif

#include <SDL/SDL.h>

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"
#include "ini.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <SDL/SDL_net.h>

#include "network.h"

#define	CLIENT_HOST_VAL	"host"
#define	CLIENT_PORT_VAL	"port"

/**!
 * @author	rannou_s
 * let's fetch data from settings.ini (section network) to add
 * some informations into network's structure
 */

static  int
network_parser_fetch(network_t *network, ini_section_t *section)
{
  char			*val;

  if (network == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((val = ini_retrieve_entry_from_section(section, CLIENT_PORT_VAL)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, CLIENT_PORT_VAL, section->name);
      return (ERROR);
    }
  network->port = atoi(val);
  if (!(network->port > 0 && network->port < 65536))
    {
      ERR_RAISE(EC_LOADER_PORT, network->port);
      return (ERROR);
    }
  if ((val = ini_retrieve_entry_from_section(section, CLIENT_HOST_VAL)) == NULL)
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, CLIENT_HOST_VAL, section->name);
      return (ERROR);
    }
  if ((network->host = strdup(val)) == NULL)
    {
      ERR_RAISE(EC_SYS_STRDUP, strerror(errno)); /* assuming errno is set */
      return (ERROR);
    }  
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialization of network's module
 * Allocates network structure and initialize its content
 */

void *
network_parser(client_t *client, ini_section_t *section)
{
  network_t		*network;

  if (client == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (NULL);
    }
  if ((network = malloc(sizeof(*network))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (NULL);
    }
  memset(network, 0, sizeof(*network));
  if (network_parser_fetch(network, section) == ERROR)
    {
      free(network);
      return (NULL);
    }
  return (network);
}
