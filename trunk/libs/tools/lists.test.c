/*
** lists.test.c for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  1 22:59:20 2009 Sebastien Rannou
** Last update Wed Jul  1 23:35:38 2009 Sebastien Rannou
*/

#include "lists.h"
#include "shortcuts.h"

#include <stdio.h>

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

int			test_lists(void)
{
  FILE			*file;
  char			line[BUFF_SIZE];
  list_t		*start = NULL;

  file = fopen(FP, FOP_R);
  if (file != NULL)
    {
      while (fgets(line, BUFF_SIZE, file) != NULL)
	{
	  list_push(&start, strdup(line));
	}
      list_dump(line);
      fclose(file);
    }
  return (SUCCESS);
}

