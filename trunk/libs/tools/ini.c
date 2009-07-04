/*
** ini.c for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul  2 22:20:45 2009 Sebastien Rannou
** Last update Sat Jul  4 17:14:06 2009 Sebastien Rannou
*/

/**!
 * @author	rannou_s
 *
 * A simple .ini file parser
 *
 * As there is no RFC or references about .ini files, this parser is limited
 * to some basic features that are used by graoom:
 * -	comments start with ;
 * -	sections are on the form [name]
 * -	key/values are defined by key = value
 *
 * A quick note about key/values, they are trimmed from any 
 * out-bordering spaces or tabulations, that means that:
 *
 * key = here is a value			| Are exactly
 * key     =		here is a value		| the same
 *
 * key = here is    a value			| Are not
 * key = here is a value			| the same
 *
 * The same goes for section's declarations
 *
 * key/values without sections are allowed but they must be placed before any
 * section declaration as they'll inherit of it
 *
 * You can use it elsewhere but take care of its evolution, 
 * it'll be modified according to graoom's needs and 
 * can broke compatibility at any time.
 */

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"
#include "tools.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef			_BSD_SOURCE
# define		_BSD_SOURCE	/* for strdup() on linux */
#endif

#define			BUFF_READ_SIZE	1024

static __inline void
ini_free_content(void *ptr)
{
  ini_content_t		*content;

  if (ptr != NULL)
    {
      content = (ini_content_t *) ptr;
      free(content->name);
      free(content->value);
      free(content);
    }
}

/**!
 * @author	rannou_s
 * Frees an allocated section structure
 */

static __inline void
ini_free_section(void *ptr)
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

void
ini_free_main(void *ptr)
{
  ini_t			*ini;

  if (ptr != NULL)
    {
      ini = (ini_t *) ptr;
      free(ini->name);
      list_free(&ini->sections_is, ini_free_section);
      list_free(&ini->content_ic, ini_free_content);
      free(ini);
    }
}

/**!
 * @author	rannou_s
 * Returns success if it's a new section declaration
 */

static __inline	int
ini_is_section(char *line, int len)
{
  if (*line == '[')
    if (line[len - 1] == ']')
      return (SUCCESS);
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Creates a new section and push it into ini
 */

static __inline ini_section_t *
ini_create_section(ini_t *ini, char *line, int len)
{
  ini_section_t		*section;

  if ((section = malloc(sizeof(*section))) != NULL)
    {
      line[len - 1] = '\0';
      line++;
      if (*line != '\0')
	{
	  if ((section = ini_retrieve_section(ini, line)) != NULL)
	    {
	      return (section);
	    }
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
 * Creates a new content and push it into ini
 * Do not accept a line full of blanks or an invalid one (missing key
 * or missing value)
 */

static __inline	int
ini_create_content(ini_t *ini, char *line, ini_section_t *section)
{
  char			*key;
  char			*value;
  char			*tmp;
  ini_content_t		*content;

  if (ini == NULL || line == NULL)
    return (ERROR);
  if ((tmp = strchr(line, '=')) == NULL)
    return (ERROR);
  *tmp = '\0';
  if ((key = trim(line)) != NULL)
    {
      if ((content = malloc(sizeof(*content))) != NULL)
	{
	  memset(content, 0, sizeof(*content));
	  if ((content->name = strdup(key)) != NULL)
	    {
	      value = trim(tmp + sizeof(*tmp));
	      /* We allow a value to be NULL (memset is default then) */
	      if (value != NULL && strlen(value) > 0)
		content->value = strdup(key);
	      content->section_is = section;
	      if (list_push(&section->content_li, content) == ERROR)
		{
		  ini_free_content((void *) content);
		  return (ERROR);
		}
	      return (SUCCESS);
	    }
	  ini_free_content((void *) content);
	}
    }
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Parses an ini line keeping a static reference to the current section
 */

static __inline	int
ini_parse_line(ini_t *ini, char *line)
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
	    return (SUCCESS);
	  if (ini_is_section(line, line_len) == SUCCESS)
	    {
	      if ((current_ct = ini_create_section(ini, line, line_len)) == NULL)
		return (ERROR);
	      return (SUCCESS);
	    }
	  else
	    return (ini_create_content(ini, line, current_ct));

	}
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Parses an ini file and returns a structure describing its content
 */

ini_t *
ini_parse_file(char *name)
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
      return (ini);
    }
  return (NULL);
}

/**!
 * @author	rannou_s
 * returns the section according to its name
 */

ini_section_t *
ini_retrieve_section(ini_t *ini, char *name)
{
  list_t	*cur;

  if (ini != NULL && name != NULL)
    {
      for (cur = ini->sections_is; cur != NULL; cur = cur->li_next)
	{	  
	  if (strcmp(name, ((ini_section_t *) cur->data)->name) == 0)
	    {
	      return ((ini_section_t *) cur->data);
	    }
	}
    }
  return (NULL);
}

/**!
 * @author	rannou_s
 * returns the first occurence of name found in section
 * if section == NULL, let's look for it in primary list
 */

char *
ini_retrieve_entry(ini_t *ini, char *section, char *key)
{
  ini_section_t	*sec;
  list_t	*start;
  list_t	*cur;

  if (ini != NULL && key != NULL && section != NULL)
    {
      if ((sec = ini_retrieve_section(ini, section)) != NULL)
	start = sec->content_li;
      else
	start = ini->content_ic;
      for (cur = start; cur != NULL; cur = cur->li_next)
	{
	  if (strcmp(key, ((ini_content_t *) cur->data)->name) == 0)
	    {
	      return (((ini_content_t *) cur->data)->value);
	    }
	}
    }
  return (NULL);
}
