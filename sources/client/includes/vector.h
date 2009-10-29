/*
** vector.h for BattleTrantor in /home/rannou_s/work/c/BattleTrantor/sources/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Oct  2 10:02:36 2009 sebastien rannou
** Last update Mon Oct  5 20:00:27 2009 sebastien rannou
*/

#ifndef	VECTOR_H
#define VECTOR_H

void
vector_add(d3_t *res, d3_t *v1, d3_t *v2);

void
vector_crossproduct(d3_t *res, d3_t *v1, d3_t *v2);

void
vector_polarize(d3_t *v, double theta, double phi);

double
vector_norm(d3_t *v);

void
vector_normalize(d3_t *v);

#define	VECTOR_INIT(vec, val)	((vec)->x = (vec)->y = (vec)->z = val)

#define	VECTOR_SET(v, X, Y, Z)	\
  (v)->x = X;			\
     (v)->y = Y;		\
	(v)->z = Z

#endif /* VECTOR_H */
