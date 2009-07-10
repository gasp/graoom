/*
** loader.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 17:51:59 2009 sebastien rannou
** Last update Fri Jul 10 11:04:10 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "tools.h"
#include "ini.h"
#include "errors.h"
#include "server.h"

#include <stdio.h>
#include <string.h>

#define	LOADER_INI_FILE		"private/internals/loader.ini"
#define	LOADER_AUTOLOAD_S	"autoload"

/**!
 * @author	rannou_s
 * Loads network's related settings
 */

static __inline int
loader_parser_network(server_t *server, ini_t *conf)
{
  if (server == NULL || conf == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  /* let's do stuff here */
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * associates a .ini file with a specific loader as can be
 * related on global array
 */

typedef struct	loader_asso_s /* associates an entry with a loader */
{
  char		*name;				/* module's name */
  int		(*f)(server_t*, ini_t*);	/* loader's pointer */
}		loader_asso_t;

static
loader_asso_t global_asso[] =
  {
    {"network", &loader_parser_network},
    {NULL, NULL}
  };

/**!
 * @author	rannou_s
 * call the appropriated function according to autoload's value given
 * in primary ini file, on any problem, raise an error
 */

#define	FULLPATH_LEN	512

static __inline	int
loader_parser_dispatch(server_t *server, ini_t *ini, ini_content_t *entry)
{
  char		fullpath[FULLPATH_LEN];
  ini_t		*conf;
  int		i;

  if (server == NULL || entry == NULL || ini == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (i = 0; global_asso[i].name != NULL; i++)
    {
      if (strcmp(entry->name, global_asso[i].name) == 0)
	{
	  snprintf(fullpath, sizeof(fullpath), "public/%s", entry->value);
	  if ((conf = ini_parse_file(fullpath)) != NULL)
	    return (global_asso[i].f(server, conf));
	  ERR_RAISE(EC_INI_FILE, fullpath);
	  return (ERROR);
	}
    }
  ERR_RAISE(EC_INI_UNKNOWN_ENTRY, entry->name, ini->name);
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Let's load main ini file, which will call loading of each sub
 * configuration files, leave on any error
 */

static __inline int
loader_parser(server_t *server)
{
  ini_content_t	*cast;
  ini_section_t	*toload;
  list_t	*cur;
  ini_t		*primary;

  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((primary = ini_parse_file(LOADER_INI_FILE)) != NULL)
    {
      if ((toload = ini_retrieve_section(primary, LOADER_AUTOLOAD_S)) != NULL)
	{
	  for (cur = toload->content_li; cur != NULL; cur = cur->li_next)
	    {
	      cast = (ini_content_t *) cur->data;
	      if (loader_parser_dispatch(server, primary, cast) == ERROR)
		{
		  ini_free_main(primary);
		  return (ERROR);
		}
	    }
	  ini_free_main(primary);
	  return (SUCCESS);
	}
      else
	ERR_RAISE(EC_INI_SEC, LOADER_AUTOLOAD_S, LOADER_INI_FILE);	
    }
  else
    ERR_RAISE(EC_INI_FILE, LOADER_INI_FILE);
  ini_free_main(primary);
  return (ERROR);  
}

/**!
 * @author	rannou_s
 * Main entry of the loader
 * Just load a primary file containing sub ini files to load
 * When an error is raised, we leave properly the loader to jump
 * to the cleaner
 */

int
loader(server_t *server)
{
  if (server != NULL)
    {
      memset(server, 0, sizeof(*server));
      if (loader_parser(server) == ERROR)
	{
	  return (ERROR);
	}
    }
  else
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  return (SUCCESS);
}
