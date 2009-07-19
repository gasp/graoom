/*
** server.c for graoom in /home/rannou_s/Work/graoom/server/cmd
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 13:35:09 2009 sebastien rannou
** Last update Sun Jul 19 14:10:13 2009 sebastien rannou
*/

#include <sys/select.h>

#include "shortcuts.h"
#include "lists.h"
#include "errors.h"
#include "server.h"
#include "network.h"
#include "cmd.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * Send connection informations to the client
 */

int
cmd_welcome(server_t *server, network_t *network, network_client_t *client)
{
  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (client == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  network_client_write(client, CMD_WELCOME_MSG, server->name);
  return (SUCCESS);
}
