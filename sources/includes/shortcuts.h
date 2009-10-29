/*
** shortcuts.h for graooom in /home/rannou_s/Work/xoosh/libs/tools
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Mon Jun 29 18:24:28 2009 Sebastien Rannou
** Last update Fri Oct  2 10:51:48 2009 sebastien rannou
*/

#ifndef	GRAOOM_SHORTCUTS_H
#define	GRAOOM_SHORTCUTS_H

#define	ERROR			-1
#define	SUCCESS			0

#define	ON			1
#define	OFF			0

#define	FOP_R			"r"
#define	FOP_AP			"a+"

#define	MAX(x, y)		(((x) > (y)) ? (x) : (y))
#define	MIN(x, y)		(((x) < (y)) ? (x) : (y))
#define	X(val)			write(1, val, strlen(val))

#define	PI			3.14159265
#define	RADIAN(x)		(x * PI / 180)

#endif	/* GRAOOM_SHORTCUTS_H */
