/*
** errors.h for battletrantor in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 20:27:27 2009 sebastien rannou
** Last update Mon Oct  5 22:31:34 2009 sebastien rannou
*/

#ifndef GRAOOM_C_ERRORS_H
#define	GRAOOM_C_ERRORS_H

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
    
    EC_SYS_MALLOC,
    EC_SYS_STRDUP,
    
    EC_INI_FILE,
    EC_INI_SEC,
    EC_INI_UNKNOWN_ENTRY,

    EC_LOADER_SEV,
    EC_LOADER_NULL,
    EC_LOADER_PORT,
    EC_LOADER_GFX_WINX,
    EC_LOADER_GFX_WINY,
    EC_LOADER_GFX_RATIO,
    EC_LOADER_EVENT_UNK,
    EC_LOADER_NOK,
    EC_LOADER_GFX_MAXFPS,
    EC_LOADER_COLOR_UNKNOWN,
    EC_LOADER_EVENT_OVER,
    EC_LOADER_INVALID_FOV,
    
    EC_SDL_NET_RESOLVE,
    EC_SDL_NET_OPEN,
    EC_SDL_INIT,
    EC_SDL_SETVIDEO,
    EC_SDL_TTF_INIT,
    EC_SDL_TTF_OPEN,
    EC_SDL_TTF_INVALID_SIZE,
    EC_SDL_CREATEMUTEX,
    EC_SDL_CREATE_THREAD,
    EC_SDL_CREATE_SURFACE,
    EC_SDL_LOAD_IMG,
    EC_SDL_TTF_RENDER,
    EC_SDL_BLIT,
    EC_SDL_TTF_NOT_FOUND,
    EC_SDL_TTF_GET,
    EC_SDL_INVALID_COLOR,
    EC_SDL_CONSOLE_INI,

    EC_GL_CONVERT_TEX,
    EC_GL_GET_TEXTURE,
    EC_GL_GET_MODEL,
    EC_MODEL_LOAD,
    EC_GL_NEW_QUAD
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
