/*
** lists.h for graoom in /home/rannou_s/Work/xoosh/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jun 29 18:21:27 2009 Sebastien Rannou
** Last update Fri Jul 17 18:48:15 2009 sebastien rannou
*/

#ifndef	GRAOOM_LIST_H
#define	GRAOOM_LIST_H

typedef struct		listi_s		/* list informations */
{
  int			nb_elements;	/* number of elements in list */
}			listi_t;

typedef struct		list_s
{
  struct list_s		*li_prev;	/* previous element in list */
  struct list_s		*li_next;	/* next element in list */
  struct listi_s	*li_info;	/* informations about the list */
  void			*data;		/* allocated pointer */
}			list_t;

int			list_free(list_t **li_start, void (*f)(void *));
int			list_pop(list_t **li_start, list_t *li_element);
int			list_pop_data(list_t **li_start, void *data);
int			list_push(list_t **li_start, void *data);
int			list_dump(list_t *li_start);
int			list_display(list_t *li_start, int (*f)(void *));
list_t			*list_fetch(list_t *li_start, void *data);

#endif /* GRAOOM_LIST_H */
