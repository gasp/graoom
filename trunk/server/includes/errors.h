/*
** errors.h for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 20:27:27 2009 sebastien rannou
** Last update Thu Aug  6 00:06:10 2009 
*/

#ifndef GRAOOM_ERRORS_H
#define	GRAOOM_ERRORS_H

/**!
 * @author	rannou_s
 * error file where logs are written
 */

#define	ERR_LOG_FILE	"error.log"

/**!
 * @author	rannou_s
 * flags related to type_b
 */

#define			ERR_T_DISPLAY		0x01	/* 0000 0001 */
#define			ERR_T_LOG		0x02	/* 0000 0010 */
#define			ERR_T_DIE		0x04	/* 0000 0100 */

/**!
 * @author	rannou_s
 * error codes defines
 */

#define			EC_NULL_PTR		1
#define			EC_NULL_PTR_DIE		2

#define			EC_SYS_CLOSE		3
#define			EC_SYS_SELECT		4
#define			EC_SYS_FD		5
#define			EC_SYS_ACCEPT		6
#define			EC_SYS_FCNTL		7
#define			EC_SYS_MALLOC		8
#define			EC_SYS_INET_NTOA	9
#define			EC_SYS_READ		10
#define			EC_SYS_WRITE		11
#define			EC_SYS_SEND		12
#define			EC_SYS_SEND_ZERO	13

#define			EC_INI_FILE		101
#define			EC_INI_SEC		102
#define			EC_INI_UNKNOWN_ENTRY	103

#define			EC_LOADER_PORT		202
#define			EC_LOADER_SEV		203
#define			EC_LOADER_NULL		204
#define			EC_LOADER_MAX		205

#define			EC_NETWORK_SOCK		301
#define			EC_NETWORK_MAX		302
#define			EC_NETWORK_NODATA	303

#define			EC_GAME_MAPLEN		401

void	/* logs a message, see errors.c for more information */
error_handler(int line, char *file, int code, ...);

/**!
 * @author	rannou_s
 * Maccro to make easier tracing of errors in development mode
 * oh my god we can do varargs inside maccros
 */

#define	ERR_RAISE(...)	error_handler(__LINE__, __FILE__, __VA_ARGS__)

#endif /* GRAOOM_ERRORS_H */
