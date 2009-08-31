/*
** server_log.h for graoom in /home/rannou_s/Work/graoom
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 11:35:09 2009 sebastien rannou
** Last update Sun Aug  9 15:00:06 2009 
*/

#ifndef	GRAOOM_LOG_SERVER_H
#define	GRAOOM_LOG_SERVER_H

#define	LOG_CLIENT_KICK_DEF	"kicking client [%d] (unknow reason)"
#define	LOG_CLIENT_KICK		"kicking client [%d] (%s)"
#define	LOG_EXEC_COMMAND	"executing command [%s] from client [%d]"
#define	LOG_CLIENT_NEW		"new connection accepted from (%s)"
#define	LOG_CLEAN_MOD		"cleaning module [%s]"
#define	LOG_LOAD_MOD		"loading module [%s]"
#define	LOG_LOAD_DONE		"loading completed"

#endif /* GRAOOM_LOG_SERVER_H */
