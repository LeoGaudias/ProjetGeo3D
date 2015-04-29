#include "Vector.h"

const float epsilon = 0.00001;

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
	// return V_new((v1.y * v2.z) - (v1.z * v2.y),
	//  (v1.z * v2.x) - (v1.x * v2.z),
	//  (v1.x * v2.y) - (v1.y * v2.x));

	Vector v;
	v.x = v1.y*v2.z - v1.z*v2.y;
	v.y = v1.x*v2.z - v1.z*v2.x;
	v.z = v1.x*v2.y - v1.y*v2.x;
	return v;
}

float  V_dot(Vector v1, Vector v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float  V_length(Vector v)
{
	return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

Vector V_unit(Vector v)
{
	float lon=V_length(v);
	return V_new(v.x/lon,v.y/lon,v.z/lon);
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
	int res=0;
	
	if(V_isOnTheRight(q1,p1,p2)+V_isOnTheRight(q2,p1,p2)==1)
	{
		if(V_isOnTheRight(p1,q1,q2)+V_isOnTheRight(p2,q1,q2)==1)
		{
			res=1;
		}
	}
	
	return res;
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
	return V_new(p.x*cos(angle)+p.z+sin(angle),p.y,-p.x*sin(angle)+p.z*cos(angle));
}

Vector V_turnAroundZ(Vector p, double angle)
{
	return V_new(p.x*cos(angle)-p.y*sin(angle),p.x*sin(angle)+p.y*cos(angle),p.z);
}

Vector V_projectOnPlane(Vector v, Vector normal)
{
	//TODO
	return V_new(0,0,0);
}

double V_decompose(Vector p, Vector u)
{
	return V_dot(p,u)*V_length(u);
}

Vector V_recompose(double x, double y, double z, Vector u, Vector v, Vector w)
{
	Vector vec=V_add(V_multiply(y,v),V_multiply(z,w));
	return V_add(V_multiply(x,u),vec);
}

void V_uxUyFromUz(Vector u_z, Vector *u_x, Vector *u_y)
{
	if(u_z.x==u_z.z && u_z.x==0)
	{
		*u_x=V_new(0,0,u_z.y);
		*u_y=V_new(u_z.y,0,0);
	}
	else
	{
		*u_x=V_multiply(V_length(u_z),V_unit(V_cross(V_new(0,1,0),u_z)));
		*u_y=V_multiply(V_length(u_z),V_unit(V_cross(*u_x,u_z)));
	}
}

Vector V_rotate(Vector p, Vector centre, Vector v1, Vector v2)
{
	// pas sûr de l'utilité des vecteurs unitaires ...
	Vector u1=V_unit(v1);
	Vector u2=V_unit(v2);

	Vector r1x,r1y, r2x, r2y;
	V_uxUyFromUz(u1,&r1x,&r1y);
	V_uxUyFromUz(u2,&r2x,&r2y);

	double x=V_decompose(p,r1x);
	double y=V_decompose(p,r1y);
	double z=V_decompose(p,u1);

	Vector recomp=V_recompose(x,y,z,r2x,r2y,u2);
	return V_add(centre,recomp);
}
