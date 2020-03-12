// Guilherme Xavier e Marcos Balatka
// gcc snowman.c -lglut -lGL -lGLU -lm -o snowman && ./snowman

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

typedef struct floco {
	float pos[3];
	float vel;
} Floco;

Floco flocos[MAX_FLOCOS];

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

	int i;
	srand(time(NULL));
	
	for(i=0; i<MAX_FLOCOS; i++){
		// Gerar um x aleatorio
		float x = (float) (1.0 / ((rand() % 11) + 1));
		x *= (rand() % 2 ? 1 : -1);
	
		float y = (float) (1.0 / ((rand() % 11) + 1));
		y *= (rand() % 2 ? 1 : -1);

		float z = (float) (1.0 / ((rand() % 11) + 1));
		z *= (rand() % 2 ? 1 : -1);

		flocos[i].pos[0] = x;
		flocos[i].pos[1] = y;
		flocos[i].pos[2] = z;

		float v = (float) (1.0 / ((rand() % 50) + 100));
		flocos[i].vel = v;
	}
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
	glTranslatef(0.0f, -1.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	gluQuadricNormals(pObj, GLU_SMOOTH);

	// Esfera de baixo
	// +2
	glPushMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);

	gluSphere(pObj, radius*0.40f, 50, 25);
	
	// Esfera do meio
	glTranslatef(0.0f, .550f, 0.0f);
	gluSphere(pObj, radius*0.3f, 50, 25);
	
	// Esfera de cima
	glTranslatef(0.0f, 0.45f, 0.0f);
	gluSphere(pObj, radius*0.24f, 50, 25);

	// Olhos
	glColor3f(0.0f, 0.0f, 0.0f);
	
	glTranslatef(0.1f, 0.1f, 0.21f);
	gluSphere(pObj, radius*0.02f, 12, 6);

	glTranslatef(-0.2f, 0.0f, 0.0f);
	gluSphere(pObj, radius*0.02f, 12, 6);

	// Nariz
	glColor3f(1.0f, 127.0/255.0f, 80.0/255.0f);

	glTranslatef(0.1f, -0.12f, 0.0f);
	gluCylinder(pObj, radius*0.04f, 0.0f, 0.3f, 50, 25);

	glPopMatrix();
	// -2

	// Chapeu
	// +2
	glPushMatrix();

	glColor3f(0.0f, 0.0f, 0.0f);

	glTranslatef(0.0f, 1.17f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, radius*0.17f, radius*0.17f, radius*0.4f, 50, 25);
	gluCylinder(pObj, radius*0.27f, radius*0.27f, radius*0.02f, 50, 25);

	// -2
	glPopMatrix();	

    // Restore the matrix state
	// -1
    glPopMatrix();
	
	glPushMatrix();

	glTranslatef(0.0f, 1.0f, -5.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
	int i;

	for(i=0; i<MAX_FLOCOS; i++){
		glPushMatrix();
		glTranslatef(flocos[i].pos[0], flocos[i].pos[1], flocos[i].pos[2]);
		gluSphere(pObj, 0.02f, 12, 6);
		flocos[i].pos[1] -= flocos[i].vel;
		flocos[i].pos[0] += sin(angle)*0.001f;
		flocos[i].pos[0] += cos(i)*0.001f;
		if(flocos[i].pos[1] < -2.5)
			flocos[i].pos[1] = 0.5;
		if(flocos[i].pos[0] < -2 || flocos[i].pos[0] > 2){
			flocos[i].pos[0] *= -1;
			if(flocos[i].pos[0] >= 2)
				flocos[i].pos[0] -= 0.3;
			else if(flocos[i].pos[0] <= -2)
				flocos[i].pos[0] += 0.3;
		}
		glPopMatrix();
	}
	angle+=0.1f;
	glPopMatrix();
    // Buffer swap
    glutSwapBuffers();

    yRot = (GLfloat)((const int)yRot % 360);
    yRot++;

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
