/*
** exec.c for graoom in /home/aimxhaisse/work/graoom/server/exec
** 
** Made by 
** Login   <aimxhaisse@epitech.net>
** 
** Started on  Sun Aug  9 14:18:43 2009 
** Last update Sun Aug  9 14:32:06 2009 
*/

#include "shortcuts.h"
#include "server.h"
#include "errors.h"

#include <stdlib.h>

typedef struct		exec_commands_s			/* cmd entry */
{
  char			*name;				/* command's name */
  void			(*f)(server_t *, char *);	/* associated action */
}			exec_commands_t;

/**!
 * @author	rannou_s
 * Called when a command is extracted and executes it
 */

int
exec_gate(server_t *server, char *command)
{
  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (command == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  
  return (SUCCESS);
}
