#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#define width 1024
#define height 768

void OnDisplay () {
    glClearColor (0.0f, 0.0f, 0.25f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Bola superior
    glBegin( GL_POLYGON );
        for(int i=0; i<100; i++){
            float x = cos(2*3.1415926535*i/100);
            float y = sin(2*3.1415926535*i/100);
            // glVertex2f(13,15);
            glVertex2f( x/width*100 , y/height*100 +0.39 +0.3);
        }
    glEnd();

    // Bola do meio
    glBegin( GL_POLYGON );
        for(int i=0; i<100; i++){
            float x = cos(2*3.1415926535*i/100);
            float y = sin(2*3.1415926535*i/100);
            // glVertex2f(13,15);
            glVertex2f( x/width*100*2 , y/height*100*2 +0.35);
        }
    glEnd();

    // Bola inferior
    glBegin( GL_POLYGON );
        for(int i=0; i<100; i++){
            float x = cos(2*3.1415926535*i/100);
            float y = sin(2*3.1415926535*i/100);
            // glVertex2f(13,15);
            glVertex2f( x/width*100*3 , y/height*100*3 -0.64+0.40 );
        }
    glEnd();

    // Olho direito
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin( GL_POLYGON );
        for(int i=0; i<100; i++){
            float x = cos(2*3.1415926535*i/100);
            float y = sin(2*3.1415926535*i/100);
            // glVertex2f(13,15);
            glVertex2f( x/width*5*3 + 0.04, y/height*5*3 +0.75 );
        }
    glEnd();

    // Olho esquerdo
    glBegin( GL_POLYGON );
        for(int i=0; i<100; i++){
            float x = cos(2*3.1415926535*i/100);
            float y = sin(2*3.1415926535*i/100);
            // glVertex2f(13,15);
            glVertex2f( x/width*5*3 - 0.04, y/height*5*3 +0.75 );
        }
    glEnd();

    // Nariz
    glColor3f(1.0, 165.0/255.0, 0.0f);
    glBegin( GL_POLYGON );
        for(int i=0; i<100; i++){
            float x = cos(2*3.1415926535*i/100);
            float y = sin(2*3.1415926535*i/100);
            // glVertex2f(13,15);
            glVertex2f( x/width*5*3, y/height*5*3 +0.68 );
        }
    glEnd();

    // Chapeu
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin( GL_QUAD_STRIP );
        glVertex2f (-0.10f, -0.10f);
        glVertex2f (0.10f, -0.10f);
        glVertex2f (0.10f, 0.10f);
        glVertex2f (-0.10f, 0.10f);
    glEnd();
    glFlush ();

}
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1024,768);
    glutCreateWindow("Boneco de neve");
    glutDisplayFunc(OnDisplay);

    glutMainLoop();
}
