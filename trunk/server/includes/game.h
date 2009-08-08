/*
** game.h for graoom in /home/aimxhaisse/work/graoom/server/game
** 
** Made by 
** Login   <aimxhaisse@epitech.net>
** 
** Started on  Wed Aug  5 14:17:03 2009 
** Last update Thu Aug  6 00:07:12 2009 
*/

#ifndef	GRAOOM_GAME_H
#define	GRAOOM_GAME_H

#define			MAP_LEN		64

typedef struct		map_s		/* struct of a map */
{
  char			name[MAP_LEN];	/* map's name */
  int			size;		/* map's size */
}			map_t;

typedef struct		game_s		/* main struct for game module */
{
  map_t			map;		/* current map */
}			game_t;

#endif /* GRAOOM_GAME_H */
