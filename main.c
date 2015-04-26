
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

int dim = DIM2;

/* dimensions de la fenetre */
int width = 650;
int height = 650;

/*var globale*/
Vector p_aim;
Polygon P;
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
	glColor3d(255,0,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(1,0,0);
	glEnd();

	glColor3d(0,255,0);
	glBegin(GL_LINES);
	glVertex3d(0,0,0);
	glVertex3d(0,1,0);
	glEnd();

	glColor3d(0,0,255);
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
		//glOrtho(-300,300,-300,300,-1,1);
		glOrtho(-1,1,-1,1,0,0);
	}
	else if(dim==DIM3)
	{
		//glOrtho(-300,300,-300,300,-300,300);
		glOrtho(-1,1,-1,1,-1,1);
	}
	else
	{
		gluPerspective( 40, (float)width/height, 1, 100);
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
			P_draw(&P,width,height);
		}
	}
	else
	{
		drawline(&P);
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

	glutPostRedisplay();
}

//------------------------------------------------------------

void special(int keycode, int x, int y)
{
	int mod = glutGetModifiers();
	switch(keycode)
    {
    case GLUT_KEY_UP        : printf("Flèche haut\n"); break;
    case GLUT_KEY_DOWN      : printf("Flèche bas\n"); break;
    case GLUT_KEY_LEFT      : printf("Flèche gauche\n"); break;
    case GLUT_KEY_RIGHT     : printf("Flèche droite\n"); break;
    case GLUT_KEY_PAGE_UP   : printf("Flèche avant\n"); break;
    case GLUT_KEY_PAGE_DOWN : printf("Flèche arriere\n"); break;
    default : fprintf(stderr,"function special : unknown keycode %d\n",keycode); break;
    }
	if(mod==GLUT_ACTIVE_CTRL)
		glLightfv(GL_LIGHT0, GL_POSITION, p_light);
}

//------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
	printf("Clic at %d %d \n",x,y);

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
	//M = NULL;

	glutMainLoop();

    return 0;
}
