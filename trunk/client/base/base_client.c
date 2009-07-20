/*
** client.h for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 18:18:43 2009 sebastien rannou
** Last update Mon Jul 20 20:33:09 2009 sebastien rannou
*/

#include "shortcuts.h"
#include "client.h"
#include "loader.h"

/**!
 * @author	rannou_s
 * main entry of the client, let's load each module and start
 * the thread's dispatcher
 */

int
main(void)
{
  client_t		client;

  if (loader(&client) == SUCCESS)
    {
      LOG("Launching the server");
    }
  cleaner(&client);
  return (SUCCESS);
}
