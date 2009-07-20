/*
** loader.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 17:51:59 2009 sebastien rannou
** Last update Mon Jul 20 23:33:01 2009 sebastien rannou
*/

#include "lists.h"
#include "shortcuts.h"
#include "tools.h"
#include "ini.h"
#include "errors.h"
#include "client.h"
#include "log.h"
#include "network_loader.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	LOADER_INI_FILE		"settings.ini"
#define	LOADER_NETWORK_S	"network"
#define	LOADER_GRAPHIC_S	"graphic"
#define	LOADER_AUDIO_S		"audio"

/**!
 * @author	rannou_s
 * associates a .ini file with a specific loader as can be
 * related on global array, works the same way of server's loader
 */

typedef struct	loader_asso_s /* associates an entry with a loader */
{
  char		*name;					/* module's name */
  void		*(*parser)(client_t*, ini_section_t*);	/* parsers's pointer */
  int		(*init)(client_t *, void *);		/* init's pointer */
  int		(*clean)(client_t *, void *);		/* cleaner's pointer */
  int		loaded;					/* > 0 when true */
  void		*data;					/* module's data */
}		loader_asso_t;

static
loader_asso_t global_asso[] =
  {

    {
      .name	=	"network",
      .parser	=	&network_parser,
      .init	=	&network_init,
      .clean	=	&network_cleaner,
      .loaded	=	0,
      .data	=	NULL
    },

    /* End of array */
    {NULL, NULL, NULL, NULL, 0, NULL}

  };

/**!
 * @author	rannou_s
 * call the appropriated function according to autoload's value given
 * in primary ini file, on any problem, raise an error
 * We dont' allow a section to be defined several times in a file
 */

static __inline	int
loader_parser_dispatch(client_t *client, ini_t *ini, ini_section_t *section)
{
  int		i;

  if (client == NULL || section == NULL || ini == NULL)
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
	  if (global_asso[i].parser != NULL)
	    {
	      global_asso[i].data = global_asso[i].parser(client, section);
	      if (global_asso[i].data == NULL)
		return (ERROR);
	    }
	  return (SUCCESS);	      
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
loader_parser(client_t *client)
{
  list_t	*cur;
  ini_t		*primary;
  int		ret;

  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((primary = ini_parse_file(LOADER_INI_FILE)) != NULL)
    {
      for (cur = primary->sections_is; cur != NULL; cur = cur->li_next)
	{
	  if (ERROR == 
	      loader_parser_dispatch(client, primary, (ini_section_t *) cur->data))
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
    {
      ERR_RAISE(EC_INI_FILE, LOADER_INI_FILE);
    }
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
loader(client_t *client)
{
  int		i;

  if (client != NULL)
    {
      memset(client, 0, sizeof(*client));
      if (loader_parser(client) == ERROR)
	return (ERROR);
      for (i = 0; global_asso[i].name != NULL; i++)
	{
	  LOG("loading module [%s]", global_asso[i].name);
	  if (global_asso[i].init != NULL)
	    {
	      if (global_asso[i].init(client,
				      global_asso[i].data) == ERROR)
		{
		  return (ERROR);
		}
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
cleaner(client_t *client)
{
  int		i;

  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (i = 0; global_asso[i].name != NULL; i++)
    {
      if (global_asso[i].loaded > 0)
	{
	  LOG("cleaning module [%s]", global_asso[i].name);
	  if (global_asso[i].clean != NULL)
	    global_asso[i].clean(client, global_asso[i].data);
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's launch each thread :)
 * 1 module <=> 1 thread
 */

int
launcher(client_t *client)
{
  int		i;

  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (i = 0; global_asso[i].name != NULL; i++)
    {
      if (global_asso[i + 1].name != NULL)
	{
	  /* Let's launch each threads */
	}
    }
  /* last module in the array becomes the main thread */
  return (ERROR);
}
