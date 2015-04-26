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