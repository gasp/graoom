/*
** lists.h for graoom in /home/rannou_s/Work/xoosh/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jun 29 18:21:27 2009 Sebastien Rannou
** Last update Wed Jul  1 22:22:12 2009 Sebastien Rannou
*/

#ifndef	_XOOSH_LIST_H
#define	_XOOSH_LIST_H

typedef struct		listi		/* list informations */
{
  int			nb_elements;	/* number of elements in list */
}			listi_t;

typedef struct		list
{
  struct list		*li_prev;	/* previous element in list */
  struct list		*li_next;	/* next element in list */
  struct listi		*li_info;	/* informations about the list */
  void			*data;		/* allocated pointer */
}			list_t;

int			list_pop(list_t **li_start, list_t *li_element);
int			list_push(list_t **li_start, void *data);
int			list_dump(list_t *li_start);
int			list_display(list_t *li_start, int (*f)(void *));

#endif /* _XOOSH_LIST_H */
