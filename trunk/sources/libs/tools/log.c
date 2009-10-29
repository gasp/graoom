/*
** log.c for battletrantor in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 22:06:09 2009 Sebastien Rannou
** Last update Tue Jul 21 01:15:22 2009 sebastien rannou
*/

#include "shortcuts.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/**!
 * @author	rannou_s
 * Prints a message on stdout with a nice prompt
 * In dev mode, also indicates line and file where it occurs
 */

int
log_print(int line, char *file, char *prefix, char *fmt, ...)
{
  va_list	ap;

  if (file != NULL)
    {
      if (prefix != NULL)
	{
	  fprintf(stdout, "%s", prefix);
	}
      fprintf(stdout, "[%s - line %d] ", file, line);
      va_start(ap, fmt);
      vfprintf(stdout, fmt, ap);
      va_end(ap);
      fprintf(stdout, "\n");
      fflush(stdout);
    }
  return (SUCCESS);
}
