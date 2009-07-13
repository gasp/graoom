/*
** network.h for graoom in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 14:11:29 2009 Sebastien Rannou
** Last update Mon Jul 13 16:01:10 2009 Sebastien Rannou
*/

#ifndef	GRAOOM_NETWORK_H
#define	GRAOOM_NETWORK_H

#include <sys/select.h>	/* required for fd_set */

typedef struct		network_pack_head_s	/* packet's header */
{
  unsigned int		magic;			/* magic number */
  unsigned int		action;			/* action to handle */
  unsigned int		len;			/* size of the paquet */
}			network_pack_head_t;

#define	NET_MAX_QUEUE	10
#define	NET_MAX_P_LEN	512
#define	NET_MAX_BUF	NET_MAX_QUEUE * (NET_MAX_P_LEN + sizeof(network_pack_head_t))

typedef struct		network_ibuff_s		/* input buffer */
{
  char			buffer[NET_MAX_BUF+1];	/* input buffer */
  network_pack_head_t	packet;			/* memset to 0 when none */
  int			offset;			/* position on the buffer */
}			network_ibuff_t;

typedef struct		network_client_s	/* structure of a client */
{
  network_ibuff_t	net_ibuff;		/* input buffer */
  void			*cli_data;		/* volontary a typeless ptr */
  char			*cli_ip;		/* client's ip */
  int			cli_socket;		/* client's socket */
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
  network_conf_t	configuration;		/* network's settings */
  network_select_t	select;			/* select's configuration */
  int			primary_socket;		/* listening socket */
  list_t		*li_clients;		/* list of connected clients */
}			network_t;

#endif /* GRAOOM_NETWORK_H */
