/*
** server.c for battletrantor in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 14:15:51 2009 sebastien rannou
** Last update Sun Jul 19 00:24:08 2009 sebastien rannou
*/

#include <sys/select.h>

#include "lists.h"
#include "shortcuts.h"
#include "tools.h"
#include "server.h"
#include "log.h"
#include "network.h"

#include <stdio.h>

/**!
 * @author	rannou_s
 * Main entry of the server
 * Call the loader, if everything goes well, start the server
 * In all cases, we call the cleaner (even if everything wasn't set)
 */

int
main(void)
{
  server_t	server;

  if (loader(&server) == SUCCESS)
    {
      LOG("Let's launch the server");
      launcher(&server);
    }
  cleaner(&server);
  return (SUCCESS);
}
