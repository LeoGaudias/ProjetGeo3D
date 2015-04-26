#include "Mesh.h"

Quad Q_new(Vector v1, Vector v2, Vector v3, Vector v4)
{
	Quad q;
	q.v1 = v1;
	q.v2 = v2;
	q.v3 = v3;
	q.v4 = v4;
	return q;
}

Mesh* M_new()
{
	Mesh m;
	m._nb_quads = 0;
	Quad _quads[M_MAX_QUADS];
	m._is_filled = 0;
	return &m
}

void M_print(Mesh *P, char *message)
{
	int i;
	fprintf(stderr,"%s\n",message);
	for(i = 0; i < P->_nb_quads; ++i)
	{
		fprintf(stderr,"Quad %d\n",i);
		fprintf(stderr,"v1.x: %f v1.y: %f v1.z: %f\n", P->_quads[i].v1.x, P->_quads[i].v1.y, P->_quads[i].v1.z);
		fprintf(stderr,"v2.x: %f v2.y: %f v2.z: %f\n", P->_quads[i].v2.x, P->_quads[i].v2.y, P->_quads[i].v2.z);
		fprintf(stderr,"v3.x: %f v3.y: %f v3.z: %f\n", P->_quads[i].v3.x, P->_quads[i].v3.y, P->_quads[i].v3.z);
		fprintf(stderr,"v4.x: %f v4.y: %f v4.z: %f\n", P->_quads[i].v4.x, P->_quads[i].v4.y, P->_quads[i].v4.z);
	}
}

void M_addQuad(Mesh *P, Quad q)
{
	if(P->_nb_quads < M_MAX_QUADS)
	{
		P->_quads[P->_nb_quads] = q;
		P->_nb_quads++;
	}
	else
	{
		fprintf(stderr,"Tableau plein !\n");
	}
}

void M_addSlice(Mesh *P, Polygon *p1, Polygon *p2)
{

}
void M_revolution(Mesh *P, Polygon *p1, int nb_slices)
{

}
void M_perlinExtrude(Mesh *QM, Polygon *p, int nb_slices)
{

}

void M_draw(Mesh *P)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	for(i = 0; i < P->_quads; ++i)
	{
		glVertex3f(P->_quads[i].v1.x, P->_quads[i].v1.y, P->_quads[i].v1.z);
		glVertex3f(P->_quads[i].v2.x, P->_quads[i].v2.y, P->_quads[i].v2.z);
		glVertex3f(P->_quads[i].v3.x, P->_quads[i].v3.y, P->_quads[i].v3.z);
		glVertex3f(P->_quads[i].v4.x, P->_quads[i].v4.y, P->_quads[i].v4.z);
	}
	glEnd();
}