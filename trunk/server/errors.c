/*
** errors.c for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 22:23:24 2009 sebastien rannou
** Last update Wed Jul  8 23:02:54 2009 sebastien rannou
*/

#include "errors.h"

#include <stdlib.h>

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

    /* Unable to load primary ini file */
    {
      .code	=	EC_PRIM_INI_FILE,
      .msg	=	"unable to load primary ini file (%s)", 
      .behavior	=	ERR_T_DISPLAY | ERR_T_LOG
    },

    /* End of array */
    {
      .code	=	0x0,
      .msg	=	NULL,
      .behavior	=	0
    }

  };
