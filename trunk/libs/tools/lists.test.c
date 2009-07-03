/*
** lists.test.c for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  1 22:59:20 2009 Sebastien Rannou
** Last update Fri Jul  3 20:23:45 2009 Sebastien Rannou
*/

#include "lists.h"
#include "shortcuts.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

/**!
 * @author	rannou_s
 * Little test that opens a file and puts each line of it
 * into a list, sometimes popping elements
 */

#define		FP		"Makefile"
#define		BUFF_SIZE	4096

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE
#endif

int			test_lists_pop(list_t **start)
{
  int			count = 0;
  list_t		*cur;
  list_t		*backup;

  srandom(time(NULL));
  for (cur = *start; cur != NULL; cur = cur->li_next)
    {
      if ((random() % 5) == 0)
	{
	  backup = cur->li_prev;
	  list_pop(start, cur);
	  cur = backup;
	  count++;
	}
    }
  return (SUCCESS);
}

int			test_lists_push(list_t **start)
{
  int			count;
  char			line[BUFF_SIZE];
  FILE			*file;

  file = fopen(FP, FOP_R);
  if (file != NULL)
    {
      count = 0;
      while (fgets(line, BUFF_SIZE, file) != NULL)
	{
	  list_push(start, strdup(line));
	  count++;
	}
      printf("\tlen : %d == %d ?\n", count, (*start)->li_info->nb_elements);
      fclose(file);
    }
  else
    {
      printf("\terror: %s\n", strerror(errno));
    }
  return (ERROR);
}

int			test_lists(void)
{
  list_t		*start = NULL;

  test_lists_push(&start);
  test_lists_pop(&start);
  list_free(&start, &free);
  printf("\tmust be NULL: %p\n", (void *) start);
  return (SUCCESS);
}

