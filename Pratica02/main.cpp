#include <windows.h>
#include <gl/glut.h>

void Desenha(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glClear(GL_COLOR_BUFFER_BIT);
     //glColor3f(0.0f, 0.0f, 1.0f);
	     glBegin(GL_QUADS);
               glVertex2i(100,150);
               glVertex2i(100,100);
               glVertex2i(150,100);
               glVertex2i(150,150);
     glEnd();
     glFlush();
}

void Inicializa (void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
                   if(h == 0) h = 1;
                   glViewport(0, 0, w, h);
                   glMatrixMode(GL_PROJECTION);
                   glLoadIdentity();
                   if (w <= h)
                           gluOrtho2D (0.0f, 350.0f, 0.0f, 350.0f*h/w);
                   else
                           gluOrtho2D (0.0f, 350.0f*w/h, 0.0f, 350.0f);
}

int main(void)
{
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(500,500);
     glutInitWindowPosition(30,30);
     glutCreateWindow("aaaaa");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     Inicializa();
     glutMainLoop();
}
