///Exemplo Ilumina��o 04
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>


/// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

/// Fun��o respons�vel pela especifica��o dos par�metros de ilumina��o
void DefineIluminacao (void)
{
	 GLfloat luzAmbiente[4]={25,0.2,0.1,0.1};
	 GLfloat luzDifusa[4]={0.5,0.5,0.5,0.1};
	 GLfloat luzEspecular[4]={1.0, 1.0, 1.0,1.0};
	 GLfloat posicaoLuz[4]={175.0, 175.0, 175.0, 1.0};

	/// Capacidade de brilho do material
	GLfloat especularidade[5]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 20;

	/// Define a reflet�ncia do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

	/// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	/// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	///Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Chama a fun��o que especifica os par�metros de ilumina��o
	DefineIluminacao();

	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidTorus(10,20,25,25);

    glutSwapBuffers();
}


/// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	DefineIluminacao();

	/// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

/// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);
	PosicionaObservador();
}

void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) 		/// Tecla ESC
		exit(0);
}

/// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		/// Salva os par�metros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

/// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void GerenciaMovim(int x, int y)
{
	/// Se pressionar Bot�o Esquerdo
	if(bot==GLUT_LEFT_BUTTON)
	{
		/// Calcula diferen�as e...
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		///... modifica �ngulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}

	/// Se pressionar Bot�o Direito
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		/// Calcula diferen�a e...
		int deltaz = y_ini - y;
		/// ... modifica dist�ncia do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}

	/// Se pressionar Bot�o do Meio
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		/// Calcula diferen�as e...
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		///... modifica posi��es
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
}

void Inicializa (void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_COLOR_MATERIAL);

	///Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);

	/// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);

	/// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	/// Habilita o modelo de tonaliza��o
	glShadeModel(GL_SMOOTH);

	/// Inicializa a vari�vel que especifica o �ngulo da proje��o
	/// perspectiva
	angle=45;

	/// Inicializa as vari�veis usadas para alterar a posi��o do
	/// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 150;
}


int main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(450,450);
	glutCreateWindow("Desenho de um torus 3D com ilumina��o");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc (Teclado);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(GerenciaMovim);
	Inicializa();
	glutMainLoop();
	return 0;
}


