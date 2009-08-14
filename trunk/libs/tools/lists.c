/*
** lists.c for graoom in /home/rannou_s/Work/xoosh/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jun 29 18:11:11 2009 Sebastien Rannou
** Last update Fri Jul 24 16:36:47 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "lists.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**!
 * @author	rannou_s
 * Free a list, allowing to call a specific function for inside void* data
 */

int
list_free(list_t **li_start, void (*f)(void *))
{
  list_t	*cur;
  list_t	*prev;

  if (li_start == NULL || *li_start == NULL)
    return (SUCCESS);
  prev = NULL;
  if ((*li_start)->li_info != NULL)
    {
      free((*li_start)->li_info);
    }
  for (cur = *li_start; cur != NULL; cur = cur->li_next)
    {
      if (cur->data != NULL && f != NULL)
	f(cur->data);
      if (cur->li_prev != NULL)
	{
	  free(cur->li_prev);
	}
      prev = cur;
    }
  if (prev != NULL)
    {
      free(prev);
    }
  *li_start = NULL;
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's pop an element from the list
 * Returns error when invalid parameters given
 */

int
list_pop(list_t **li_start, list_t *li_element)
{
  if (li_element == NULL || li_start == NULL || *li_start == NULL)
    return (ERROR);
  if (li_element->li_prev != NULL)
    li_element->li_prev->li_next = li_element->li_next;
  if (li_element->li_next != NULL)
    li_element->li_next->li_prev = li_element->li_prev;
  if (*li_start == li_element)
    *li_start = li_element->li_next;
  if (li_element->li_info != NULL)
    li_element->li_info->nb_elements--;
  if (*li_start == NULL)
    free(li_element->li_info);
  free(li_element);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Fetch a list_t element from it's data  reference
 */

list_t *
list_fetch(list_t *start, void *data)
{
  list_t	*cur;

  if (start && data)
    {
      for (cur = start; cur != NULL; cur = cur->li_next)
	{
	  if (data == cur->data)
	    {
	      return (data);
	    }
	}
    }
  return (NULL);
}

/**!
 * @author	rannou_s
 * Let's pop an element from the list from it's data reference
 * Returns error when invalid parameters given
 */

int
list_pop_data(list_t **li_start, void *data)
{
  if (data == NULL || li_start == NULL || *li_start == NULL)
    return (ERROR);
  return (list_pop(li_start, list_fetch(*li_start, data)));
}

/**!
 * @author	rannou_s
 * Creates a new listinfo element
 */

static  listi_t	*
list_create_info(void)
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

int
list_display(list_t *li_start, int (*f)(void *))
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

int
list_dump(list_t *li_start)
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

int
list_push(list_t **li_start, void *data)
{
  listi_t	*list_info;
  list_t	*new_elem;

  if (li_start == NULL)
    return (ERROR);
  if ((new_elem = malloc(sizeof(*new_elem))) != NULL)
    {
      memset(new_elem, 0, sizeof(*new_elem));
      if (*li_start == NULL)
	{
	  if ((list_info = list_create_info()) == NULL)
	    {
	      free(new_elem);
	      return (ERROR);
	    }
	  new_elem->li_info = list_info;
	  *li_start = new_elem;
	}
      else
	{
	  (*li_start)->li_prev = new_elem;
	  new_elem->li_next = *li_start;
	  new_elem->li_info = (*li_start)->li_info;
	  *li_start = new_elem;
	}
      new_elem->li_info->nb_elements++;
      new_elem->data = data;
      return (SUCCESS);
    }
  return (ERROR);
}
