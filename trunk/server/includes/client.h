/*
** client.h for graoom in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 14 11:18:58 2009 Sebastien Rannou
** Last update Sun Jul 19 00:18:41 2009 sebastien rannou
*/

#ifndef	GRAOOM_CLIENT_H
#define	GRAOOM_CLIENT_H

#define	CLI_KICK_READ_ERR	"unable to read from that client (%s)"
#define	CLI_KICK_OVERFLOW	"input buffer: overflowed"
#define	CLI_KICK_CLOSED		"connection closed"

int	/* let's kick a client */
client_kick(network_client_t *client, char *message);

#endif /* GRAOOM_CLIENT_H */
