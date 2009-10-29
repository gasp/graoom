/*
** base_vectors.c for BattleTrantor in /home/rannou_s/work/c/BattleTrantor/sources/client/base
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Oct  2 09:41:58 2009 sebastien rannou
** Last update Mon Oct  5 18:17:10 2009 sebastien rannou
*/

#include <math.h>
#include <stdio.h>

#include "coor.h"

/**!
 * Some common operations on vectors...
 */

/**!
 * Addition of two vectors
 */

void
vector_add(d3_t *res, d3_t *v1, d3_t *v2)
{
  if (res && v1 && v2)
    {
      res->x = v1->x + v2->x;
      res->y = v1->y + v2->y;
      res->z = v1->z + v2->z;
    }
}

/**!
 * Crossproduct of two vectors
 */

void
vector_crossproduct(d3_t *res, d3_t *v1, d3_t *v2)
{
  if (res && v1 && v2)
    {
      res->x = v1->y * v2->z - v1->z * v2->y;
      res->y = v1->z * v2->x - v1->x * v2->z;
      res->z = v1->x * v2->y - v1->y * v2->x;
    }
}

/**!
 * Polarize a vector
 */

void
vector_polarize(d3_t *v, double theta, double phi)
{
  double	rtmp;

  if (v != NULL)
    {
      rtmp = cos(phi);
      v->z = sin(phi);
      v->y = rtmp * sin(theta);
      v->x = rtmp * cos(theta);
    }
}

/**!
 * Returns norm of a vector
 */

double
vector_norm(d3_t *v)
{
  if (v != NULL)
    {
      return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    }
  /* ERR_RAISE?! */
  return 42;
}

/**!
 * Normalize a vector
 */

void
vector_normalize(d3_t *v)
{
  double	len;

  if (v != NULL)
    {
      len = vector_norm(v);
      v->x /= len;
      v->y /= len;
      v->z /= len;
    }
}
