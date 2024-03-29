#include "Polygon.h"
#include "Vector.h"

void P_init(Polygon *p)
{
	p->_nb_vertices = 0;
	p->_is_closed = 0;
	// 1 --> true
	p->_is_filled = 1;
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

void P_draw(Polygon *P)
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
	
	int i, test = 0;
	for (i = 0; i < P->_nb_vertices - 1; ++i)
	{
		test += V_isOnTheRight(M,P->_vertices[i],P->_vertices[i+1]);
	}

	if(P->_nb_vertices>=3)
	{
		if(test == P->_nb_vertices - 1 && V_isOnTheRight(P->_vertices[2],P->_vertices[0],P->_vertices[1])==1)
		{
			return 1;
		}
		else if(test==0 && V_isOnTheRight(P->_vertices[2],P->_vertices[0],P->_vertices[1])==0)
		{
			return 1;
		}
	}
	else
	{
		fprintf(stderr, "Nombre de vertices doit être supérieur ou égal à 3\n");
		return -1;
	}
	
	return 0;
}

void P_turnAroundY(Polygon *P, double radians){
	int i;
	for (i=0; i < P->_nb_vertices; i++){
		V_turnAroundY(P->_vertices[i], radians);
	}
}

Vector P_center(Polygon *P)
{
	int i=0;
	Vector centre=V_new(0,0,0);

	for(i=0;i<P->_nb_vertices;i++)
	{
		centre=V_add(centre,P->_vertices[i]);
	}
	centre=V_multiply((double)1.0/P->_nb_vertices,centre);

	return centre;
}

Vector P_normal(Polygon *P)
{
	Vector v1=V_substract(P->_vertices[1], P->_vertices[0]);
	Vector v2=V_substract(P->_vertices[2], P->_vertices[0]);
	return V_unit(V_cross(v1,v2));
}

void P_scale(Polygon *P, double factor)
{
	//TODO
}

void P_translate(Polygon *P, Vector trans)
{
	int i=0;
	for(i=0;i<P->_nb_vertices;i++)
	{
		P->_vertices[i]=V_add(P->_vertices[i],trans);
	}
}

void P_rotate(Polygon *P, Vector normal)
{
	Vector centre=P_center(P);

	Vector normal_act=V_add(centre,P_normal(P));
	Vector normal_voulu=V_add(centre,V_unit(normal));

	int i=0;
	for(i=0;i<P->_nb_vertices;i++)
	{
		V_rotate(P->_vertices[i],centre,normal_act,normal_voulu);
	}
}