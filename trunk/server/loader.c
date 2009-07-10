/*
** loader.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 17:51:59 2009 sebastien rannou
** Last update Fri Jul 10 09:07:22 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "tools.h"
#include "ini.h"
#include "errors.h"
#include "server.h"

#include <stdio.h>

#define	LOADER_INI_FILE		"loader/loader.ini"
#define	LOADER_AUTOLOAD_S	"autoload"

static __inline int
loader_parser_network(server_t *server, char *file)
{
  return (SUCCESS);
}

static __inline int
loader_parser(server_t *server)
{
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
	      /* Stopped here: let's treat each sub-section loading */
	    }
	  ini_free_main(primary);
	  return (SUCCESS);
	}
    }
  ERR_RAISE(EC_PRIM_INI_FILE, LOADER_INI_FILE);
  ini_free_main(primary);
  return (ERROR);  
}

/**!
 * @author	rannou_s
 * Main entry of the loader
 * Just load a primary file containing sub ini files to load
 */

int
loader(server_t *server)
{
  if (server != NULL)
    {
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
