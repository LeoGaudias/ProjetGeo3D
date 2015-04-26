#include "Polygon.h"
#include "Vector.h"

void P_init(Polygon *p)
{
	p->_nb_vertices = 0;
	p->_is_closed = 0;
	// 1 --> true
	p->_is_filled = 0;
	p->_is_convex = 0;
}

void P_copy(Polygon *original, Polygon *copy)
{
	copy->_nb_vertices = original->_nb_vertices;
	copy->_is_closed = original->_is_closed;
	copy->_is_filled = original->_is_filled;
	copy->_is_convex = original->_is_convex;
	int i;
	for(i = 0; i < P_MAX_VERTICES; ++i)
	{
	copy->_vertices[i] = original->_vertices[i];
	}
}

void P_addVertex(Polygon *P, Vector p)
{
	if(P->_nb_vertices < P_MAX_VERTICES)
	{
		P->_vertices[P->_nb_vertices] = p;
		P->_nb_vertices++;
	}
	else
	{
		fprintf(stderr,"Tableau plein !\n");
	}
}

void P_removeLastVertex(Polygon *P)
{
	if(P->_nb_vertices > 0)
	{
		P->_nb_vertices--;
	}
	else
	{
		fprintf(stderr,"Tableau vide !\n");
	}
}

void P_print(Polygon *P, char *message)
{
	int i;
	fprintf(stderr,"%s\n",message);
	for(i = 0; i < P->_nb_vertices; ++i)
	{
		fprintf(stderr,"Vector %d : %f, %f , %f\n",i,P->_vertices[i].x,P->_vertices[i].y,P->_vertices[i].z);
	}
}

void P_draw(Polygon *P, int width, int height)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	for(i = 0; i < P->_nb_vertices; ++i)
	{
		glVertex3f(P->_vertices[i].x,P->_vertices[i].y,P->_vertices[i].z);
	}
	glEnd();
}

int P_isConvex(Polygon *P)
{
	if(P->_nb_vertices > 2)
	{
		int i, test = 0;
		for (i = 0; i < P->_nb_vertices - 2; ++i)
		{
			test += V_isOnTheRight(P->_vertices[i+2],P->_vertices[i],P->_vertices[i+1]);
		}
		printf("test = %d\n",test);
		if(test == P->_nb_vertices - 2 || test == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		fprintf(stderr,"Pas assez de Vector pour le réaliser le test\n");
		return -1;	
	}
}

int P_isOnTheLeftOfAllEdges(Polygon *P, Vector M)
{
	//TODO
	return 0;
}

int P_nbEdgesIntersectedByRay(Polygon *P, Vector M, Vector u_ray)
{
	//TODO
	return 0;
}

int P_isInside(Polygon *P, Vector M)
{
	//TODO
	return 0;
}

void P_turnAroundY(Polygon *P, double radians)
{
	//TODO
}

Vector P_center(Polygon *P)
{
	//TODO
	return V_new(0,0,0);
}

Vector P_normal(Polygon *P)
{
	//TODO
	return V_new(0,0,0);
}

void P_scale(Polygon *P, double factor)
{
	//TODO
}

void P_translate(Polygon *P, Vector trans)
{
	//TODO
}

void P_rotate(Polygon *P, Vector normal)
{
	//TODO
}