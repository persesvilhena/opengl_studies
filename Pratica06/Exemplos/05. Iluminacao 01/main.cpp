//Exemplo Iluminação 01
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

static int giro=0;

void inicializa(void)
{
     glClearColor(0.0,0.0,0.0,0.0); // RGBA
     glShadeModel(GL_SMOOTH);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_DEPTH_TEST);
}

void desenha(void)
{
     GLfloat posicao[]={0.0,0.0,1.5,1.0};
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glPushMatrix();
       glTranslatef(0.0,0.0,-5.0);
        glPushMatrix();
           glRotated(giro, 1.0,0.0,0.0);
           glLightfv(GL_LIGHT0, GL_POSITION, posicao);
           glTranslated(0.0,0.0,1.5);
           glDisable(GL_LIGHTING);
           glColor3f(0.0,1.0,1.0);
           glEnable(GL_LIGHTING);
       glPopMatrix();
       glutSolidTorus(0.275,0.85,8,15);
     glPopMatrix();
     glFlush();
}

void configuracao(int w, int h)
{
     glViewport(0,0,(GLsizei) w, (GLsizei) h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
       if (button == GLUT_LEFT_BUTTON)
       {
             giro = (giro + 50) % 360;
             glutPostRedisplay();
       }

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Iluminação");
    inicializa();
    glutDisplayFunc(desenha);
    glutReshapeFunc(configuracao);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

