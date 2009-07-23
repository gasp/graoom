/*
** client.h for graoom in /home/rannou_s/Work/graoom/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 18:18:43 2009 sebastien rannou
** Last update Thu Jul 23 12:27:51 2009 sebastien rannou
*/

#include <SDL/SDL.h>

#include "shortcuts.h"
#include "client.h"
#include "loader.h"
#include "log.h"
#include "log_client.h"

/**!
 * @author	rannou_s
 * main entry of the client
 */

int
main(void)
{
  client_t		client;

  if (loader(&client) == SUCCESS)
    {
      LOG(LOG_LOADED_OK);
      launcher(&client);
    }
  cleaner(&client);
  return (SUCCESS);
}
