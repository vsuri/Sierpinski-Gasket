/* 
 *
 * Vinay Suri
 * COEN 290
 * sphere.c
 *
*/


/* Recursive subdivision of tetrahedron to form a sphere */

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

typedef float point[3];

/* initial triangle */

/* Roughly a tetrahedron on the unit sphere

 Vertex 0, x= 0.000, y= 0.000, z= 1.000 
 Vretex 1, x= 0.943, y= 0.000, z=-0.333 
 Vertex 2, x=-0.471, y= 0.816, z=-0.333 
 Vertex 3, x=-0.471, y=-0.816, z=-0.333

*/

point vertex[4] = { { 0.0, 0.0, 1.0 }, { 0.943, 0.0, -0.333 }, { -0.471, 0.816, -0.333 }, { -0.471, -0.816, -0.333 } }; 

// Change depth of recursion
int depth = 5;

void triangle(point a, point b, point c)

/* display one triangle  */
{
    glBegin(GL_TRIANGLES);
       glVertex2fv(a);
       glVertex2fv(b);
       glVertex2fv(c);
    glEnd();
}

// normalize a vector
void normalize(point v)
{

	double d = 0.0;
	int i;
	for (i =0; i < 3; i++)
		d+=v[i]*v[i];
	d = sqrt(d);
	if(d>0.0)
		for(i=0; i<3; i++)
			v[i]/=d;
}

void divide_triangle(point a, point b, point c, int m)
{

/* triangle subdivision using vertex numbers */

    point v0, v1, v2;
    int j;
    if(m>0) 
    {
        for(j=0; j<3; j++) v0[j]=(a[j]+b[j])/2;
	normalize(v0);

        for(j=0; j<3; j++) v1[j]=(a[j]+c[j])/2;
	normalize(v1);

        for(j=0; j<3; j++) v2[j]=(b[j]+c[j])/2;
	normalize(v2);
        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
	divide_triangle(v0, v1, v2, m-1);
    }
    else(triangle(a,b,c)); /* draw triangle at end of recursion */
}

void tetra (int m)
{
	// Divide each face of the tetrahedron
	divide_triangle(vertex[0], vertex[1], vertex[2], m);
	divide_triangle(vertex[3], vertex[0], vertex[1], m);
	divide_triangle(vertex[2], vertex[3], vertex[0], m);
	divide_triangle(vertex[1], vertex[2], vertex[3], m);

}

int j;
//point new, old={250,100,250}; 

void clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
}

void display(void)

/* computes and plots a single new point */

{
	glClear(GL_COLOR_BUFFER_BIT);
	tetra(depth);
    glFlush();




}


void mouse(int btn, int state, int x, int y)
{
if(btn==GLUT_LEFT_BUTTON&state==GLUT_DOWN)  glutIdleFunc(display);
if(btn==GLUT_MIDDLE_BUTTON&state==GLUT_DOWN)   glutIdleFunc(NULL);
if(btn==GLUT_RIGHT_BUTTON&state==GLUT_DOWN)   exit(0);
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Sphere");

	glutIdleFunc (display);
	glutMouseFunc (mouse);  
	glClearColor(1.0, 1.0, 1.0, 0.0); /* white background */
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(20.0, 20.0, 20.0, 20.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glutDisplayFunc(clear);
	glutMainLoop();
}

