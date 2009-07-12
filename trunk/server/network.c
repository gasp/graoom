/*
** network.c for graoom in /usr/home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 17:08:02 2009 Sebastien Rannou
** Last update Sun Jul 12 17:47:31 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "network.h"
#include "server.h"
#include "errors.h"

#include <stdlib.h>

/**!
 * @author	rannou_s
 * initialization of the network
 */

int
network_initialize(server_t *server)
{
  if (server == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  
  return (SUCCESS);
}
