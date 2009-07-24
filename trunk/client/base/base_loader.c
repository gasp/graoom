/*
** loader.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 17:51:59 2009 sebastien rannou
** Last update Fri Jul 24 01:35:21 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "lists.h"
#include "shortcuts.h"
#include "tools.h"
#include "ini.h"
#include "errors.h"
#include "client.h"
#include "log.h"
#include "log_client.h"
#include "network_loader.h"
#include "graphic_loader.h"
#include "event_loader.h"
#include "threads.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define	LOADER_INI_FILE		"settings.ini"

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
  int		(*thread)(void *);			/* cleaner's pointer */
  int		loaded;					/* > 0 when true */
  void		*data;					/* module's data */
}		loader_asso_t;

static
loader_asso_t global_asso[] =
  {

    /* Graphic module - need to be loaded first */

    {
      .name	=	"graphic",
      .parser	=	&graphic_parser,
      .init	=	&graphic_init,
      .clean	=	&graphic_cleaner,
      .thread   =	&graphic_thread,
      .loaded	=	0,
      .data	=	NULL
    },    

    /* Events module */

    {
      .name	=	"event",
      .parser	=	&event_parser,
      .init	=	&event_init,
      .clean	=	&event_cleaner,
      .thread   =	&event_thread,
      .loaded	=	0,
      .data	=	NULL
    },

    /* Network module */

    {
      .name	=	"network",
      .parser	=	&network_parser,
      .init	=	&network_init,
      .clean	=	&network_cleaner,
      .thread   =	&network_thread,
      .loaded	=	0,
      .data	=	NULL
    },

    /* End of array */
    {NULL, NULL, NULL, NULL, NULL, 0, NULL}

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
	  LOG(LOG_LOADER_MODULE_CONF, ((ini_section_t *) cur->data)->name);
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
	  LOG(LOG_LOADER_MODULE, global_asso[i].name);
	  if (global_asso[i].init != NULL)
	    {
	      if (global_asso[i].init(client,
				      global_asso[i].data) == ERROR)
		{
		  ERR_RAISE(EC_LOADER_NOK, global_asso[i].name);
		  return (ERROR);
		}
	    }
	}
      LOG(LOG_LOADER_MODULE_OK);
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
	  free(global_asso[i].data);
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialize a parameter struct to be send to the thread and launch it
 */

static __inline int
launcher_thread(client_t *client, loader_asso_t *data, int has_to_thread)
{
  client_thread_t	*new_thread;

  if (client == NULL || data == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (data->thread == NULL)
    return (SUCCESS);
  new_thread = malloc(sizeof(*new_thread));
  if (new_thread == NULL)
    {
      threads_leave(client);
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  new_thread->client = client;
  new_thread->data = data->data;
  if (has_to_thread == SUCCESS)
    {
      if (SDL_CreateThread(data->thread, new_thread) == NULL)
	{
	  threads_leave(client);
	  ERR_RAISE(EC_SDL_CREATE_THREAD, SDL_GetError());
	  return (ERROR);
	}
    }
  else
    data->thread(new_thread);
  return (SUCCESS);
}

/**!
 * @author	rannou_s 
 * The network thread then wait other threads to have finnished by sleeping
 * in cycles of SLEEP_CYCLE
 */

#define	SLEEP_CYCLE	50

static __inline int
launcher_wait_threads_to_leave(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  SDL_mutexP(client->mutex);
  while (client->launched_threads > 0)
    {
      SDL_mutexV(client->mutex);
      LOG(LOG_WAIT_THREADS, client->launched_threads);
      SDL_Delay(SLEEP_CYCLE);
      SDL_mutexP(client->mutex);
    }
  SDL_mutexV(client->mutex);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's launch each thread :)
 * 1 module <=> 1 thread
 * We start at i = 1 to avoid loading the first thread (it will become
 * the main thread), because OpenGL requires to be initialized in the same
 * thread (it's already loaded before).
 */

int
launcher(client_t *client)
{
  int			i;

  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (threads_init(client) == ERROR)
    return (ERROR);
  for (i = 1; global_asso[i].name != NULL; i++)
    {
      if (launcher_thread(client, &global_asso[i], SUCCESS) == ERROR)
	{
	  threads_leave(client);
	  break;
	}
      else
	client->launched_threads++;
    }
  /* First module in the array becomes the main thread */
  if (launcher_thread(client, &global_asso[0], ERROR) == ERROR)
    threads_leave(client);
  return (launcher_wait_threads_to_leave(client));
}
