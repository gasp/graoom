/*
** network_prototypes.h for graoom in /home/rannou_s/Work/graoom/server
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Jul 17 20:14:35 2009 sebastien rannou
** Last update Sat Aug  8 14:39:29 2009 
*/

#ifndef GRAOOM_GAME_PROTOTYPES_H
#define GRAOOM_GAME_PROTOTYPES_H

int	/* parser which allocates game's structure */
game_parser(server_t *server, ini_section_t *conf);

int	/* initialize the previously allocated area */
game_initialize(server_t *server);

int	/* cleans up everything from that module */
game_clean(server_t *server);

#endif /* GRAOOM_GAME_PROTOTYPES_H */
