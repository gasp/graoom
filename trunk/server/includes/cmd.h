/*
** cmd.h for graoom in /home/rannou_s/Work/graoom/server/cmd
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 19 13:39:22 2009 sebastien rannou
** Last update Sun Jul 19 14:00:26 2009 sebastien rannou
*/

#ifndef GRAOOM_CMD_H
#define GRAOOM_CMD_H

#define	CMD_WELCOME_MSG	"welcome on graoom server [%s]"

int	/* called when a new client is connected */
cmd_welcome(server_t *server, network_t *network, network_client_t *client);

#endif /* GRAOOM_CMD_H */
