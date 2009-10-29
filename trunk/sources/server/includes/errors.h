/*
** errors.h for battletrantor in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 20:27:27 2009 sebastien rannou
** Last update Thu Oct  1 17:29:26 2009 sebastien rannou
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

enum ERRORS
  {
    EC_VOID,
    EC_NULL_PTR,
    EC_NULL_PTR_DIE,

    EC_SYS_CLOSE,
    EC_SYS_SELECT,
    EC_SYS_FD,
    EC_SYS_ACCEPT,
    EC_SYS_FCNTL,
    EC_SYS_MALLOC,
    EC_SYS_INET_NTOA,
    EC_SYS_READ,
    EC_SYS_WRITE,
    EC_SYS_SEND,
    EC_SYS_SEND_ZERO,
    
    EC_INI_FILE,
    EC_INI_SEC,
    EC_INI_UNKNOWN_ENTRY,

    EC_LOADER_PORT,
    EC_LOADER_SEV,
    EC_LOADER_NULL,
    EC_LOADER_MAX,

    EC_NETWORK_SOCK,
    EC_NETWORK_MAX,
    EC_NETWORK_NODATA,

    EC_GAME_MAPLEN
  };

void	/* logs a message, see errors.c for more information */
error_handler(int line, char *file, int code, ...);

/**!
 * @author	rannou_s
 * Maccro to make easier tracing of errors in development mode
 * oh my god we can do varargs inside maccros
 */

#define	ERR_RAISE(...)	error_handler(__LINE__, __FILE__, __VA_ARGS__)

#endif /* GRAOOM_ERRORS_H */
