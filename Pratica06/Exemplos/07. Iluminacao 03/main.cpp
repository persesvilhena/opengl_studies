//Exemplo Ilumina��o 03
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat fAspect;
// ----------------------------------------------------------------------------
// Fun��o respons�vel pela especifica��o dos par�metros de ilumina��o
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.0,0.0,0.0,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0}; 		// "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};	// "brilho"

	GLfloat posicaoLuz[4]={0.0, 0.0,100.0, 1.0};
	// {x,y,z,w} onde: se w=0, fonte de luz direcional: posi��o infinita e dire��o dada por (x,y,z).
    //Se w=1, fonte de luz posicional, com posi��o dada por (x,y,z) em coordenada de objeto.

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
    // Define a reflet�ncia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

	GLfloat especMaterial[1]={60};
    // Define a concentra��o do brilho
	glMaterialfv(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
  //  GLfloat luzAmbiente[1]={0.0};
//	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE,luzAmbiente );

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}
//-----------------------------------------------------------------------------
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Chama a fun��o que especifica os par�metros de ilumina��o
	DefineIluminacao();

	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidTorus(20.0, 35.0, 20, 40);

	glFlush();

}
//-----------------------------------------------------------------------------
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) 		// Tecla ESC
		exit(0);
}

//-----------------------------------------------------------------------------
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(45,fAspect,0.5,500);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Posiciona e orienta o observador
	glTranslatef(0,0,-150);

}

//-----------------------------------------------------------------------------
void Inicializa (void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// habilita o uso de cor de material
    glEnable(GL_COLOR_MATERIAL);

	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);

	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);

	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de tonaliza��o de Gouraud
	glShadeModel(GL_SMOOTH);


}

//----------------------------------------------------------------------------

int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(450,450);
	glutCreateWindow("Desenho de um TORUS 3D com ilumina��o");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc (Teclado);
	Inicializa();
	glutMainLoop();
	return 0;
}
