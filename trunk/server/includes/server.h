/*
** server.h for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Wed Jul  8 23:27:43 2009 sebastien rannou
** Last update Sun Jul 19 13:56:18 2009 sebastien rannou
*/

#ifndef	GRAOOM_SERVER_H
#define	GRAOOM_SERVER_H

/**!
 * @author	rannou_s
 * As everything is this part of the code is related to server
 * let's define some shortcuts to have a clean code
 */

#define	SERVER_STATE_ON		0
#define	SERVER_STATE_OFF	1
#define	SERVER_NAME_LEN		256

typedef struct		server_s	/* main structure of the program */
{
  char			name[256];	/* server's name */
  int			state;		/* server's state, default is ON */
}			server_t;

int	/* let's load each module */
loader(server_t *server);

int	/* let's clean previously loaded modules */
cleaner(server_t *server);

int	/* let's launch the server */
launcher(server_t *server);

#endif /* GRAOOM_SERVER_H */
