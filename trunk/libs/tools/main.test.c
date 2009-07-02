/*
** main.test.c for graoom in /home/rannou_s/Work/graoom/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  1 23:18:52 2009 Sebastien Rannou
** Last update Wed Jul  1 23:46:07 2009 Sebastien Rannou
*/

#include "shortcuts.h"
#include "tests.h"

#include <stdio.h>

/**!
 * @author	rannou_s
 * Test's main entry
 */

int		main(void)
{
  printf("Starting to test libtools\n");
  test_lists();
  printf("End of test\n");
  return (SUCCESS);
}
