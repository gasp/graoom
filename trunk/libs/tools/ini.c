/*
** ini.c for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul  2 22:20:45 2009 Sebastien Rannou
** Last update Thu Jul  2 23:54:11 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef			_BSD_SOURCE
# define		_BSD_SOURCE	/* for strdup() on linux */
#endif

#define			BUFF_READ_SIZE	1024
#define			INI_COMMENT	';'

/**!
 * @author	rannou_s
 * Frees an allocated ini structure
 */

void			ini_free_main(ini_t *ini)
{
  if (ini != NULL)
    {
      free(ini->name);
      free(ini);
    }
}

/**!
 * @author	rannou_s
 * Parses an ini line keeping a static reference to the current section
 */

int			ini_parse_line(ini_t *ini, char *line)
{
  int			line_len;
  static ini_content_t	*current_ct = NULL;

  if (ini != NULL && line != NULL)
    {
      line_len = strlen(line);
      if (line_len > 0)
	{
	  if (*line == INI_COMMENT)
	    {
	      return (SUCCESS);
	    }
	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Parses an ini file and returns a structure describing its content
 */

ini_t			*ini_parse_file(const char *name)
{
  char			buffer[BUFF_READ_SIZE];
  ini_t			*ini;
  FILE			*file;

  if ((ini = malloc(sizeof(*ini))) != NULL)
    {
      memset(ini, 0, sizeof(*ini));
      if ((file = fopen(name, FOP_R)) == NULL)
	{
	  ini_free_main(ini);
	  return (NULL);
	}
      ini->name = strdup(name);
      while (fgets(buffer, BUFF_READ_SIZE, file) != NULL)
	{
	  if (ini_parse_line(ini, buffer) == ERROR)
	    {
	      ini_free_main(ini);
	      fclose(file);
	      return (NULL);
	    }
	}
      fclose(file);
    }
  return (NULL);
}
