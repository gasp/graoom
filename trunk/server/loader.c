/*
** loader.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 17:51:59 2009 sebastien rannou
** Last update Mon Jul 13 10:41:28 2009 Sebastien Rannou
*/

#include "lists.h"
#include "shortcuts.h"
#include "tools.h"
#include "ini.h"
#include "errors.h"
#include "network.h"
#include "server.h"
#include "init.h"
#include "log.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>

#define	LOADER_INI_FILE		"public/settings.ini"
#define	LOADER_NETWORK_S	"network"

/**!
 * These defines are related to key's value 
 * on configuration file
 */

#define	LOADER_NET_PORT		"port"
#define	LOADER_NET_MAX		"max_connection"

/**!
 * @author	rannou_s
 * retrieve the maximum number of connection
 * according to three values:
 * ->	FD_SETSIZE
 * ->	user's config
 * We use the smallest of these two values
 */

static __inline	int
loader_parser_network_max_con(server_t *server, ini_section_t *conf)
{
  char		*value;
  int		max;

  if (server == NULL || conf == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
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
  server->network.configuration.num_max_connection = max;
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Loads network's related settings
 * Here we fetch the maximal number of connection the server can handle
 * with FD_SETSIZE or getrlimit
 */

static __inline int
loader_parser_network(server_t *server, ini_section_t *conf)
{
  char		*value;
  int		num;

  if (server == NULL || conf == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (!(value = ini_retrieve_entry_from_section(conf, LOADER_NET_PORT)))
    {
      ERR_RAISE(EC_INI_UNKNOWN_ENTRY, LOADER_NET_PORT, conf->name);
      return (ERROR);
    }
  num = atoi(value);
  if (!(num > 0 && num < 65536))
    {
      ERR_RAISE(EC_LOADER_PORT, num);
      return (ERROR);
    }
  server->network.configuration.port = num;  
  if (loader_parser_network_max_con(server, conf) == ERROR)
    {
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * associates a .ini file with a specific loader as can be
 * related on global array
 */

typedef struct	loader_asso_s /* associates an entry with a loader */
{
  char		*name;					/* module's name */
  int		(*parser)(server_t *, ini_section_t *);	/* loader's pointer */
  int		(*init)(server_t *);			/* init's pointer */
  int		(*clean)(server_t *);			/* cleaner's pointer */
  int		loaded;					/* > 0 when true */
}		loader_asso_t;

static
loader_asso_t global_asso[] =
  {

    /* network's module */
    {
      .name	=	LOADER_NETWORK_S, 
      .parser	=	&loader_parser_network, 
      .init	=	&network_initialize, 
      .clean	=	&network_clean,
      .loaded	=	0
    },

    /* End of array */
    {NULL, NULL, NULL, NULL, 0}

  };

/**!
 * @author	rannou_s
 * call the appropriated function according to autoload's value given
 * in primary ini file, on any problem, raise an error
 * We dont' allow a section to be defined several times in a file
 */

static __inline	int
loader_parser_dispatch(server_t *server, ini_t *ini, ini_section_t *section)
{
  int		i;

  if (server == NULL || section == NULL || ini == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (i = 0; global_asso[i].name != NULL; i++)
    {
      if (strcmp(section->name, global_asso[i].name) == 0)
	{
	  if (global_asso[i].loaded++ > 0)
	    {
	      ERR_RAISE(EC_LOADER_SEV, section->name, ini->name);
	      return (ERROR);
	    }
	  return (global_asso[i].parser(server, section));
	}
    }
  ERR_RAISE(EC_INI_UNKNOWN_ENTRY, section->name, ini->name);
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Let's check that everything was correctly loaded
 */

static __inline int
loader_parser_check(ini_t *file)
{
  int		i;

  if (file == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (i = 0; global_asso[i].name != NULL; i++)
    {
      if (global_asso[i].loaded != 1)
	{
	  ERR_RAISE(EC_LOADER_NULL, global_asso[i].name, file->name);
	  return (ERROR);
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's load ini file, we check each section and call the appropriated
 * loader with a dispatcher
 */

static __inline int
loader_parser(server_t *server)
{
  list_t	*cur;
  ini_t		*primary;
  int		ret;

  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((primary = ini_parse_file(LOADER_INI_FILE)) != NULL)
    {
      for (cur = primary->sections_is; cur != NULL; cur = cur->li_next)
	{
	  if (ERROR == 
	      loader_parser_dispatch(server, primary, (ini_section_t *) cur->data))
	    {
	      ini_free_main(primary);	      
	      return (ERROR);
	    }
	}
      ret = loader_parser_check(primary);
      ini_free_main(primary);
      return (ret);
    }
  else
    ERR_RAISE(EC_INI_FILE, LOADER_INI_FILE);
  ini_free_main(primary);
  return (ERROR);  
}

/**!
 * @author	rannou_s
 * Main entry of the loader
 * Just load configuration files and initialize structures
 * When an error is raised, we leave properly the loader to jump
 * to the cleaner
 * We also check that everything has been correctly loaded
 * Then we initialize each module one by one
 */

int
loader(server_t *server)
{
  int		i;

  if (server != NULL)
    {
      memset(server, 0, sizeof(*server));
      if (loader_parser(server) == ERROR)
	return (ERROR);
      for (i = 0; global_asso[i].name != NULL; i++)
	{
	  LOG("loading module [%s]", global_asso[i].name);
	  if (global_asso[i].init(server) == ERROR)
	    {
	      return (ERROR);
	    }
	}
      LOG("loading completed");
    }
  else
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Clean modules that were previously initialized
 * Continue even if errors were raised
 */

int
cleaner(server_t *server)
{
  int		i;

  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (i = 0; global_asso[i].name != NULL; i++)
    {
      if (global_asso[i].loaded > 0)
	{
	  LOG("cleaning module [%s]", global_asso[i].name);
	  global_asso[i].clean(server);
	}
    }
  return (SUCCESS);
}
