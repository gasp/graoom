/*
** main.c for graoom in /home/rannou_s/Work/graoom/test/lists
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 22:30:39 2009 Sebastien Rannou
** Last update Sat Sep  5 18:17:42 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE	/* strdup on linux */
#endif

/**!
 * @author	rannou_s
 * Let's test some ini files
 * usage: ./test [file] [key] [expected]
 */

int
main(int ac, char **av)
{
  ini_t		*file;
  char		*value;

  if (ac == 4)
    {
      if ((file = ini_parse_file(av[1])) == NULL)
	return (ERROR);
      value = ini_retrieve_entry(file, NULL, av[2]);
      if (value == NULL || strcmp(av[3], value) != 0)
	{
	  printf("ini_retrieve_entry failed [%s][%s]\n", value, av[3]);
	  return (ERROR);
	}
      ini_free_main(file);
    }
  return (SUCCESS);
}
