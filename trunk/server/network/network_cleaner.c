/*
** network.c for graoom in /usr/home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 17:08:02 2009 Sebastien Rannou
** Last update Sun Aug  9 14:37:51 2009 
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"
#include "log.h"

#include <stdlib.h>
#include <unistd.h>

/**!
 * @author	rannou_s
 * Called before leaving the program, clean everything that was
 * loaded by network_initialize
 * -> close primary socket
 */

int
network_clean(server_t *server, network_t *network)
{
  if (server == NULL || network == NULL)
    {
      ERR_RAISE(EC_NULL_PTR);
      return (ERROR);
    }
  if (network->primary_socket > 0)
    {
      if (close(network->primary_socket) == ERROR)
	{
	  ERR_RAISE(EC_SYS_CLOSE);
	}
    }
  return (SUCCESS);
}
