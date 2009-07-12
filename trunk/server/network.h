/*
** network.h for graoom in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 14:11:29 2009 Sebastien Rannou
** Last update Sun Jul 12 17:47:25 2009 Sebastien Rannou
*/

#ifndef	GRAOOM_NETWORK_K
#define	GRAOOM_NETWORK_K

typedef	struct		network_conf_s
{
  int			port;
  int			num_max_connection;
}			network_conf_t;

typedef struct		network_s
{
  network_conf_t	configuration;
}			network_t;

#endif /* GRAOOM_NETWORK_K */
