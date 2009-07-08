/*
** loader.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 17:51:59 2009 sebastien rannou
** Last update Wed Jul  8 23:39:50 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "tools.h"
#include "ini.h"
#include "errors.h"

#include <stdio.h>

#define	LOADER_INI_FILE		"loader/loader.ini"
#define	LOADER_AUTOLOAD_S	"autoload"

/**!
 * @author	rannou_s
 * Main entry of the loader
 * Just load a primary file containing sub ini files to load
 */

int
loader(void)
{
  ini_t		*primary;
  section_t	*toload;
  list_t	*cur;

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
  ini_free_main(primary);
  return (ERROR);
}
