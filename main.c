
/*======================================================*\
  Wednesday September the 25th 2013
  Arash HABIBI
  Question1.c
\*======================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include "Vector.h"
#include "Polygon.h"
//#include "QuadMesh.h" ??
#include "Mesh.h"

#define DIM2 0
#define DIM3 1

#define WIREFRAME 0
#define FLAT      1
#define SHADE     2
int draw = WIREFRAME;

int dim = DIM2;
int rev=0;

/* dimensions de la fenetre */
int width = 650;
int height = 650;

/*var globale*/
Vector p_aim;
float phi = -20;
float theta = 20;
Polygon P;
Mesh m;
//Mesh ou QuadMesh M
int dessiner=1; // on peut dessiner

GLfloat p_light[4];

//------------------------------------------------------------

// void drawLine(Vector p1, Vector p2)
// {
// 	glBegin(GL_LINES);
// 	glVertex3d(p1.x,p1.y,p1.z);
// 	glVertex3d(p2.x,p2.y,p2.z);
// 	glEnd();
// }

void drawline(Polygon *P)
{
	int i;
	glBegin(GL_LINE_STRIP);
	for(i = 0; i < P->_nb_vertices; ++i)
	{
		glVertex3f(P->_vertices[i].x,P->_vertices[i].y,P->_vertices[i].z);
	}
	glEnd();
}

//------------------------------------------------------------

void drawRepere()
{
	glColor3d(1,0,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(1,0,0);
	glEnd();

	glColor3d(0,1,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,1,0);
	glEnd();

	glColor3d(0,0,1);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,0,1);
	glEnd();
}

//------------------------------------------------------------
void initShade()
{
	GLfloat mat_diffuse[] = {1,1,1,1.0};
	GLfloat mat_ambient[] = {0.1,0.1,0.1,0.0};

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, p_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}


/*************************************************************************/
/* Fonctions callback */
/*************************************************************************/

void display()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(dim==DIM2)
	{
		glOrtho(-1,1,-1,1,-1,1);
	}
	else
	{
		gluPerspective( 40, (float)width/height, 1, 100);
		glTranslatef(p_aim.x,p_aim.y,p_aim.z);
		glRotatef(theta,1,0,0);
		glRotatef(phi,0,1,0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Dessiner ici
	// ...

	//chooseRandomColor();
	if(P._is_convex)
	{
		glColor3d(255,0,0);
	}
	else
	{
		glColor3d(0,0,255);
	}
	if(P._is_filled)
	{
		if(P._nb_vertices < 3)
		{
			drawline(&P);
		}
		else
		{
			P_draw(&P);
		}
	}
	else
	{
		drawline(&P);
	}

	if(rev==1)
	{
		glColor3d(255,255,255);
		M_draw(&m);
	}

	// Repere du monde

	drawRepere();

	glutSwapBuffers();
}

//------------------------------------------------------------

void keyboard(unsigned char keycode, int x, int y)
{
	// printf("Touche frapee : %c (code ascii %d)\n",keycode, keycode);

	if (keycode==27) // ECHAP
		exit(0);
	if (keycode=='c' || keycode=='C')
	{
		if(P._is_filled)
		{
			P._is_filled = 0;
		}
		else
		{
			P._is_filled = 1;
		}
	}
	else if(keycode=='r' || keycode=='R')
	{	
		if(dim == DIM2)
		{
			dim=DIM3;
			M_init(&m);
		}
		else
		{
			dim=DIM2;
		}

		if(rev==0 && dim==DIM3)
		{
			//M_revolution(&m,&P,12);
			M_perlinExtrude(&m,&P,128);
			rev=1;
		}
	}
	else if(keycode=='a' || keycode=='A')
	{
		switch(draw)
		{
			case WIREFRAME :
				draw = FLAT;
				P._is_filled = 0;
				glDisable(GL_LIGHTING);
				glEnable(GL_DEPTH_TEST);
				break;

			case FLAT :
				draw = SHADE;
				P._is_filled = 1;
				initShade();
				break;

			case SHADE :
				draw = WIREFRAME;
				P._is_filled = 1;
				glDisable(GL_LIGHTING);
				glDisable(GL_DEPTH_TEST);
				break;
		}
	}

	glutPostRedisplay();
}

//------------------------------------------------------------

void special(int keycode, int x, int y)
{
	int mod = glutGetModifiers();
	switch(keycode)
    {
    case GLUT_KEY_UP        : if(mod==GLUT_ACTIVE_CTRL) p_light[1]+=1; else if(mod==GLUT_ACTIVE_SHIFT) p_aim.y+=.1; else theta-= 10; break;
    case GLUT_KEY_DOWN      : if(mod==GLUT_ACTIVE_CTRL) p_light[1]-=1; else if(mod==GLUT_ACTIVE_SHIFT) p_aim.y-=.1; else theta+= 10; break;
    case GLUT_KEY_LEFT      : if(mod==GLUT_ACTIVE_CTRL) p_light[0]-=1; else if(mod==GLUT_ACTIVE_SHIFT) p_aim.x-=.1; else phi-= 10; break;
    case GLUT_KEY_RIGHT     : if(mod==GLUT_ACTIVE_CTRL) p_light[0]+=1; else if(mod==GLUT_ACTIVE_SHIFT) p_aim.x+=.1; else phi+= 10; break;
    case GLUT_KEY_PAGE_UP   : if(mod==GLUT_ACTIVE_CTRL) p_light[2]-=1; else p_aim.z-=1; break;
    case GLUT_KEY_PAGE_DOWN : if(mod==GLUT_ACTIVE_CTRL) p_light[2]+=1; else p_aim.z+=1; break;
    default : fprintf(stderr,"function special : unknown keycode %d\n",keycode); break;
    }
	if(mod==GLUT_ACTIVE_CTRL)
		glLightfv(GL_LIGHT0, GL_POSITION, p_light);

	glutPostRedisplay();
}

//------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
	//printf("Clic at %d %d \n",x,y);

	switch(button)
    {
	    case GLUT_LEFT_BUTTON :
			if(state==GLUT_DOWN)
			{
				Vector pos=V_new((double)(x-width/2)/(double)(width/2),(double)(-y+height/2)/(double)(height/2),0);
				if(dessiner==1)
				{
					fprintf(stderr,"Clic gauche\n");
					//Vector pos = V_new(x - width/2,height/2 - y,0);

					int i;

					int inter = 0;
					for(i=0;i<P._nb_vertices-1;i++)
					{
						printf("intersect %d\n", V_segmentsIntersect(P._vertices[i], P._vertices[i+1],P._vertices[P._nb_vertices-1] , pos )+V_segmentsIntersect(P._vertices[i+1], P._vertices[i],P._vertices[P._nb_vertices-1] , pos ));
						if(V_segmentsIntersect(P._vertices[i], P._vertices[i+1],P._vertices[P._nb_vertices-1] , pos)+V_segmentsIntersect(P._vertices[i+1], P._vertices[i],P._vertices[P._nb_vertices-1] , pos)>1)
						{
							fprintf(stderr,"Erreur, segment qui se croisent !\n");
							inter=1;
							break;
						}
					}

					if(inter==0)
					{
						P_addVertex(&P, pos);
				
						printf("P is -> %d\n",P_isConvex(&P));
						P._is_convex = P_isConvex(&P);
						//P_print(&P,"affichage des valeurs");
					}
				}
				else
				{
					printf("Ajout de sommet désactivé, clic du mileu pour le réactiver, ");
					printf("inside : %d\n",P_isInside(&P,pos));
				}
			}
		break;

	    case GLUT_MIDDLE_BUTTON :
			if(state==GLUT_DOWN)
			{
				fprintf(stderr,"Clic milieu\n");
				if(dessiner==1)
				{
					dessiner=0;
					printf("Dessin terminé, clique du milieu pour continuer\n");
				}
				else if(dessiner==0)
				{
					dessiner=1;
				}
			}
		break;

	    case GLUT_RIGHT_BUTTON :
			if(state==GLUT_DOWN)
			{
				fprintf(stderr,"Clic droit.\n");
				P_removeLastVertex(&P);
				P._is_convex = P_isConvex(&P);
				//P_print(&P,"affichage des valeurs après ");
			}
		break;
    }

	glutPostRedisplay();
}

//------------------------------------------------------------

void idle()
{
	// animation du personnage ici

	glutPostRedisplay();
}

/*************************************************************************/
/* Fonction principale */
/*************************************************************************/

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
    glutCreateWindow("Transformations matricielles");
    glViewport(0, 0, width, height);
	glClearColor(0,0,0,0);

	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	p_light[0]=-10.0;
	p_light[1]=20.0;
	p_light[2]=0.0;
	p_light[3]=1.0;

	p_aim = V_new(0,0,-2.75);
	//P = P_new();
	P_init(&P);
	M_init(&m);
	/*Vector p000 = V_new(-0.5,-0.5,-0.5);
	Vector p001 = V_new(-0.5,-0.5, 0.5);
	Vector p010 = V_new(-0.5, 0.5,-0.5);
	Vector p011 = V_new(-0.5, 0.5, 0.5);
	Vector p100 = V_new( 0.5,-0.5,-0.5);
	Vector p101 = V_new( 0.5,-0.5, 0.5);
	Vector p110 = V_new( 0.5, 0.5,-0.5);
	Vector p111 = V_new( 0.5, 0.5, 0.5);

	m._nb_quads = 6;
	m._quads[0] = Q_new(p010,p011,p111,p110);  // top
	m._quads[1] = Q_new(p000,p100,p101,p001);  // bottom
	m._quads[2] = Q_new(p110,p111,p101,p100);  // right
	m._quads[3] = Q_new(p000,p001,p011,p010);  // left
	m._quads[4] = Q_new(p111,p011,p001,p101);  // front
	m._quads[5] = Q_new(p000,p010,p110,p100);  // back*/
	// P_addVertex(&P,V_new(-0.8,-0.8,0));
	// P_addVertex(&P,V_new(-0.8,0.8,0));
	// P_addVertex(&P,V_new(0.8,0.8,0));
	// P_addVertex(&P,V_new(0.8,-0.8,0));
	// M_init(&m);
	//M = NULL;

	glutMainLoop();

    return 0;
}
