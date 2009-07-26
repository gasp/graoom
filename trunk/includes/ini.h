/*
** ini.h for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul  2 22:21:41 2009 Sebastien Rannou
** Last update Sat Jul 25 12:49:09 2009 sebastien rannou
*/

#ifndef GRAOOM_INI_H
#define GRAOOM_INI_H

typedef struct		ini_section_s	/* content of a section */
{
  char			*name;		/* section's name */
  list_t		*content_li;	/* list of content (ini_content_t *) */
  int			content_num;	/* number of contents */
}			ini_section_t;

typedef struct		ini_content_s	/* content of a parameter */
{
  char			*name;		/* parameter's name */
  char			*value;		/* parameter's value */
  ini_section_t		*section_is;	/* hash on section's content */
}			ini_content_t;

typedef struct		ini_s		/* content of a .ini file */
{
  char			*name;		/* file's name */
  list_t		*sections_is;	/* list of sections */
  list_t		*content_ic;	/* list of contents */
  int			section_num;	/* number of sections */
  int			content_num;	/* number of contents */
}			ini_t;

ini_section_t *	/* returns a section from its name */
ini_retrieve_section(ini_t *ini, char *name);

ini_t *		/* primary function, parses an ini file */
ini_parse_file(char *name);

char *		/* returns an entry related by its section and its key */
ini_retrieve_entry(ini_t *ini, char *section, char *key);

char *		/* returns an entry from its section */
ini_retrieve_entry_from_section(ini_section_t *section, char *key);

int		/* returns 1 if ON, 0 if OFF, -1 on error */
ini_retrieve_entry_from_section_bool(ini_section_t *section, char *key);

void		/* free everything that's was loaded from a file */
ini_free_main(void *ini);

#endif /* GRAOOM_INI_H */
