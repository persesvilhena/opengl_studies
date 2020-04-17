//Exemplo com mouse
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, corR, corG, corB;
GLfloat obsX, obsY, obsZ;


void Desenha(void)
{

    glMatrixMode(GL_MODELVIEW); //Define que as fun��es usadas a ap�s a chamada desta rotina ir�o referir-se ao aos objetos do cen�rio 3D e n�o ao observador.
	glLoadIdentity();
    gluLookAt(60,40,50, 5,15,5, 0,1,0);

    glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(corR, corG, corB);

   	glTranslatef(obsX,obsY,obsZ);

    glRotatef(rotX,0.0f,0.0f,1.0f);

    glutWireCube(20);

    // Executa os comandos OpenGL
    glFlush();

}

void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) 		// Tecla ESC
		exit(0);
}

// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN) // pressionado
	{
		obsX = 10;
		obsY = 10;
		obsZ = 10;

	}

	if(state==GLUT_UP) // liberado
	{

		obsX = 0;
		obsY = 0;
		obsZ = 0;


	}

    if(button==GLUT_RIGHT_BUTTON) // bot�o direito pressionado
	{
        rotX = 30.0f;
       // corR = 1.0;
       // corG = 0.0;
        //corB = 0.0;

    }

    if(button==GLUT_LEFT_BUTTON) // bot�o esquerdo pressionado
	{
        rotX = 60.0f;
    }

    if(button==GLUT_MIDDLE_BUTTON) // bot�o do meio pressionado
    {
        rotX = 0;
    }


   	glutPostRedisplay();
}


void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle,fAspect,0.5,500);


}

void Inicializa (void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicializa a vari�vel que especifica o �ngulo da proje��o - perspectiva
	angle=45;

	// Inicializa as vari�veis usadas para alterar a posi��o do observador virtual
    rotX = 0.0;
    obsX = 0;
	obsZ = 0;
    obsY = 0;

    corR = 0.0 ;
    corG = 0.0;
    corB = 1.0;
}

int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(5,5);
	glutInitWindowSize(450,450);
	glutCreateWindow("Desenho de um torus 3D com movimenta��o");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc (Teclado);
	glutMouseFunc(GerenciaMouse);
	Inicializa();
	glutMainLoop();
	return 0;
}
