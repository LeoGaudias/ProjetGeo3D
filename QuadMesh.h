#ifndef _QUADMESH_H_
#define _QUADMESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "Vector.h"

typedef struct
{
	Vector _vertices[4];
	int _is_filled;
	int _is_convex;
}Quad;

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4);
void M_init(Maillage *M);
void M_addQuad(Maillage *M, Quad q);
void M_draw(Maillage *M) ;
void M_print(Maillage *M, char *message) ; 

#endif // _QUADMESH_H_