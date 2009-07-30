/*
** network_init.c for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 21:07:00 2009 sebastien rannou
** Last update Wed Jul 29 21:10:57 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "shortcuts.h"
#include "lists.h"
#include "client.h"
#include "errors.h"
#include "ini.h"
#include "SDL_console.h"

#ifndef	_BSD_SOURCE	/* strdup on linux */
#define	_BSD_SOURCE
#endif

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "event.h"

typedef struct		event_asso_s	/* associates an event with a key */
{
  char			*name;		/* name of the action */
  int			(*action)(client_t *client, event_t *event);
}			event_asso_t;

static event_asso_t
global_event_asso[] =
  {

    /* Leave the client */
    {
      .name	=	"quit",
      .action	=	&event_leave
    },

    /* Move to left */
    {
      .name	=	"move_left",
      .action	=	&event_move_left
    },

    /* End of array */
    {NULL, NULL}
  };

typedef struct		event_key_s	/* associates a key with a name */
{
  char			*name;		/* name found in ini files */
  int			type;		/* event type */
  int			code;		/* associated keycode/mouse button */
}			event_key_t;

static event_key_t
global_event_keys[] = 
  {

    /* Escape event */
    {
      .name	=	"key_escape",
      .type	=	SDL_KEYDOWN,
      .code	=	SDLK_ESCAPE
    },

    /* Space event */
    {
      .name	=	"key_space",
      .type	=	SDL_KEYDOWN,
      .code	=	SDLK_SPACE
    },

    /* Left arrow */
    {
      .name	=	"key_left",
      .type	=	SDL_KEYDOWN,
      .code	=	SDLK_LEFT
    },

    /* End of array */
    {NULL, -1, -1}
  };

/**!
 * @author	rannou_s
 * Events that CAN'T BE CHANGED through ini file 
 */

static event_entry_t
global_entry_default[] =
  {

    /* Console toogling (forbidden to touch this !) */
    {
      .type	=	SDL_KEYDOWN,
      .code	=	SDLK_BACKQUOTE,
      .action	=	&event_console_toggle
    },
    
    /* End of array */
    {
      .type	=	-1,
      .code	=	-1,
      .action	=	NULL
    }
  };

/**!
 * @author	rannou_s
 * Let's push the key/value entry to event's list
 */

static __inline int
event_parser_fetch_push(event_t *event, event_asso_t *action, 
			event_key_t *key)
{
  event_entry_t		*new_elem;

  if (event == NULL || action == NULL || key == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if ((new_elem = malloc(sizeof(*new_elem))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  new_elem->type = key->type;
  new_elem->code = key->code;
  new_elem->action = action->action;
  if (list_push(&event->events, new_elem) == ERROR)
    {
      free(new_elem);
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * For each association key = value in the .ini file,
 * let's try to associate it with an existing key and an existing action
 * Do not leave on error
 */

static __inline int
event_parser_fetch(event_t *event, ini_section_t *section)
{
  ini_content_t		*content;
  list_t		*cur;
  int			i, j;
  int			match;

  if (event == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (cur = section->content_li, match = 0; cur != NULL; cur = cur->li_next)
    {
      content = (ini_content_t *) cur->data;
      for (i = 0; global_event_keys[i].name != NULL; i++)
	{
	  if (strcasecmp(global_event_keys[i].name, content->name) == 0)
	    {
	      for (j = 0; global_event_asso[j].name; j++)
		{
		  if (strcasecmp(global_event_asso[j].name, content->value) == 0)
		    {
		      event_parser_fetch_push(event, &global_event_asso[j],
					      &global_event_keys[i]);
		      match++;
		    }
		}
	    }
	}
      if (!match)
	{
	  ERR_RAISE(EC_LOADER_EVENT_UNK, content->name, content->value);
	  return (ERROR);
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's bind some shortcuts that can't be changed
 * Performs a check so as to forbid overload of that events 
 */

static __inline int
event_parser_default_locked(client_t *client, event_t *event)
{
  int			i;
  event_entry_t		*entry;
  event_entry_t		*tmp;
  list_t		*current;

  if (client == NULL || event == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  for (i = 0; global_entry_default[i].action != NULL; i++)
    {
      if ((entry = malloc(sizeof(*entry))) == NULL)
	{
	  ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
	  return (ERROR);
	}
      memcpy(entry,  &global_entry_default[i], sizeof(*entry));
      for (current = event->events; current != NULL; current = current->li_next)
	{
	  tmp = current->data;
	  if (tmp->type == entry->type && tmp->code == entry->code)
	    {
	      ERR_RAISE(EC_LOADER_EVENT_OVER, entry->type, entry->code);
	      return (ERROR);
	    }
	}
      if (list_push(&event->events, entry) == ERROR)
	{
	  free(entry);
	  ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
	  return (ERROR);
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Initialization of event's module
 * Allocates event structure and initialize its content
 * Here the binding between keys and actions is made
 */

void *
event_parser(client_t *client, ini_section_t *section)
{
  event_t		*event;

  if (client == NULL || section == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (NULL);
    }
  if ((event = malloc(sizeof(*event))) == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (NULL);
    }
  memset(event, 0, sizeof(*event));
  if (event_parser_fetch(event, section) == ERROR)
    {
      free(event);
      return (NULL);
    }
  if (event_parser_default_locked(client, event) == ERROR)
    {
      free(event);
      return (NULL);
    }
  return (event);
}
