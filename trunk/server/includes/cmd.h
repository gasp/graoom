/*
** cmd.h for graoom in /home/rannou_s/Work/graoom/server/cmd
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 13:39:22 2009 sebastien rannou
** Last update Sat Aug  8 16:30:12 2009 
*/

#ifndef GRAOOM_CMD_H
#define GRAOOM_CMD_H

int	/* sends information about the map */
cmd_map(server_t *server, network_client_t *client);

int	/* called when a new client is connected */
cmd_welcome(server_t *server, network_client_t *client);

#endif /* GRAOOM_CMD_H */
