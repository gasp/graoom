/*
** tools.c for graoom in /home/rannou_s/Work/graoom
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 21:57:07 2009 Sebastien Rannou
** Last update Sat Sep  5 16:26:15 2009 Sebastien Rannou
*/

#include <stdlib.h>
#include <stdio.h>

#include "shortcuts.h"

/**!
 * @author	rannou_s
 * Trims a string in a destructive way
 * leaving off out-of-string spaces and tabulations
 */

char *
trim(char *source)
{
  int		i;
  char		*start;
  char		*end;

  if (source != NULL && *source != '\0')
    {
      i = 0;
      while (source[i] != '\0' && (source[i] == ' ' || source[i] == '\t'))
	i++;
      if (source[i] == '\0')
	return (NULL);
      start = &source[i];
      for (i = 0, end = NULL; source[i] != '\0'; i++)
	{
	  if (end == NULL && (source[i] == ' ' || source[i] == '\t'))
	    end = &source[i];
	  else
	    end = NULL;
	}
      if (end != NULL && *end != '\0')
	*end = '\0';
      return (start);
    }
  return (NULL);
}

/**!
 * @author	rannou_s
 * printf a message on stderr before diying
 */

void
xerror(char *string)
{
  fprintf(stderr, "%s\n", string);
  fflush(stderr);
  exit(ERROR);
}
