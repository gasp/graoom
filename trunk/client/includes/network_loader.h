/*
** network_loader.h for graoom in /home/rannou_s/Work/graoom/client/network
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jul 20 22:27:26 2009 sebastien rannou
** Last update Mon Jul 20 23:32:52 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_NETWORK_LOADER_H
#define	GRAOOM_C_NETWORK_LOADER_H

void *	/* Let's parse .ini file */
network_parser(client_t *client, ini_section_t *section);

int	/* Let's connect to remote host */
network_init(client_t *client, void *network);

int	/* Let's clean up everything */
network_cleaner(client_t *client, void *network);

#endif /* GRAOOM_C_NETWORK_LOADER_H */
