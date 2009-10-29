/*
** map.h for BattleTrantor in /home/rannou_s/work/c/BattleTrantor/sources/client/graphic/map
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Fri Oct  2 15:22:30 2009 sebastien rannou
** Last update Fri Oct  2 16:01:24 2009 sebastien rannou
*/

#ifndef	MAP_H
#define MAP_H

int	/* Destroy the map and its list */
map_destruct(void);

int	/* Initialize the map module */
map_initialize(void);

void	/* Draws the list */
map_draw(void);

#endif /* MAP_H */
