// gcc snowman.cpp -lglut -lGL -lGLU -o  snowman && ./snowman
#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <utility>

#define PI 3.14159265

float angulo = 0.0;

std::pair<float, int> oscilacao1 = std::make_pair(0.0, 0);
std::pair<float, int> oscilacao2 = std::make_pair(0.0, 0);

void drawCube(float side);

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 5.0, 1.0,
             0.0, 0.0, 1.0,
             0.0, 0.0, 1.0);

    angulo += 0.5;

    glRotated(angulo, 0, 0, 1);

    //Oscilação 60
    if(oscilacao1.first >= 60)
        oscilacao1.second = 1;
    else if(oscilacao1.first <= -60)
        oscilacao1.second = 0;

    if(oscilacao1.second == 0)
        oscilacao1.first += 0.7;
    else
        oscilacao1.first -= 0.7;

    //Oscilação 30
    if(oscilacao2.first >= 30)
        oscilacao2.second = 1;
    else if(oscilacao2.first <= -30)
        oscilacao2.second = 0;

    if(oscilacao2.second == 0)
        oscilacao2.first += 0.3;
    else
        oscilacao2.first -= 0.3;


    glColor3f(1.0, 1.0, 1.0); //branco

    glPushMatrix();
        //Rotaciona a perna 60
        glTranslatef(0.2, 0.0, 0.9);
        glRotated(oscilacao1.first, 1.0, 0.0, 0.0);
        glTranslatef(-0.2, 0.0, -0.9);

        glPushMatrix();
            glTranslatef(0.2, 0.0, 0.55);
            glScalef(1.0, 1.0, 2.0);
            drawCube(0.15);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.2, 0.0, 0.55);
            glRotated(oscilacao2.first, 1.0, 0.0, 0.0);
            glTranslatef(-0.2, 0.0, -0.55);
            glPushMatrix();
                glTranslatef(0.2, -0.1, 0.1);
                glRotated(-20, 1.0, 0.0, 0.0);
                glScalef(1.0, 1.0, 2.0);
                drawCube(0.15);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();

    glPushMatrix();
        //Rotaciona a perna intercalando

        glTranslatef(0.2, 0.0, 0.9);
        glRotated(oscilacao1.first, 1.0, 0.0, 0.0);
        glTranslatef(-0.2, 0.0, -0.9);

        glPushMatrix();
            glTranslatef(-0.2, 0.0, 0.55);
            glScalef(1.0, 1.0, 2.0);
            drawCube(0.15);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.2, 0.0, 0.55);
            glRotated(-oscilacao2.first, 1.0, 0.0, 0.0);
            glTranslatef(0.2, 0.0, -0.55);
            glPushMatrix();
                glTranslatef(-0.2, -0.1, 0.1);
                glRotated(-20, 1.0, 0.0, 0.0);
                glScalef(1.0, 1.0, 2.0);
                drawCube(0.15);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Desenha torso esticando um cubo
    glPushMatrix();
        glTranslatef(0.0, 0.0, 1.4);
        glScalef(1.8, 1.0, 2.3);
        drawCube(0.25);
    glPopMatrix();


    glPushMatrix();
        //Rotaciona o braço oscilando entre 60 e -60 graus
        glTranslatef(0.6, 0.0, 1.8);
        glRotated(oscilacao1.first, 1.0, 0.0, 0.0);
        glTranslatef(-0.6, 0.0, -1.8);

        //Desenha braço esticando um cubo
        glPushMatrix();
            glTranslatef(0.6, 0.0, 1.6);
            glScalef(1.0, 1.0, 2.0);
            drawCube(0.15);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.6, 0.0, 1.0);
            glRotated(-oscilacao2.first, 1.0, 0.0, 0.0);
            glTranslatef(-0.6, 0.0, -1.0);
            glPushMatrix();
                glTranslatef(0.6, 0.1, 1.1);
                glRotated(30, 1.0, 0.0, 0.0);
                glScalef(1.0, 1.0, 1.8);
                drawCube(0.15);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        //Rotaciona o braço 60
        glTranslatef(-0.6, 0.0, 1.8);
        glRotated(oscilacao1.first, 1.0, 0.0, 0.0);
        glTranslatef(0.6, 0.0, -1.8);

        //Desenha braço esticando um cubo
        glPushMatrix();
            glTranslatef(-0.6, 0.0, 1.6);
            glScalef(1.0, 1.0, 2.0);
            drawCube(0.15);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-0.6, 0.0, 1.0);
            glRotated(oscilacao2.first, 1.0, 0.0, 0.0);
            glTranslatef(0.6, 0.0, -1.0);
            glPushMatrix();
                glTranslatef(-0.6, 0.1, 1.1);
                glRotated(30, 1.0, 0.0, 0.0);
                glScalef(1.0, 1.0, 1.8);
                drawCube(0.15);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    //Desenha cabeça
    glPushMatrix();
        glTranslatef(0.0, 0.0, 2.2);
        drawCube(0.25);
    glPopMatrix();

    //Desenha antena
    glPushMatrix();
        glTranslatef(0.0, 0.0, 2.6);
        glScalef(1.0, 1.0, 4.0);
        drawCube(0.025);
    glPopMatrix();


    glColor3f(1.0, 0.0, 0.0);

    //luz da antena
    glPushMatrix();
        glTranslatef(0.0, 0.0, 2.7);
        drawCube(0.025);
    glPopMatrix();

    glColor3f(1.0, 1.0, 0.0);

    //olho direito
    glPushMatrix();
        glTranslatef(0.1, 0.21, 2.2);
        drawCube(0.05);
    glPopMatrix();

    //olho esquerdo
    glPushMatrix();
        glTranslatef(-0.1, 0.21, 2.2);
        drawCube(0.05);
    glPopMatrix();


    glFlush();
    glutSwapBuffers();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Robo Articulado");

    glutDisplayFunc(display);
    glutIdleFunc( display );

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat) 800 / 600, 2.0f, 15.0f);
    glMatrixMode(GL_MODELVIEW);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.0, 1.0, 0.0, 1.0);

    GLfloat diffuse[] =  {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {1.0, 1.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();

    return 0;
}

void drawCube(float side)
{
    glBegin(GL_QUADS);

        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-side, side, side);
        glVertex3f(side, side, side);
        glVertex3f(side, side, -side);
        glVertex3f(-side, side, -side);

        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(side, -side, side);
        glVertex3f(side, side, side);
        glVertex3f(-side, side, side);
        glVertex3f(-side, -side, side);

        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(side, side, -side);
        glVertex3f(side, side, side);
        glVertex3f(side, -side, side);
        glVertex3f(side, -side, -side);

        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-side, -side, side);
        glVertex3f(-side, side, side);
        glVertex3f(-side, side, -side);
        glVertex3f(-side, -side, -side);

        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(side, -side, side);
        glVertex3f(-side, -side, side);
        glVertex3f(-side, -side, -side);
        glVertex3f(side, -side, -side);

        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(side, side, -side);
        glVertex3f(side, -side, -side);
        glVertex3f(-side, -side, -side);
        glVertex3f(-side, side, -side);

    glEnd();
}
