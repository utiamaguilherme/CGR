#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TRONCO 5.0
#define TAM_BRACO 3.0
#define BRACO_INF 2.0
#define PE_SUPERIOR_RAIO  0.5
#define PERNA_INF_RAIO  0.5
#define PERNA_INF_ALTURA 2.0
#define PERNA_SUP_ALTURA 3.0
#define TRONCO_RAIO 1.0
#define BRACO_INF_RAIO  0.5
#define BRACO_SUP_RAIO  0.5
#define CABECA_ALTURA 1.5
#define CABECA_RAIO 1.0

typedef float point[3];

static GLint angle = 2;

GLUquadricObj *t;

void left_upper_leg(){
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(t,PE_SUPERIOR_RAIO, PE_SUPERIOR_RAIO, PERNA_SUP_ALTURA,10,10);
   glPopMatrix();
}

void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.25, 0.0);

    //torso
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,TRONCO_RAIO, TRONCO_RAIO, TRONCO,10,10);
    glPopMatrix();
    glPushMatrix();

    //cabeça
    glTranslatef(0.0, TRONCO+0.5*CABECA_ALTURA, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.5*CABECA_ALTURA, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.5*CABECA_ALTURA,0.0);
    glScalef(CABECA_RAIO, CABECA_ALTURA, CABECA_RAIO);
    gluSphere(t,1.0,10,10);
    glPopMatrix();

    //braco inf dir
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TRONCO_RAIO+BRACO_INF_RAIO), 0.9*TRONCO, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,BRACO_INF_RAIO, BRACO_INF_RAIO, TAM_BRACO,10,10);
    glPopMatrix();

    //braco sup esq
    glTranslatef(0.0, TAM_BRACO, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,BRACO_SUP_RAIO, BRACO_SUP_RAIO, BRACO_INF,10,10);
    glPopMatrix();

    //braco dir inf
    glPopMatrix();
    glPushMatrix();
    glTranslatef(TRONCO_RAIO+BRACO_INF_RAIO, 0.9*TRONCO, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,BRACO_INF_RAIO, BRACO_INF_RAIO, TAM_BRACO,10,10);
    glPopMatrix();

    //braco sup direito
    glTranslatef(0.0, TAM_BRACO, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,BRACO_SUP_RAIO, BRACO_SUP_RAIO, BRACO_INF,10,10);
    glPopMatrix();

    //perna sup esquerda
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TRONCO_RAIO+PE_SUPERIOR_RAIO), 0.1*PERNA_SUP_ALTURA, 0.0);
    glRotatef(180.0, 1.0, 0.0, 0.0);

    /* glPushMatrix();
    *  glRotatef(-90.0, 1.0, 0.0, 0.0);
    *  gluCylinder(rla,BRACO_SUP_RAIO, BRACO_SUP_RAIO, BRACO_INF,10,10);
    *  glPopMatrix();*/
    left_upper_leg();

    //perna esq inf
    glTranslatef(0.0, PERNA_SUP_ALTURA, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,PERNA_INF_RAIO, PERNA_INF_RAIO, PERNA_INF_ALTURA,10,10);
    glPopMatrix();

    //perna superior direita
    glPopMatrix();
    glPushMatrix();
    glTranslatef(TRONCO_RAIO+PE_SUPERIOR_RAIO, 0.1*PERNA_SUP_ALTURA, 0.0);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,PE_SUPERIOR_RAIO, PE_SUPERIOR_RAIO, PERNA_SUP_ALTURA,10,10);
    glPopMatrix();

    //perna direita inf
    glTranslatef(0.0, PERNA_SUP_ALTURA, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,PERNA_INF_RAIO, PERNA_INF_RAIO, PERNA_INF_ALTURA,10,10);
    glPopMatrix();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
            10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
            10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
        GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess={100.0};
        GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
        GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
        GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
        GLfloat light_position[]={10.0, 10.0, 10.0, 0.0};

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glColor3f(0.0, 0.0, 0.0);

/* allocate quadrics with filled drawing style */

        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("robot");
    init();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
}
