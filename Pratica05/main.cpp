#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat fAspect;
void casinha(void){
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireCube(19);

	glTranslatef(0.0f, 10.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.3f, 1.3f, 1.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCone(10,20,4,2);
}

void rosquinha(void){
    glTranslatef(0.0f, 10.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.3f, 1.3f, 1.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glutWireTorus(10.0f,20.0f,20.0f,100.0f);
    glPopMatrix();

    glTranslatef(0.0f, 20.0f, 0.0f);
    glScalef(2.0f, 2.0f, 2.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutWireSphere(10.0f,50.0f,10.0f);

    glTranslatef(0.0f, 10.0f, 0.0f);
	//glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	//glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(1.3f, 1.3f, 1.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCone(7,20,40,2);

    glPopMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
   // glScalef(2.0f, 2.0f, 2.0f);
    glColor3f(0.0f, 0.5f, 0.0f);
    glutSolidSphere(2.0f,50.0f,10.0f);

    glPopMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);
    //glScalef(2.0f, 2.0f, 2.0f);
    glColor3f(0.0f, 0.5f, 0.0f);
    glutSolidSphere(2.0f,50.0f,10.0f);

    glPopMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);
    //glScalef(2.0f, 2.0f, 2.0f);
    glColor3f(0.0f, 0.5f, 0.0f);
    glutSolidSphere(2.0f,50.0f,10.0f);

}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

/*	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES); // para desennaosei152511har o objeto 2D
        glVertex2i(0,0);
        glVertex2i(15,5);
        glVertex2i(10,15);
    glEnd();
*/
//casinha();
rosquinha();



	glFlush();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;

	//Área de Projeção/Saída
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Características de Projeção/Pespectiva
	gluPerspective(50,fAspect,0.5,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Características do Observador
	gluLookAt(100,100,100, 10,10,10, 0,1,0);
}

void Inicializa (void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(1.0);
}

int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(450,450);
	glutCreateWindow("Coco da galera - cubo");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
	return 0;
}
