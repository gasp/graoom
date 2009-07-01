/*
** lists.c for graoom in /home/rannou_s/Work/xoosh/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jun 29 18:11:11 2009 Sebastien Rannou
** Last update Wed Jul  1 22:22:05 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "lists.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**!
 * @author	rannou_s
 * Let's pop an element from the list
 * Returns error when invalid parameters given
 */

int		list_pop(list_t **li_start, list_t *li_element)
{
  if (li_element == NULL || li_start == NULL || *li_start == NULL)
    return (ERROR);
  if (li_element->li_prev != NULL)
    {
      li_element->li_prev->li_next = li_element->li_next;
    }
  else
    {
      /* it means this the first element in the list */
      *li_start = li_element->li_next;
    }
  if (li_element->li_info != NULL)
    {
      li_element->li_info->nb_elements--;
    }
  free(li_element);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Creates a new listinfo element
 */

static __inline
listi_t		*list_create_info(void)
{
  listi_t	*list_info;

  if ((list_info = malloc(sizeof(*list_info))) != NULL)
    {
      memset(list_info, 0, sizeof(*list_info));
      return (list_info);
    }
  return (NULL);
}

/**!
 * @author	rannou_s
 * Prints informations about a list and allows a 
 * function to display more informations about element's data
 * Can be usefull to debug
 */

int		list_display(list_t *li_start, int (*f)(void *))
{
  int		i;
  list_t	*li_cur;

  if (li_start != NULL)
    {
      printf("dumping list [addr = %p] (%d elements)\n", 
	     (void*) li_start, 
	     li_start->li_info->nb_elements);
      i = 0;
      for (li_cur = li_start; li_cur != NULL; li_cur = li_cur->li_next)
	{
	  printf("\t#%d\t[addr = %p]\n", i, li_cur->data);
	  if (f != NULL)
	    {
	      f(li_cur->data);
	    }
	  i++;
	}
      return (SUCCESS);      
    }
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Prints informations about a list
 */

int		list_dump(list_t *li_start)
{
  int		i;
  list_t	*li_cur;

  if (li_start != NULL && li_start->li_info != NULL)
    {
      printf("dumping list [addr = %p] (%d elements)\n", 
	     (void *) li_start, 
	     li_start->li_info->nb_elements);
      i = 0;
      for (li_cur = li_start; li_cur != NULL; li_cur = li_cur->li_next)
	{
	  printf("\t#%d\t[addr = %p]\n", i, li_cur->data);
	  i++;
	}
      return (SUCCESS);
    }
  return (ERROR);
}

/**!
 * @author	rannou_s
 * Let's push a new element in the list
 * Returns error when unable perform a malloc 
 * or when invalid parameters given
 */

int		list_push(list_t **li_start, void *data)
{
  listi_t	*list_info;
  list_t	*new_elem;

  if (li_start == NULL)
    return (ERROR);
  if ((new_elem = malloc(sizeof(new_elem))) != NULL)
    {
      memset(new_elem, 0, sizeof(*new_elem));
      if (*li_start == NULL)
	{
	  /* First element in the list */
	  if ((list_info = list_create_info()) != NULL)
	    {
	      free(new_elem);
	      return (ERROR);
	    }
	  *li_start = new_elem;
	}
      else
	{
	  /* List is not empty */
	  new_elem->li_next = *li_start;
	  new_elem->li_info = (*li_start)->li_info;
	  *li_start = new_elem;
	}
      if (new_elem->li_info != NULL)
	{
	  new_elem->li_info->nb_elements++;
	}
      new_elem->data = data;
      return (SUCCESS);
    }
  return (ERROR);
}
