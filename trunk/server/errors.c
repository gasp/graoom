/*
** errors.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 22:23:24 2009 sebastien rannou
** Last update Fri Jul 10 00:09:46 2009 sebastien rannou
*/

#include "errors.h"
#include "shortcuts.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

/**!
 * @author	rannou_s
 * This file contains errors informations allowing them to have a different
 * behavior when raised. Each error has a code and an additionnal string 
 * describing it. There's also an additional flag which will determine 
 * what we should do when raised, this flag can combine:
 *	- ERR_T_DISPLAY	: outputs string on stderr
 *	- ERR_T_LOG	: log it to a file
 *	- ERR_T_DIE	: leave the program
 */

error_t		global_errors[] =
  {

    /* NULL pointer found (expected) */
    {
      .code	=	EC_NULL_PTR,
      .fmt	=	"NULL pointer",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* NULL pointer found (unexpected) */
    {
      .code	=	EC_NULL_PTR_DIE,
      .fmt	=	"NULL pointer (critical)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG | ERR_T_DIE
    },

    /* Unable to load primary ini file */
    {
      .code	=	EC_PRIM_INI_FILE,
      .fmt	=	"unable to load primary ini file (%s)", 
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* End of array */
    {
      .code	=	0x0,
      .fmt	=	NULL,
      .behavior	=	0
    }

  };

FILE	*global_error_log = NULL;

void
error_handler_log_close(void)
{
  fclose(global_error_log);
}

/**!
 * @author	rannou_s
 * called when an error is raised and when ERR_T_LOG flag is set
 * We assume ap contains list of arguments to vfprintf and we use it
 * to generate a nice log
 * First time a log is executed, we open a error.log file with a feed
 * that is registered to be closed when leaving the soft
 */

#define	ERROR_BUFF_SIZE	512
#define	ERROR_FMT_LOG	"error raised in [%s] on line %d: "

static __inline void
error_handler_log(error_t *err, int line, char *file, va_list ap)
{
  static int	initialized = 0;
  char		*date;
  char		buffer[ERROR_BUFF_SIZE];
  time_t	timer;

  if (err == NULL)
    return;
  if (initialized == 0)
    {
      initialized++;
      global_error_log = fopen(FOP_AP, ERR_LOG_FILE);
      if (global_error_log != NULL)
	{
	  if (atexit(&error_handler_log_close) != 0)
	    {
	      fclose(global_error_log);
	    }
	}
    }
  if (global_error_log != NULL)
    {
      if ((timer = time(NULL)) > 0)
	{
	  date = ctime(&timer);
	  snprintf(buffer, ERROR_BUFF_SIZE, "[%s] ", date);
	  fwrite(buffer, strlen(buffer), 1, global_error_log);
	}
      snprintf(buffer, ERROR_BUFF_SIZE, ERROR_FMT_LOG, file, line);
      fwrite(buffer, strlen(buffer), 1, global_error_log);
      snprintf(buffer, ERROR_BUFF_SIZE, err->fmt, ap);
      fwrite(buffer, strlen(buffer), 1, global_error_log);
      fwrite("\n", 1, 1, global_error_log);
    }
}

/**!
 * @author	rannou_s
 * called when an error is raised and when ERR_T_DISPLAY flag is set
 * We assume ap contains list of arguments to vfprintf
 */

static __inline void
error_handler_display(error_t *err, int line, char *file, va_list ap)
{
  if (err != NULL)
    {
      fprintf(stderr, ERROR_FMT_LOG, file, line);
      vfprintf(stderr, err->fmt, ap);
      fprintf(stderr, "\n");
      fflush(stderr);
    }
}

/**!
 * @author	rannou_s
 * Main entry on errors, this is called through and overloading
 * macro so as to get line and file where error occurs
 * @todo	in non-dev mode, it would be great to disable that macros, or to
 * change their behavior so as to have something comprehensible to users
 */

void
error_handler(int code, int line, char *file, ...)
{
  error_t	*err;
  va_list	ap;
  int		i;

  va_start(ap, file);
  for (i = 0; global_errors[i].code != 0x0; i++)
    {
      if (global_errors[i].code == code)
	{
	  err = &global_errors[i];
	  if (err->behavior | ERR_T_DISPLAY)
	    error_handler_display(err, line, file, ap);
	  if (err->behavior | ERR_T_LOG)
	    error_handler_log(err, line, file, ap);
	  if (err->behavior | ERR_T_DIE)
	    {
	      va_end(ap);
	      exit(ERROR);
	    }	  
	}
    }
  va_end(ap);
}
