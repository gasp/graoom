/*
** mdl.h for zappy in /home/rannou_s/Work/zappy1/srcs/gfx_client
** 
** Made by Sebastien Rannou
** Login   <rannou_s@epitech.net>
** 
** Started on  Thu May 21 13:33:59 2009 Sebastien Rannou
** Last update Mon Oct  5 18:28:41 2009 sebastien rannou
*/

#ifndef __CLIENT_MDL_STRUCTURES__
#define __CLIENT_MDL_STRUCTURES__

/* vector */
typedef float vec3_t[3];

/* mdl header */
typedef struct
{
  int ident;            /* magic number: "IDPO" */
  int version;          /* version: 6 */

  vec3_t scale;         /* scale factor */
  vec3_t translate;     /* translation vector */
  float boundingradius;
  vec3_t eyeposition;   /* eyes' position */

  int num_skins;        /* number of textures */
  int skinwidth;        /* texture width */
  int skinheight;       /* texture height */

  int num_verts;        /* number of vertices */
  int num_tris;         /* number of triangles */
  int num_frames;       /* number of frames */

  int synctype;         /* 0 = synchron, 1 = random */
  int flags;            /* state flag */
  float size;

} mdl_header_t;

/* skin */
typedef struct
{
  int group;      /* 0 = single, 1 = group */
  GLubyte *data;  /* texture data */

} mdl_skin_t;

/* texture coords */
typedef struct
{
  int onseam;
  int s;
  int t;

} mdl_texCoord_t;

/* triangle info */
typedef struct
{
  int facesfront;  /* 0 = backface, 1 = frontface */
  int vertex[3];   /* vertex indices */

} mdl_triangle_t;

/* compressed vertex */
typedef struct
{
  unsigned char v[3];
  unsigned char normalIndex;

} mdl_vertex_t;

/* simple frame */
typedef struct
{
  mdl_vertex_t bboxmin;	/* bouding box min */
  mdl_vertex_t bboxmax;	/* bouding box max */
  char name[16];
  mdl_vertex_t *verts;  /* vertex list of the frame */

} mdl_simpleframe_t;

/* model frame */
typedef struct
{
  int type;                 /* 0 = simple, !0 = group */
  mdl_simpleframe_t frame;  /* this program can't read models
			       composed of group frames! */
} mdl_frame_t;

/* mdl model structure */
typedef struct
{
  mdl_header_t header;

  mdl_skin_t *skins;
  mdl_texCoord_t *texcoords;
  mdl_triangle_t *triangles;
  mdl_frame_t *frames;

  GLuint *tex_id;
  int iskin;

} mdl_model_t;

void
RenderFrameItp (int n, float interp, mdl_model_t *mdl);

#endif /* __CLIENT_MDL_STRUCTURES__ */
