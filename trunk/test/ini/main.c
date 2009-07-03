/*
** main.c for graoom in /home/rannou_s/Work/graoom/test/lists
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 22:30:39 2009 Sebastien Rannou
** Last update Fri Jul  3 23:26:54 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"

#include <stdlib.h>

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE	/* strdup on linux */
#endif

int
main(int ac, char **av)
{
  ini_t		*file;

  if (ac == 2)
    {
      if ((file = ini_parse_file(av[1])) == NULL)
	{
	  return (ERROR);
	}
    }
  return (SUCCESS);
}
