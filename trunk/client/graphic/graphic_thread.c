/*
** event_thread.c for graoom in /home/rannou_s/Work/graoom/client/event
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 01:25:00 2009 sebastien rannou
** Last update Wed Aug  5 02:15:59 2009 
*/

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "lists.h"
#include "coor.h"
#include "font.h"
#include "client.h"
#include "shortcuts.h"
#include "errors.h"
#include "graphic.h"
#include "threads.h"
#include "log.h"

#define	TIME	(&client->time)

/**!
 * @author	rannou_s
 * more of the calculs are done in this function
 */

static __inline int
graphic_thread_computes(client_t *client, graphic_t *graphic)
{
  if (client == NULL || graphic == NULL)
    {
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  graphic_3d_draw(client, graphic);
  graphic_2d_draw(client, graphic);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's sleep to let other threads having some time to lock/unlock
 * client's mutex.
 */

#define	MIN_SLEEP_SLOW	1

static __inline int
graphic_thread_sleep(client_t *client)
{
  int		time_to_sleep;
  int		time_elapsed;

  if (client == NULL)
    {
      threads_leave(client);
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  TIME->loop_end = SDL_GetTicks();
  time_elapsed = TIME->loop_end - TIME->loop_start;
  time_to_sleep = (1000 / TIME->max_fps) - time_elapsed;
  if (time_to_sleep <= 0)
    {
      /**!
       * Application is slow (not reaching max_fps) 
       * Would be great to make a benchmark to know how to sleep()
       * sleep() is an obligation as we have to let other threads a part
       * of control ... so? let's choose an arbitrary sleep value :(
       *
       * This value is 1 (sdl doc) // Thanks to Talus
       */
      SDL_Delay(MIN_SLEEP_SLOW);
    }
  else
    {
      SDL_Delay((Uint32) time_to_sleep);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Refreshes current_fps & loop_start value
 * Also try to estimate virtual_max_fps, which is the maximum number
 * of FPS that the graphic thread can display, it's different than the maximum
 * num of FPS of the application, as it depends on other threads and on time
 * used to lock/unlock access to client's structure.
 */

static __inline int
graphic_thread_time_refresh(client_t *client)
{
  Uint32		elapsed_time;
  int			virtual_max_fps;
  int			current_fps;

  if (client == NULL)
    {
      threads_leave(client);
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  if (client->time.loop_end != 0)	/* First frame == 0 */
    {
      elapsed_time = TIME->loop_end - TIME->loop_start;
      if (elapsed_time == 0)		/* What an amazing computer */
	elapsed_time++;
      virtual_max_fps = (int) ((Uint32) 1000 / elapsed_time);
      current_fps = (virtual_max_fps > TIME->max_fps) ?
	            (TIME->max_fps) : (virtual_max_fps);
      TIME->current_fps = current_fps;
      TIME->virtual_max_fps = virtual_max_fps;
      TIME->loop_start = SDL_GetTicks();
    }
  client->time.loop_start = SDL_GetTicks();
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * main loop of graphic's thread
 */

int
graphic_thread(client_thread_t *holder)
{
  if (holder == NULL)
    {
      threads_leave(holder->client);
      ERR_RAISE(EC_NULL_PTR_DIE);
      return (ERROR);
    }
  SDL_mutexP(holder->client->mutex);
  while (holder->client->state == CLIENT_STATE_ON)
    {
      graphic_thread_time_refresh(holder->client);
      {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	graphic_thread_computes(holder->client, holder->data);
	SDL_mutexV(holder->client->mutex);
	glFlush();
	SDL_GL_SwapBuffers();
      }
      graphic_thread_sleep(holder->client);
      SDL_mutexP(holder->client->mutex);
    }
  SDL_mutexV(holder->client->mutex);
  free(holder);
  return (SUCCESS);
}
