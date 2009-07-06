/*
** main.c for graoom in /home/rannou_s/Work/graoom/test/lists
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 22:30:39 2009 Sebastien Rannou
** Last update Sat Sep  5 14:41:40 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "tools.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef		_BSD_SOURCE
# define	_BSD_SOURCE	/* strdup on linux */
#endif

typedef struct	test_s
{
  char		*input;
  char		*output;
}		test_t;

/**!
 * @author	rannou_s
 * expected results for trim() function
 */

test_t		tests[] =
  {
    {"Hello world",			"Hello world"},
    {" Hello world",			"Hello world"},
    {"Hello world ",			"Hello world"},
    {"			  Hello world",	"Hello world"},
    {"		Hello world	",	"Hello world"},
    {"",				NULL},
    {"	",				NULL},
    {NULL,				NULL}
  };

int
main(void)
{
  int		i;
  char		buffer[64];
  char		*str;

  for (i = 0; tests[i].input != NULL; i++)
    {
      strcpy(buffer, tests[i].input);
      buffer[strlen(tests[i].input)] = '\0';
      str = trim(buffer);
      if (str == NULL || tests[i].output == NULL)
	{
	  if (tests[i].output != str)
	    {
	      printf("failed on trim of [%s] - output [%s] (expected [%s])\n", 
		     tests[i].input, str, tests[i].output);
	      return (ERROR);
	    }
	}
      else
	{
	  if (strcmp(tests[i].output, str) != 0)
	    {
	      printf("failed on trim of [%s] - output [%s] (expected [%s])\n", 
		     tests[i].input, str, tests[i].output);
	      return (ERROR);
	    }
	}
    }
  return (SUCCESS);
}
