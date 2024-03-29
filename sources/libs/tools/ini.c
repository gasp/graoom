/*
** ini.c for battletrantor in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul  2 22:20:45 2009 Sebastien Rannou
** Last update Sat Jul 25 17:37:16 2009 sebastien rannou
*/

/**!
 * @author	rannou_s
 *
 * A simple .ini file parser
 *
 * As there is no RFC or references about .ini files, this parser is limited
 * to some basic features that are used by battletrantor:
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
 * it'll be modified according to battletrantor's needs and 
 * can broke compatibility at any time.
 */

#include "shortcuts.h"
#include "lists.h"
#include "ini.h"
#include "tools.h"

#ifndef			_BSD_SOURCE
# define		_BSD_SOURCE	/* for strdup() on linux */
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define			BUFF_READ_SIZE	1024

static  void
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

static  void
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

static 	int
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

static  ini_section_t *
ini_create_section(ini_t *ini, char *line, int len)
{
  ini_section_t		*section;

  if ((section = ini_retrieve_section(ini, line)) != NULL)
    return (section);
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
 * Let's push the new allocated content in its associated lists
 * If malloc fails in push's functions, we remove it
 * /!\ section == NULL is not a bug /!\
 */

static 	int
ini_create_content_push(ini_t *ini, ini_section_t *section, 
			ini_content_t *content)
{
    if (ini == NULL || content == NULL)
      return (ERROR);
    if (section != NULL)
      {
	if (list_push(&section->content_li, content) == ERROR)
	  {
	    ini_free_content((void *) content);
	    return (ERROR);
	  }
      }
    if (list_push(&ini->content_ic, content) == ERROR)
      {
	list_pop_data(&section->content_li, content);
	ini_free_content((void *) content);
	return (ERROR);
      }
    return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Creates a new content and push it into ini
 * Do not accept a line full of blanks or an invalid one (missing key)
 * but accept missing values (set to NULL then)
 */

static 	int
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
      if ((content = malloc(sizeof(*content))) == NULL)
	return (ERROR);
      memset(content, 0, sizeof(*content));
      if ((content->name = strdup(key)) != NULL)
	{
	  value = trim(tmp + sizeof(*tmp));
	  if (value != NULL && strlen(value) > 0)
	    content->value = strdup(value);
	  content->section_is = section;
	  return (ini_create_content_push(ini, section, content));
	}
      ini_free_content((void *) content);
    }
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Parses an ini line keeping a static reference to the current section
 */

static 	int
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
	      if (!(current_ct = ini_create_section(ini, line, line_len)))
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

  if (ini != NULL && key != NULL)
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

/**!
 * @author	rannou_s
 * Returns a value from a section according to its key
 * it nothing was found, let's return NULL
 */

char *
ini_retrieve_entry_from_section(ini_section_t *section, char *key)
{
  list_t	*cur;

  if (section != NULL && key != NULL)
    {
      for (cur = section->content_li; cur != NULL; cur = cur->li_next)
	{
	  if (strcmp(((ini_content_t *) cur->data)->name, key) == 0)
	    {
	      return (((ini_content_t *) cur->data)->value);
	    }
	}
    }
  return (NULL);
}

/**!
 * @author	rannou_s
 * Returns a	1 if the entry is set to ON
 *		0 if the entry is set to OFF
 *		-1 on error
 */

#define		BOOL_ON		"on"
#define		BOOL_OFF	"off"

int
ini_retrieve_entry_from_section_bool(ini_section_t *section, char *key)
{
  char			*value;

  if (section == NULL || key == NULL)
    {
      return (ERROR);
    }
  if ((value = ini_retrieve_entry_from_section(section, key)) == NULL)
    {
      return (ERROR);
    }
  if (strcasecmp(BOOL_ON, value) == 0)
    {
      return (1);
    }
  if (strcasecmp(BOOL_OFF, value) == 0)
    {
      return (0);
    }
  return (ERROR);
}
