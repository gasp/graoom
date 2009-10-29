/*
** graphic_model.c for battletrantor in /home/rannou_s/Work/graoom/client/graphic
** 
** Made by sebastien rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu Jul 23 19:55:08 2009 sebastien rannou
** Last update Mon Oct  5 20:28:22 2009 sebastien rannou
*/

#ifndef	_BSD_SOURCE	/* strdup() */
#define	_BSD_SOURCE
#endif

#include "coor.h"
#include "shortcuts.h"
#include "lists.h"
#include "ini.h"
#include "errors.h"
#include "log.h"
#include "log_client.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <GL/gl.h>

#include "mdl.h"
#include "graphic_model.h"

void		FreeModel (mdl_model_t *mdl);
int		ReadMDLModel (const char *filename, mdl_model_t *mdl);

#define		MODELS_INI_FILE		"internals/models.ini"
#define		INI_PATH		"path"

typedef struct	internal_model_s
{
  char		*name;
  mdl_model_t	model;
}		internal_model_t;

list_t *
global_models = NULL;

mdl_model_t *
graphic_get_model(const char *name)
{
  list_t		*current;
  internal_model_t	*elem;

  for (current = global_models; current != NULL; current = current->li_next)
    {
      elem = current->data;
      if (!strcmp(elem->name, name))
	{
	  return &elem->model;
	}
    }
  ERR_RAISE(EC_GL_GET_MODEL, name);
  return NULL;
}

/**!
 * @author	rannou_s
 * Let's destroy an internal model
 */

void
graphic_clean_model(void *ptr)
{
  internal_model_t *		model = ptr;

  if (model != NULL)
    {
      free(model->name);
      FreeModel(&model->model);
      free(model);
    }
}

/**!
 * @author	rannou_s
 * Tries to load a model, if it works, push it to models' list
 */

static int
graphic_load_model_push(char *name, char * path)
{
  internal_model_t *		new_elem;

  new_elem = malloc(sizeof(*new_elem));
  if (new_elem == NULL)
    {
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  if ((new_elem->name = strdup(name)) == NULL)
    {
      free(new_elem);
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  if (ReadMDLModel(path, &new_elem->model) == ERROR)
    {
      free(new_elem);
      return (ERROR);
    }
  if (list_push(&global_models, new_elem) == ERROR)
    {
      free(new_elem);
      ERR_RAISE(EC_SYS_MALLOC, strerror(errno));
      return (ERROR);
    }
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * Let's load mdl files
 */

int
graphic_load_models(void)
{
  ini_t *		ini = ini_parse_file(MODELS_INI_FILE);
  list_t *		cur;
  char *		path;

  LOG(GRAPHIC_LOADING_MODELS);
  if (ini == NULL)
    {
      ERR_RAISE(EC_INI_FILE, MODELS_INI_FILE);
      return ERROR;
    }
  for (cur = ini->sections_is; cur != NULL; cur = cur->li_next)
    {
      path = ini_retrieve_entry_from_section(cur->data, INI_PATH);
      if (path == NULL)
	{
	  ERR_RAISE(EC_INI_UNKNOWN_ENTRY, INI_PATH, MODELS_INI_FILE);
	}
      else
	{
	  if (graphic_load_model_push(((ini_section_t *)(cur->data))->name, path) == ERROR)
	    {
	      ERR_RAISE(EC_MODEL_LOAD, path);
	    }
	  else
	    {
	      LOG(GRAPHIC_LOADING_MODEL_OK, path);
	    }
	}
    }
  ini_free_main(ini);
  return (SUCCESS);
}

/**!
 * @author	rannou_s
 * And finnaly, the cleaner that cleans up each model
 */

int
graphic_clean_models(void)
{
  return (list_free(&global_models, &graphic_clean_model));
}


/**!
 * @author	rannou_s
 * Draws a fixed model (no animation)
 */

void
graphic_draw_fixed_model(const model_instance_t * mdl)
{
  if (NULL != mdl)
    {
      glPushMatrix();
      {
	glTranslatef(mdl->position.x, mdl->position.y, mdl->position.z);
	glScalef(mdl->scale.x, mdl->scale.y, mdl->scale.z);
	glPushMatrix();
	{
	  RenderFrameItp(1, 1, mdl->model);
	}
	glPopMatrix();
      }
      glPopMatrix();
    }
}
