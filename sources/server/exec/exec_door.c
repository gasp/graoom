/*
** exec.c for battletrantor in /home/aimxhaisse/work/graoom/server/exec
** 
** Made by 
** Login   <aimxhaisse@epitech.net>
** 
** Started on  Sun Aug  9 14:18:43 2009 
** Last update Sun Aug  9 15:30:03 2009 
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "server.h"
#include "errors.h"
#include "log.h"
#include "network.h"
#include "client.h"
#include "server_log.h"

#include <string.h>
#include <stdlib.h>

typedef struct		exec_commands_s			/* cmd entry */
{
  char			*name;				/* command's name */
  void			(*f)(server_t *, char *);	/* associated action */
}			exec_commands_t;

exec_commands_t		global_exec[] = 
  {

    /* talk command */
    {
      .name	=	"talk",
      .f	=	NULL
    },

    /* End of array */
    {
      .name	=	NULL,
      .f	=	NULL
    }

  };

/**!
 * @author	rannou_s
 * Called when a command is extracted
 * Look into global_exec for a command association, and call it
 * command contains : command:parameters
 * example:
 * talk:hi everybody
 */

int
exec_gate(server_t *server, network_client_t *client, char *command)
{
  int		i;
  int		len;
  unsigned int	cmdlen;

  if (server == NULL || command == NULL || client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  cmdlen = strlen(command);
  for (i = 0; global_exec[i].name != NULL; i++)
    {
      len = MIN(cmdlen, strlen(global_exec[i].name));
      if (strncmp(command, global_exec[i].name, len) == 0 &&
	  *(command + len + 1) == ':')
	{
	  LOG(LOG_EXEC_COMMAND, global_exec[i].name, client->id);
	  if (global_exec[i].f != NULL)
	    {
	      
	    }
	}
    }
  return (SUCCESS);
}
