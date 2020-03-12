// Guilherme Xavier e Marcos Balatka
// gcc castelo.c -lglut -lGL -lGLU -lm -o castelo && ./castelo

#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_FLOCOS 500
#define PI 3.1415

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
float radius = 1.0f;
float angle = 0.0f;

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h) {
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(30.0f, fAspect, 1.0, 40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(){
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

	}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y){

    // Refresh the Window


}


void OnDisplay(void){

  GLUquadricObj *pObj = gluNewQuadric();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // +1
  glPushMatrix();

	// Move object back and do in place rotation
	glTranslatef(0.0f, -1.0f, -20.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	gluQuadricNormals(pObj, GLU_SMOOTH);

	// +2
	glPushMatrix();

	glColor3f(1.0f, .3f, .6f);

	// Cilindro frente esquerda
	glPushMatrix();	// Geral
	glTranslatef(-2.0f, 0.0f, 2.0f);

	glPushMatrix(); // Base
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius, 25, 2);
	glPopMatrix();	// Base

	glPushMatrix(); // Parede para tras esquerda
	glTranslatef(0.0, 0.4, 0.0);
	glRotatef(-180.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius*4.2, 2, 25);
	glPopMatrix();	// Parede para tras esquerda

	glPushMatrix(); // Parede para frente direita
	glTranslatef(0.0, 0.4, 0.0);
	glRotatef(-180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius*4.2, 2, 25);
	glPopMatrix();	// Parede para frente direita

	glTranslatef(0.0f, radius, 0.0f);
	// Chapeuzinho
	glPushMatrix(); // Chapeu
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, 0, radius/2, 25, 2);
	glPopMatrix(); // Chapeu

	glPopMatrix(); // Geral

	// Cilindro tras esquerda
	glPushMatrix(); // Geral
	glTranslatef(-2.0f, 0.0f, -2.0f);

	glPushMatrix(); // Base
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius, 25, 2);
	glPopMatrix(); // Base

	glTranslatef(0.0f, radius, 0.0f);
	// Chapeuzinho
	glPushMatrix(); // Chapeu
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, 0, radius/2, 25, 2);
	glPopMatrix(); // Chapeu

	glPopMatrix(); // Geral

	// Cilindro frente direita
	glPushMatrix(); // Geral
	glTranslatef(2.0f, 0.0f, 2.0f);

	glPushMatrix(); // Base
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius, 25, 2);
	glPopMatrix(); // Base

	glTranslatef(0, radius, 0);
	// Chapeuzinho
	glPushMatrix(); // Chapeu
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, 0, radius/2, 25, 2);
	glPopMatrix(); // Chapeu

	glPopMatrix(); // Geral

	// Cilindro tras direita
	glPushMatrix(); // Geral
	glTranslatef(2.0f, 0.0f, -2.0f);

	glPushMatrix(); // Base
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius, 25, 2);
	glPopMatrix(); // Base

	glPushMatrix(); // Parede para tras esquerda
	glTranslatef(0.0, 0.4, 0.0);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius*4.2, 2, 25);
	glPopMatrix();	// Parede para tras esquerda

	glPushMatrix(); // Parede para frente direita
	glTranslatef(0.0, 0.4, 0.0);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, radius*4.2, 2, 25);
	glPopMatrix();	// Parede para frente direita

	glTranslatef(0.0f, radius, 0.0f);
	// Chapeuzinho
	glPushMatrix(); // Chapeu
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, 0, radius/2, 25, 2);
	glPopMatrix(); // Chapeu

	glPopMatrix(); // Geral

	glPushMatrix();

	glPushMatrix(); // Base
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.40f, radius*0.40f, 2*radius, 25, 2);
	glPopMatrix();	// Base
	glPopMatrix();

	glPopMatrix();
	// -1

  // Restore the matrix state
	// -1
  glPopMatrix();
  // Buffer swap
  glutSwapBuffers();

  yRot+= 0.1f;
	if(yRot >= 360)
		yRot = 0;
  glutPostRedisplay();
}


int main(int argc, char *argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modeling with Quadrics");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(OnDisplay);
    init();
    glutMainLoop();

    return 0;

}
