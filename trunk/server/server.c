/*
** server.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 14:15:51 2009 sebastien rannou
** Last update Fri Jul 17 19:27:08 2009 sebastien rannou
*/

#include "lists.h"
#include "shortcuts.h"
#include "tools.h"
#include "server.h"
#include "log.h"

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
    LOG("Let's launch the server");
  cleaner(&server);
  return (SUCCESS);
}
