/*
** network.h for graoom in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 14:11:29 2009 Sebastien Rannou
** Last update Sun Jul 19 01:32:58 2009 sebastien rannou
*/

#ifndef	GRAOOM_NETWORK_H
#define	GRAOOM_NETWORK_H

#define	IBUFF_SIZE	4096			/* input buffer max size */

typedef struct		network_ibuff_s		/* input buffer */
{
  char			buffer[IBUFF_SIZE+1];	/* input buffer */
  int			offset;			/* position on the buffer */
}			network_ibuff_t;

#define	CLIENT_CONNECTED	1		/* 0001 */
#define	CLIENT_KICKED		2		/* 0010 */

typedef struct		network_client_s	/* structure of a client */
{
  network_ibuff_t	ibuff;			/* input buffer */
  void			*data;			/* volontary a typeless ptr */
  char			*ip;			/* client's ip */
  int			sock;			/* client's socket */
  int			state;			/* to kick? playing? */
  int			id;			/* client's id */
}			network_client_t;

typedef	struct		network_conf_s		/* network settings */
{
  int			port;			/* listening port */
  int			num_max_connection;	/* maximum number of connections */
}			network_conf_t;

typedef struct		network_select_s	/* data related to select */
{
  int			current_fd_max;		/* current highest fd */
  fd_set		readfs;			/* to know activity from openned sockets */
}			network_select_t;

typedef struct		network_s		/* main structure */
{
  network_select_t	select;			/* select's configuration */
  network_conf_t	configuration;		/* network's settings */
  list_t		*clients;		/* list of connected clients */
  int			last_client_id;		/* used to determine ids */
  int			primary_socket;		/* listening socket */
}			network_t;

#endif /* GRAOOM_NETWORK_H */
