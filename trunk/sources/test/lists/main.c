/*
** main.c for battletrantor in /home/rannou_s/Work/graoom/test/lists
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 22:30:39 2009 Sebastien Rannou
** Last update Mon Jul  6 19:09:41 2009 aimxhaisse
*/

#include "shortcuts.h"
#include "lists.h"

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE	/* strdup on linux */
#endif

#include <stdlib.h>
#include <string.h>
#include <time.h>

int
main(int ac, char **av)
{
  list_t	*start = NULL;
  list_t	*current;
  list_t	*tmp;
  int		count;
  int		len;
  int		i;

  for (i = 0; i < ac; i++)
    {
      list_push(&start, strdup(av[i]));
    }
  srand(time(NULL));
  count = 0;
  len = start->li_info->nb_elements;
  if (len != i)
    return (ERROR);
  for (current = start; current != NULL; current = current->li_next)
    {
      tmp = current->li_prev;
      if ((random() % 10) == 0)
	{
	  list_pop(&start, current);
	  current = tmp;
	  count++;
	}
    }
  if ((len - count) != start->li_info->nb_elements)
    return (ERROR);
  return (SUCCESS);
}
