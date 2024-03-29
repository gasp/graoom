/*
** log.h for battletrantor in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 22:06:23 2009 Sebastien Rannou
** Last update Tue Jul 21 11:39:18 2009 sebastien rannou
*/

#ifndef GRAOOM_LOG_H
#define GRAOOM_LOG_H

#define	LOG_PREFIX_OK		"+ "

int
log_print(int line, char *file, char *prefix, ...);

#define	LOG(...)	log_print(__LINE__, __FILE__, LOG_PREFIX_OK, __VA_ARGS__)

#endif /* GRAOOM_LOG_H */
