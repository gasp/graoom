/*
** main.c for graoom in /home/rannou_s/Work/graoom/test/lists
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 22:30:39 2009 Sebastien Rannou
** Last update Sat Jul  4 17:00:05 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE	/* strdup on linux */
#endif

int
main(int ac, char **av)
{
  ini_t		*file;
  char		*value;

  if (ac == 2)
    {
      if ((file = ini_parse_file(av[1])) == NULL)
	{
	  return (ERROR);
	}
      value = ini_retrieve_entry(file, "SQL", "sql.safe_mode");
      printf("Existing value (sql safe mode): [%s]\n", value);
      value = ini_retrieve_entry(file, "??", "UNKNOWN");
      printf("Non existing value: [%s]\n", value);
      ini_free_main(file);
    }
  return (SUCCESS);
}
