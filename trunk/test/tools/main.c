/*
** main.c for graoom in /home/rannou_s/Work/graoom/test/lists
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 22:30:39 2009 Sebastien Rannou
** Last update Mon Jul  6 20:27:51 2009 aimxhaisse
*/

#include "shortcuts.h"
#include "lists.h"
#include "tools.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct	test_s
{
    char	*input;		/* input to send */
    char	*output;	/* waiting for this output */
}		test_t;

/**!
 * @author	rannou_s
 * expected results for trim() function
 */

test_t		tests[] =
  {
    {"Hello world             ",	"Hello world"},
    {"Hello world	",		"Hello world"},
    {"	Hello world",			"Hello world"},
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
      printf("trim [%s]\noutput [%s]\nexpected [%s]\n\n", 
	     tests[i].input, str, tests[i].output);
      if (str == NULL || tests[i].output == NULL)
      {
	  if (tests[i].output != str)
	      return (ERROR);
      }
      else
	  if (strcmp(tests[i].output, str) != 0)
	      return (ERROR);
    }
  return (SUCCESS);
}
