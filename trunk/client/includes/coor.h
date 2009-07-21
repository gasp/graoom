/*
** coor_types.h for graoom in /home/rannou_s/Work/graoom/bin/graoom-client/internals
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Tue Jul 21 20:12:49 2009 sebastien rannou
** Last update Tue Jul 21 20:18:35 2009 sebastien rannou
*/

#ifndef	GRAOOM_C_COOR_H
#define	GRAOOM_C_COOR_H

/**!
 * @author	rannou_s
 * here is the synthax used by these structs :
 * AB_t where:
 *	A = type (i = int, f = float, ...)
 *	B = dimensions (3d = 3, 2d = 2, ...)
 */

typedef struct		d3_s
{
  double		x;
  double		y;
  double		z;
}			d3_t;

typedef struct		d2_s
{
  double		x;
  double		y;
}			d2_t;

typedef struct		i2_s
{
  int			x;
  int			y;
}			i2_t;

#endif /* GRAOOM_C_COOR_H */
