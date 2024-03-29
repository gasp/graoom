/*
** errors.c for battletrantor in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 22:23:24 2009 sebastien rannou
** Last update Mon Oct  5 22:31:15 2009 sebastien rannou
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

typedef struct	error_s		/* structure describing an error */
{
  int		code;		/* associated code */
  char		*fmt;		/* associated message */
  char		behavior;	/* bytes to know what to do when raised */
}		error_t;

static
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

    /* malloc syscall failed */
    {
      .code	=	EC_SYS_MALLOC,
      .fmt	=	"unable to perform malloc (%s)",
      .behavior	=	ERR_T_LOG
    },

    /* strdup failed */
    {
      .code	=	EC_SYS_STRDUP,
      .fmt	=	"unable to perform strdup (%s)",
      .behavior	=	ERR_T_LOG
    },

    /* Unable to load ini file */
    {
      .code	=	EC_INI_FILE,
      .fmt	=	"unable to load ini file (%s)", 
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Unable to find section in ini file */
    {
      .code	=	EC_INI_SEC,
      .fmt	=	"unable to find section (%s) in ini file (%s)", 
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Invalid port given in .ini configuration file */
    {
      .code	=	EC_LOADER_PORT,
      .fmt	=	"invalid port (%d) range: must be between 1 and 65536",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Unknown entry in ini file */
    {
      .code	=	EC_INI_UNKNOWN_ENTRY,
      .fmt	=	"unknown entry (%s) in ini file (%s)", 
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Loader has already loaded this module before */
    {
      .code	=	EC_LOADER_SEV,
      .fmt	=	"module (%s) already loaded in (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* This module wasn't loaded */
    {
      .code	=	EC_LOADER_NULL,
      .fmt	=	"unable to find section (%s) in file (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Unable to load that module */
    {
      .code	=	EC_LOADER_NOK,
      .fmt	=	"unable to load module (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Invalid winx value given  */
    {
      .code	=	EC_LOADER_GFX_WINX,
      .fmt	=	"invalid resolution range for width (%d), must be > 0",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* Invalid winy value given  */
    {
      .code	=	EC_LOADER_GFX_WINY,
      .fmt	=	"invalid resolution range for height (%d), must be > 0",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Invalid resolution ratio  */
    {
      .code	=	EC_LOADER_GFX_RATIO,
      .fmt	=	"invalid ratio resolution (%dx%d), try another resolution",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* Invalid max_fps  */
    {
      .code	=	EC_LOADER_GFX_MAXFPS,
      .fmt	=	"invalid maximum number of FPS (%d), must be > 0",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Color not found  */
    {
      .code	=	EC_LOADER_COLOR_UNKNOWN,
      .fmt	=	"color not found (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Color not found  */
    {
      .code	=	EC_LOADER_EVENT_OVER,
      .fmt	=	"forbidden to overload that event (type = %d code = %d)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Color not found  */
    {
      .code	=	EC_LOADER_INVALID_FOV,
      .fmt	=	"invalid fov (%d), must be > 0",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Unknow association of binding in event section */
    {
      .code	=	EC_LOADER_EVENT_UNK,
      .fmt	=	"invalid key/action given (%s = %s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* SDLNet_ResolveHost failed */
    {
      .code	=	EC_SDL_NET_RESOLVE,
      .fmt	=	"unable to resolve host [%s:%d] (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* SDLNet_TCP_OPEN failed */
    {
      .code	=	EC_SDL_NET_OPEN,
      .fmt	=	"unable to open socket (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* SDL_Init failed */
    {
      .code	=	EC_SDL_INIT,
      .fmt	=	"unable to initialize SDL (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* SDL_SetVideoMode failed */
    {
      .code	=	EC_SDL_SETVIDEO,
      .fmt	=	"unable to create window (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* SDL console initialization failed */
    {
      .code	=	EC_SDL_CONSOLE_INI,
      .fmt	=	"unable to initialize console",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* TTF_Init failed */
    {
      .code	=	EC_SDL_TTF_INIT,
      .fmt	=	"unable to initialize TTF (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* font size is invalid */
    {
      .code	=	EC_SDL_TTF_INVALID_SIZE,
      .fmt	=	"invalid font size (%d) in %s [section %s]",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* TTF_OpenFont failed */
    {
      .code	=	EC_SDL_TTF_OPEN,
      .fmt	=	"unable to load font (%s) (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* TTF render failed */
    {
      .code	=	EC_SDL_TTF_RENDER,
      .fmt	=	"unable to render text (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* SDL_Blit failed */
    {
      .code	=	EC_SDL_BLIT,
      .fmt	=	"unable to blit SDL_Surface (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* TTF font wasn't found */
    {
      .code	=	EC_SDL_TTF_NOT_FOUND,
      .fmt	=	"unable to find that font (%d)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* TTF font wasn't found */
    {
      .code	=	EC_SDL_TTF_GET,
      .fmt	=	"unable to get that font (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* Unable to create a mutex? */
    {
      .code	=	EC_SDL_CREATEMUTEX,
      .fmt	=	"unable to initialize mutex (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* Unable to create thread */
    {
      .code	=	EC_SDL_CREATE_THREAD,
      .fmt	=	"unable to create thread (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },    

    /* Unable to create RGB surface */
    {
      .code	=	EC_SDL_CREATE_SURFACE,
      .fmt	=	"unable to create RGB surface (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },    

    /* Unable to load image */
    {
      .code	=	EC_SDL_LOAD_IMG,
      .fmt	=	"unable to load image [%s] (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },    

    /* Invalid color given */
    {
      .code	=	EC_SDL_INVALID_COLOR,
      .fmt	=	"invalid color range (%d) for %s (%s) : trimming it",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* Unable to convert surface */
    {
      .code	=	EC_GL_CONVERT_TEX,
      .fmt	=	"unable to convert surface to OpenGL texture",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG      
    },

    /* Unable to load model */
    {
      .code	=	EC_MODEL_LOAD,
      .fmt	=	"unable to load mdl file (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Unable to get that texture */
    {
      .code	=	EC_GL_GET_TEXTURE,
      .fmt	=	"unable to get that texture (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* Unable to get that model */
    {
      .code	=	EC_GL_GET_MODEL,
      .fmt	=	"unable to get that model (%s)",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* unable to create that quadric */
    {
      .code	=	EC_GL_NEW_QUAD,
      .fmt	=	"unable to create a new quadric",
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* End of array */
    {
      .code	=	0x0,
      .fmt	=	NULL,
      .behavior	=	0
    }

  };

static
FILE		*global_error_log = NULL;

/**!
 * @author	rannou_s
 * called at exit to close global_error_log
 */

void
error_handler_log_close(void)
{
  fclose(global_error_log);
}

/**!
 * @author	rannou_s
 * Initialize error log file by creating it, do not
 * log if we can't clean it at exit
 */

static void
error_handler_log_init(void)
{
  global_error_log = fopen(ERR_LOG_FILE, FOP_AP);
  if (global_error_log != NULL)
    {
      if (atexit(&error_handler_log_close) != 0)
	{
	  fclose(global_error_log);  
	}
    }
}

/**!
 * @author	rannou_s
 * called when an error is raised and when ERR_T_LOG flag is set
 * We assume ap contains list of arguments to vfprintf and we use it
 * to generate a nice log
 * First time a log is executed, initialize the error log file
 */

#define	ERROR_BUFF_SIZE	512
#define	ERROR_FMT_LOG	"error raised in [%s] on line %d: "

static void
error_handler_log(error_t *err, int line, char *file, va_list ap)
{
  static int	initialized = 0;
  char		*date;
  char		buffer[ERROR_BUFF_SIZE];
  time_t	timer;
  int		len;

  if (err == NULL)
    return;
  if (initialized++ == 0)
    error_handler_log_init();
  if (global_error_log != NULL)
    {
      if ((timer = time(NULL)) > 0)
	{
	  date = ctime(&timer);
	  if (date != NULL && (len = strlen(date)) > 0)
	    {
	      date[len - 1] = '\0';
	      snprintf(buffer, ERROR_BUFF_SIZE, "[%s] ", date);
	      fwrite(buffer, strlen(buffer), 1, global_error_log);
	    }
	}
      snprintf(buffer, ERROR_BUFF_SIZE, ERROR_FMT_LOG, file, line);
      fwrite(buffer, strlen(buffer), 1, global_error_log);
      vsnprintf(buffer, ERROR_BUFF_SIZE, err->fmt, ap);
      fwrite(buffer, strlen(buffer), 1, global_error_log);
      fwrite("\n", 1, 1, global_error_log);
    }
}

/**!
 * @author	rannou_s
 * called when an error is raised and when ERR_T_DISPLAY flag is set
 * We assume ap contains list of arguments to vfprintf
 */

static void
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
 * @todo	- in non-dev mode, it would be great to disable that macros
 *		- do not va_copy when log is not set
 */

void
error_handler(int line, char *file, int code, ...)
{
  error_t	*err;
  va_list	aplog;
  va_list	ap;
  int		i;

  va_start(ap, code);
  va_copy(aplog, ap);
  for (i = 0; global_errors[i].code != 0x0; i++)
    {
      if (global_errors[i].code == code)
	{
	  err = &global_errors[i];
	  if (err->behavior & ERR_T_LOG)
	    error_handler_log(err, line, file, aplog);
	  if (err->behavior & ERR_T_DISPLAY)
	    error_handler_display(err, line, file, ap);
	  if (err->behavior & ERR_T_DIE)
	    {
	      va_end(ap);
	      va_end(aplog);
	      exit(ERROR);
	    }	  
	}
    }
  va_end(aplog);
  va_end(ap);
}
