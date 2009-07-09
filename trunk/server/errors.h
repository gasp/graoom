/*
** errors.h for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 20:27:27 2009 sebastien rannou
** Last update Fri Jul 10 00:29:04 2009 sebastien rannou
*/

#ifndef GRAOOM_ERRORS_H
#define	GRAOOM_ERRORS_H

/**!
 * @author	rannou_s
 * error file where logs are writtent
 */

#define	ERR_LOG_FILE	"error.log"

typedef struct		error_s		/* structure describing an error */
{
  int			code;		/* associated code */
  char			*fmt;		/* associated message */
  char			behavior;	/* bytes to know what to do when raised */
}			error_t;

/**!
 * @author	rannou_s
 * flags related to type_b
 */

#define			ERR_T_DISPLAY		0x01	/* 0000 0001 */
#define			ERR_T_LOG		0x02	/* 0000 0010 */
#define			ERR_T_DIE		0x04	/* 0000 1000 */

/**!
 * @author	rannou_s
 * error codes defines
 */

#define			EC_NULL_PTR		0x01
#define			EC_NULL_PTR_DIE		0x02
#define			EC_PRIM_INI_FILE	0x03

void			error_handler(int code, int line, char *file, ...);

/**!
 * @author	rannou_s
 * Maccro to make easier tracing of errors in development mode
 * oh my god we can do varargs inside maccros
 */

#define	ERR_RAISE(c, ...) error_handler(c, __LINE__, __FILE__, ##__VA_ARGS__)

#endif /* GRAOOM_ERRORS_H */
