/*
** errors.h for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 20:27:27 2009 sebastien rannou
** Last update Fri Jul 10 10:59:19 2009 sebastien rannou
*/

#ifndef GRAOOM_ERRORS_H
#define	GRAOOM_ERRORS_H

/**!
 * @author	rannou_s
 * error file where logs are writtent
 */

#define	ERR_LOG_FILE	"error.log"

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
#define			EC_INI_FILE		0x03
#define			EC_INI_SEC		0x04
#define			EC_INI_UNKNOWN_ENTRY	0x05

void			error_handler(int line, char *file, int code, ...);

/**!
 * @author	rannou_s
 * Maccro to make easier tracing of errors in development mode
 * oh my god we can do varargs inside maccros
 */

#define	ERR_RAISE(...)	error_handler(__LINE__, __FILE__, __VA_ARGS__)

#endif /* GRAOOM_ERRORS_H */
