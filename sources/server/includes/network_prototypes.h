/*
** network_prototypes.h for battletrantor in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 20:14:35 2009 sebastien rannou
** Last update Sun Jul 19 13:18:46 2009 sebastien rannou
*/

#ifndef GRAOOM_NETWORK_PROTOTYPES_H
#define GRAOOM_NETWORK_PROTOTYPES_H

int	/* parser which allocates network's structure */
network_parser(server_t *server, ini_section_t *conf);

int	/* initialize the previously allocated area, start sockets, ... */
network_initialize(server_t *server);

int	/* cleans up everything from that module */
network_clean(server_t *server);

#endif /* GRAOOM_NETWORK_PROTOTYPES_H */
