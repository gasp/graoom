/*
** graphic_model.h for BattleTrantor in /home/rannou_s/work/c/BattleTrantor/sources/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Oct  1 17:14:27 2009 sebastien rannou
** Last update Mon Oct  5 18:26:59 2009 sebastien rannou
*/

#ifndef	GRAPHIC_MODEL_H
#define	GRAPHIC_MODEL_H

int /* load models */
graphic_load_models(void);

int /* free models */
graphic_clean_models(void);

mdl_model_t * /* retrieve a model */
graphic_get_model(const char *);

typedef struct		model_instance_s
{
  mdl_model_t *		model;
  d3_t			position;
  d3_t			rotation;
  d3_t			scale;
}			model_instance_t;

void /* draws a fixed model */
graphic_draw_fixed_model(const model_instance_t *);

#endif /* GRAPHIC_MODEL_H */
