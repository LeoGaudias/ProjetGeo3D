#include "Vector.h"

const float epsilon = 0.0000000001;

Vector V_new(float x, float y, float z)
{
	Vector v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

void V_print(Vector v, char *message)
{
	fprintf(stderr,"%s : %f %f %f\n",message, v.x,v.y,v.z);
}

Vector V_add(Vector v1, Vector v2)
{
	return V_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector V_substract(Vector v1, Vector v2)
{
	return V_new(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector V_multiply(double lambda, Vector v)
{
	return V_new(lambda * v.x, lambda * v.y, lambda * v.z);
}

Vector V_cross(Vector v1, Vector v2)
{
	return V_new((v1.y * v2.z) - (v1.z * v2.y),
	 (v1.z * v2.x) - (v1.x * v2.z),
	 (v1.x * v2.y) - (v1.y * v2.x));
}

float  V_dot(Vector v1, Vector v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float  V_length(Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector V_unit(Vector v)
{
	//TODO
	return V_new(0,0,0);
}

int V_isOnTheRight(Vector M, Vector A, Vector B)
{
	Vector v = V_cross(V_substract(B,A), V_substract(M,A));
	Vector oz = V_new(0,0,1), oy = V_new(0,1,0), ox = V_new(1,0,0);

	float f = V_dot(v,oz);
	if (f > epsilon)
	{
		return 1;
	}
	else if (f < -epsilon)
	{
		return 0;
	}
	else
	{
		f = V_dot(v,ox);
		if (f > epsilon)
		{
	  		return 1;
		}
		else if (f < -epsilon)
		{
			return 0;
		}
		else
		{
		  f = V_dot(v,oy);
		  if (f > epsilon)
		  {
		  	return 1;
		  }
		  else if (f < -epsilon)
		  {
		    return 0;
		  }
		}
	}

	return 0;
}

int V_segmentsIntersect(Vector p1, Vector p2, Vector q1, Vector q2)
{

}

int V_rayIntersectsSegment(Vector M, Vector u_ray, Vector p1, Vector p2)
{
	int res = 0;
	Vector M2 = V_add(M,u_ray);

	float scalA = V_dot(V_substract(p1,M),u_ray);
	float scalB = V_dot(V_substract(p2,M),u_ray);

	if(V_isOnTheRight(p1,M,M2) == 1 && V_isOnTheRight(p2,M,M2)==0)
	{
	if(scalA > epsilon && scalB > epsilon)
	{
	  res=1;
	}
	}
	else if(V_isOnTheRight(p1,M,M2)==0 && V_isOnTheRight(p2,M,M2)==1)
	{
	if(scalA > epsilon && scalB > epsilon)
	{
	  res=1;
	}
	}

	return res;
}

Vector V_turnAroundY(Vector p, double angle)
{
	//TODO
}

Vector V_turnAroundZ(Vector p, double angle)
{
	//TODO
}

Vector V_projectOnPlane(Vector v, Vector normal)
{
	//TODO
}

double V_decompose(Vector p, Vector u)
{
	//TODO
}

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w)
{
	//TODO
}

void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y)
{
	//TODO
}

Vector V_rotate(Vector p, Vector centre, Vector v1, Vector v2)
{
	//TODO
}