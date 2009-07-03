/*
** ini.c for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul  2 22:20:45 2009 Sebastien Rannou
** Last update Fri Jul  3 08:03:18 2009 Sebastien Rannou
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

/**!
 * @author	rannou_s
 * Frees an allocated section structure
 */

void			ini_free_section(void *ptr)
{
  ini_section_t		*section;

  if (ptr != NULL)
    {
      section = (ini_section_t *) ptr;
      list_free(&section->content_li, NULL);
      free(section->name);
      free(section);
    }
}

/**!
 * @author	rannou_s
 * Frees an allocated ini structure
 */

void			ini_free_main(void *ptr)
{
  ini_t			*ini;

  if (ptr != NULL)
    {
      ini = (ini_t *) ptr;
      free(ini->name);
      free(ini);
    }
}

/**!
 * @author	rannou_s
 * Returns success if it's a new section declaration
 */

static __inline
int			ini_is_section(char *line, int len)
{
  if (*line == '[')
    {
      if (line[len] == ']')
	{
	  return (SUCCESS);
	}
    }
  return (ERROR);
}

/**!
 * @author		rannou_s
 * Creates a new section and push it into ini
 */

static __inline
ini_section_t		*ini_create_section(ini_t *ini, char *line, int len)
{
  ini_section_t		*section;

  if ((section = malloc(sizeof(*section))) != NULL)
    {
      line[len - 1] = '\0';
      line++;
      if (*line != '\0')
	{
	  memset(section, 0, sizeof(*section));
	  section->name = strdup(line);
	  if (list_push(&ini->sections_is, section) == ERROR)
	    {
	      ini_free_section(section);
	      return (NULL);
	    }
	  return (section);
	}
      free(section);
    }
  return (NULL);
}

/**!
 * @author	rannou_s
 * Parses an ini line keeping a static reference to the current section
 */

static __inline
int			ini_parse_line(ini_t *ini, char *line)
{
  int			line_len;
  static ini_section_t	*current_ct = NULL;

  if (ini != NULL && line != NULL)
    {
      line_len = strlen(line);
      if (line_len > 1)
	{
	  line[--line_len] = '\0';
	  if (*line == ';')
	    {
	      return (SUCCESS);
	    }
	  if (ini_is_section(line, line_len) == SUCCESS)
	    {
	      current_ct = ini_create_section(ini, line, line_len);
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

ini_t			*ini_parse_file(char *name)
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
