/*
 * mdl.c -- mdl model loader
 * last modification: dec. 19, 2005
 *
 * Copyright (c) 2005 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * gcc -Wall -ansi -L/usr/X11R6/lib -lGL -lGLU -lglut mdl.c -o mdl
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mdl.h"

/* table of precalculated normals */
vec3_t anorms_table[162] = {
#include "anorms.h"
};

/* palette */
unsigned char colormap[256][3] = {
#include "colormap.h"
};


GLuint
MakeTexture (int n, mdl_model_t *mdl)
{
  int i;
  GLuint id;
  GLubyte *pixels = (GLubyte *)malloc (sizeof (GLubyte)
	* mdl->header.skinwidth * mdl->header.skinheight * 3);

  /* convert indexed 8 bits texture to RGB 24 bits */
  for (i = 0; i < mdl->header.skinwidth * mdl->header.skinheight; ++i)
    {
      pixels[(i * 3) + 0] = colormap[mdl->skins[n].data[i]][0];
      pixels[(i * 3) + 1] = colormap[mdl->skins[n].data[i]][1];
      pixels[(i * 3) + 2] = colormap[mdl->skins[n].data[i]][2];
    }

  /* generate OpenGL texture */
  glGenTextures (1, &id);
  glBindTexture (GL_TEXTURE_2D, id);

  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  gluBuild2DMipmaps (GL_TEXTURE_2D, GL_RGB, mdl->header.skinwidth,
		     mdl->header.skinheight, GL_RGB, GL_UNSIGNED_BYTE,
		     pixels);

  /* OpenGL has its own copy of image data */
  free (pixels);
  return id;
}


int
ReadMDLModel (const char *filename, mdl_model_t *mdl)
{
  FILE *fp;
  int i;

  fp = fopen (filename, "rb");
  if (!fp)
    {
      fprintf (stderr, "error: couldn't open \"%s\"!\n", filename);
      return 0;
    }

  /* read header */
  fread (&mdl->header, 1, sizeof (mdl_header_t), fp);
  if ((mdl->header.ident != 1330660425) ||
      (mdl->header.version != 6))
    {
      /* error! */
      fclose (fp);


      printf("Bad version\n");
      return 0;
    }

  /* memory allocation */
  mdl->skins = (mdl_skin_t *)malloc (sizeof (mdl_skin_t) * mdl->header.num_skins);
  mdl->texcoords = (mdl_texCoord_t *)malloc (sizeof (mdl_texCoord_t) * mdl->header.num_verts);
  mdl->triangles = (mdl_triangle_t *)malloc (sizeof (mdl_triangle_t) * mdl->header.num_tris);
  mdl->frames = (mdl_frame_t *)malloc (sizeof (mdl_frame_t) * mdl->header.num_frames);
  mdl->tex_id = (GLuint *)malloc (sizeof (GLuint) * mdl->header.num_skins);

  mdl->iskin = 0;

  /* read texture data */
  for (i = 0; i < mdl->header.num_skins; ++i)
    {
      mdl->skins[i].data = (GLubyte *)malloc (sizeof (GLubyte)
		* mdl->header.skinwidth * mdl->header.skinheight);

      fread (&mdl->skins[i].group, sizeof (int), 1, fp);
      fread (mdl->skins[i].data, sizeof (GLubyte),
	     mdl->header.skinwidth * mdl->header.skinheight, fp);

      mdl->tex_id[i] = MakeTexture (i, mdl);

      free (mdl->skins[i].data);
      mdl->skins[i].data = NULL;
    }

  fread (mdl->texcoords, sizeof (mdl_texCoord_t), mdl->header.num_verts, fp);
  fread (mdl->triangles, sizeof (mdl_triangle_t), mdl->header.num_tris, fp);

  /* read frames */
  for (i = 0; i < mdl->header.num_frames; ++i)
    {
      /* memory allocation for vertices of this frame */
      mdl->frames[i].frame.verts = (mdl_vertex_t *)
	malloc (sizeof (mdl_vertex_t) * mdl->header.num_verts);

      /* read frame data */
      fread (&mdl->frames[i].type, sizeof (long), 1, fp);
      fread (&mdl->frames[i].frame.bboxmin, sizeof (mdl_vertex_t), 1, fp);
      fread (&mdl->frames[i].frame.bboxmax, sizeof (mdl_vertex_t), 1, fp);
      fread (mdl->frames[i].frame.name, sizeof (char), 16, fp);
      fread (mdl->frames[i].frame.verts, sizeof (mdl_vertex_t),
	     mdl->header.num_verts, fp);
    }

  fclose (fp);
  return 1;
}


void
FreeModel (mdl_model_t *mdl)
{
  int i;

  if (mdl->skins)
    {
      free (mdl->skins);
      mdl->skins = NULL;
    }

  if (mdl->texcoords)
    {
      free (mdl->texcoords);
      mdl->texcoords = NULL;
    }

  if (mdl->triangles)
    {
      free (mdl->triangles);
      mdl->triangles = NULL;
    }

  if (mdl->tex_id)
    {
      /* delete OpenGL textures */
      glDeleteTextures (mdl->header.num_skins, mdl->tex_id);

      free (mdl->tex_id);
      mdl->tex_id = NULL;
    }

  if (mdl->frames)
    {
      for (i = 0; i < mdl->header.num_frames; ++i)
	{
	  free (mdl->frames[i].frame.verts);
	  mdl->frames[i].frame.verts = NULL;
	}

      free (mdl->frames);
      mdl->frames = NULL;
    }
}

void
RenderFrameItp (int n, float interp, mdl_model_t *mdl)
{
  int i, j;
  GLfloat s, t;
  vec3_t norm, v;
  GLfloat *n_curr, *n_next;
  mdl_vertex_t *pvert1, *pvert2;

  /* check if n is in a valid range */
  if ((n < 0) || (n >= mdl->header.num_frames))
    return;

  /* enable model's texture */
  glBindTexture (GL_TEXTURE_2D, mdl->tex_id[mdl->iskin]);
  
  /* draw the model */
  glBegin (GL_TRIANGLES);
    /* draw each triangle */
    for (i = 0; i < mdl->header.num_tris; ++i)
      {
	/* draw each vertex */
	for (j = 0; j < 3; ++j)
	  {
	    pvert1 = &mdl->frames[n].frame.verts[mdl->triangles[i].vertex[j]];
	    pvert2 = &mdl->frames[n + 1].frame.verts[mdl->triangles[i].vertex[j]];

	    /* compute texture coordinates */
	    s = (GLfloat)mdl->texcoords[mdl->triangles[i].vertex[j]].s;
	    t = (GLfloat)mdl->texcoords[mdl->triangles[i].vertex[j]].t;

	    if (!mdl->triangles[i].facesfront &&
		mdl->texcoords[mdl->triangles[i].vertex[j]].onseam)
	      {
		s += mdl->header.skinwidth * 0.5f; /* backface */
	      }

	    /* scale s and t to range from 0.0 to 1.0 */
	    s = (s + 0.5) / mdl->header.skinwidth;
	    t = (t + 0.5) / mdl->header.skinheight;

	    /* pass texture coordinates to OpenGL */
	    glTexCoord2f (s, t);

	    /* interpolate normals */
	    /*
	    memcpy (n_curr, anorms_table[pvert1->normalIndex], sizeof (vec3_t));
	    memcpy (n_next, anorms_table[pvert2->normalIndex], sizeof (vec3_t));
	    */

	    n_curr = anorms_table[pvert1->normalIndex];
	    n_next = anorms_table[pvert2->normalIndex];

	    norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
	    norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
	    norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);

	    glNormal3fv (norm);

	    /* interpolate vertices */
	    v[0] = mdl->header.scale[0] * (pvert1->v[0] + interp
		* (pvert2->v[0] - pvert1->v[0])) + mdl->header.translate[0];
	    v[1] = mdl->header.scale[1] * (pvert1->v[1] + interp
		* (pvert2->v[1] - pvert1->v[1])) + mdl->header.translate[1];
	    v[2] = mdl->header.scale[2] * (pvert1->v[2] + interp
		* (pvert2->v[2] - pvert1->v[2])) + mdl->header.translate[2];

	    glVertex3fv (v);
	  }
      }
  glEnd ();
}
