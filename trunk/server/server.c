/*
** server.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 14:15:51 2009 sebastien rannou
** Last update Wed Jul  8 23:29:15 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "tools.h"
#include "server.h"

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE
#endif

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
  if (loader() == SUCCESS)
    {
      printf("Here we launch the server\n");
    }
  printf("We clean everything\n");
  return (SUCCESS);
}
