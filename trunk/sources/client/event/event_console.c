/*
** event_console.c for battletrantor in /home/aimxhaisse/work/graoom/client/event
** 
** Made by 
** Login   <aimxhaisse@epitech.net>
** 
** Started on  Fri Jul 31 20:50:31 2009 
** Last update Wed Oct  7 09:22:49 2009 sebastien rannou
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "lists.h"
#include "client.h"
#include "errors.h"
#include "shortcuts.h"
#include "event.h"
#include "SDL_console.h"

#include <stdlib.h>

/**!
 * Global reference to the main structure, ugly yeah, but don't have the choice
 * since SDL_Console doesn't handle passing an additionnal parameter to the handler
 */

static void *
global_console_client = NULL;

typedef struct		console_action_s
{
  char			*name;
  int			(*action)(client_t *);
}			console_action_t;

console_action_t
global_console_actions[] =
  {
    
    /* byebye */
    {
      .name		=	"quit",
      .action		=	&event_leave,
    },

    /* byebye */
    {
      .name		=	"exit",
      .action		=	&event_leave,
    },
    
    /* end of array */
    {NULL, NULL}
  };

/**!
 * @author	rannou_s
 * Command dispatcher, call the appropriated function according to the
 * command typed by the user
 */

#define	CMD_NOT_FOUND	"%s: command not found"

void
console_command_handler(ConsoleInformation *console, char *command)
{
  client_t		*client = global_console_client;
  int			i;
  int			len;
  int			tmp;

  if (console == NULL || command == NULL || client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return;
    }
  tmp = strlen(command);
  /* Let's check actions */
  for (i = 0; global_console_actions[i].action != NULL; i++)
    {
      len = strlen(global_console_actions[i].name);
      if (len == (int) strlen(command))
	{
	  if (strncasecmp(global_console_actions[i].name, command, len) == 0)
	    {
	      if (command[len] == '\0' || command[len] == ' ' || command[len] == '\t')
		{
		  global_console_actions[i].action(client);
		  return;
		}
	    }
	}
    }
  CON_Out(console, CMD_NOT_FOUND, command);
  return;
}

/**!
 * @author	rannou_s
 * Let's full a local array of some completion options
 */

char *
console_tab_handler(char *command)
{
  return (command);
}

/**!
 * @author	rannou_s
 * Initialize this file by setting global_client to client's address
 * Quite ugly but the only solution is to redesign SDL_Console library
 * Only allocated memory for completion
 */

int
console_event_init(client_t *client)
{
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  global_console_client = client;
  return (SUCCESS);
}
