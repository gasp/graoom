/*
** ini.h for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul  2 22:21:41 2009 Sebastien Rannou
** Last update Sat Jul  4 17:03:56 2009 Sebastien Rannou
*/

#ifndef _GRAOOM_INI_H
#define _GRAOOM_INI_H

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

ini_section_t		*ini_retrieve_section(ini_t *ini, char *name);
ini_t			*ini_parse_file(char *name);
char			*ini_retrieve_entry(ini_t *ini, char *section, char *key);
void			ini_free_main(void *ini);

#endif /* _GRAOOM_INI_H */
