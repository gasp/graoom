/*
** errors.h for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 20:27:27 2009 sebastien rannou
** Last update Wed Jul  8 23:26:08 2009 sebastien rannou
*/

#ifndef GRAOOM_ERRORS_H
#define	GRAOOM_ERRORS_H

typedef struct		error_s		/* structure describing an error */
{
  int			code;		/* associated code */
  char			*msg;		/* associated message */
  char			behavior;	/* bytes to know what to do when raised */
}			error_t;

/**!
 * @author	rannou_s
 * flags related to type_b
 */

#define	ERR_T_DISPLAY		0x01	/* 0000 0001 */
#define	ERR_T_LOG		0x02	/* 0000 0010 */
#define	ERR_T_DIE		0x04	/* 0000 1000 */

/**!
 * @author	rannou_s
 * error codes defines
 */

#define	EC_PRIM_INI_FILE	0x01

#endif /* GRAOOM_ERRORS_H */
