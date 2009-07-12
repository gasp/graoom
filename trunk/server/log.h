/*
** log.h for graoom in /home/rannou_s/work/graoom/server
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Sun Jul 12 22:06:23 2009 Sebastien Rannou
** Last update Sun Jul 12 22:26:42 2009 Sebastien Rannou
*/

#ifndef GRAOOM_LOG_H
#define GRAOOM_LOG_H

int
log_print(int line, char *file, char *prefix, ...);

#define	LOG(...)	log_print(__LINE__, __FILE__, "+ ", __VA_ARGS__)

#endif /* GRAOOM_LOG_H */
