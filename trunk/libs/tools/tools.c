/*
** tools.c for graoom in /home/rannou_s/Work/graoom
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul  3 21:57:07 2009 Sebastien Rannou
** Last update Mon Jul  6 20:39:00 2009 aimxhaisse
*/

#include <stdlib.h>
#include <stdio.h>

#include "shortcuts.h"

/**!
 * @author	rannou_s
 * Trims a string in a destructive way
 * leaving off out-of-string spaces and tabulations
 * No allocation is made there, we modify source
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
      for (i = 0, end = NULL; start[i] != '\0'; i++)
	{
	  if (end == NULL && (start[i] == ' ' || start[i] == '\t'))
	    end = &start[i];
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
 * printf() a message on stderr before diying
 */

void
xerror(char *string)
{
  fprintf(stderr, "%s\n", string);
  fflush(stderr);
  exit(ERROR);
}
