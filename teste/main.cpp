// Inclus�o das bibliotecas com as fun��es utilizadas;
// Nos programas desenvolvidos para SO Windows � necess�rio incluir...
// ...a biblioteca <windows.h> antes das bibliotecas do OpenGL

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat fAspect;

void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   // Limpa a janela de visualiza��o com a cor de fundo especificada

/*
    glColor3f(0.0f, 0.0f, 1.0f);    // Determina a cor que ser�o constru�dos os objetos
    glBegin(GL_TRIANGLES);          // Determina o in�cio da constru��o dos objetos (Tri�ngulos)
               glVertex2i(100,100);     // Especifica as coordenadas X,Y do primeiro ponto,
               glVertex2i(200,300);     // Especifica as coordenadas X,Y do segundo ponto,
               glVertex2i(300,100);     // Especifica as coordenadas X,Y do terceiro ponto,
    glEnd();
*/

    glMatrixMode(GL_PROJECTION);        // Define o tipo de proje��o e/ou com qual matriz vai se trabalhar: GL_PROJECTION:Matriz de proje��o
	glLoadIdentity();                   // Define o par�metro de visualiza��o. Inicializa o sistema de coordenadas antes da execu��o de qualquer opera��o da manipula��o de matrizes

	gluPerspective(20,fAspect,0.5,500);
	// fovY = Especifica o �ngulo de visualiza��o em graus, na dire��o y.
	// fAspect = � a raz�o de aspecto que determina a area de visualiza��o na dire��o x.
	// zNear = Define a dist�ncia do observador at� o plano frontal
	// zFar = Define a dist�ncia do observador at� o plano traseiro

	gluLookAt(150,100,50, 0,0,0, 0,0,1);
	// obsX, obsY, obsZ = Define as coordenadas x,y,z da posi��o da c�mera
	// alvoX, alvoY, alvoZ = Define as coordenadas x,y,z do alvo (ou do ponto onde o observador est� olhando)
	// upX, upY, upZ = Define as coordenadas x,y,z do vetor UP (ou posi��o SUPERIOR da c�mera)
	// Mudar para: gluLookAt(225,225,225, 0,0,0, 0,1,0);
    // Deixando sem Rota��o e Transla��o... Alterando somente a escala dos objetos para valor = 3.0

    // glColor3f(1.0f, 0.0f, 0.0f);        // Determina a cor corrente para atribuir ao objeto.
	// glutWireCube(10);                   // Constroi um objeto aramado(wire): Cubo

    // glTranslatef(50.0f, 50.0f, 100.0f);   // Define uma nova Posi��o para o Objeto (em 150.0 nos eixos x,y,z).
    // Se modificarmos muito os eixos (como:0.0f,50.0f,50.0f), ele modifica essas coordenadas.
    // Por isso, dependendo dos valores corre-se o risco de n�o visualizar o objeto devido � sua localiza��o...
    // Mudar para: (0.0f, 10.0f, 50.0f); (0.0f, 80.0f, 60.0f);

	// glScalef(3.0f, 3.0f, 3.0f);       // Define uma nova Escala para o Objeto (em 2.0 nos eixos x,y,z).
	// Se modificarmos muito os eixos (como:2.0f,0.0f,0.0f), corre-se o risco de n�o visualizar o eixo/objeto devido � sua propor��o...
	// Mudar para: (4.0f, 3.0f, 3.0f); (1.0f, 2.0f, 3.0f);

    // glRotatef(45.0f, 1.0f, 0.0f, 0.0f); // Define uma nova Rota��o para o Objeto (em N graus no eixo x,y,z).
	// Se modificarmos muito o angulo em um eixo (ou em dois ou tr�s eixos) pode ser que n�o se consiga visualizar o objeto.
	// Por�m, pode-se especificar a rota��o nos eixos pretendidos (para rota��o) mencionando valor 1.0 nos eixos e o valor do �ngulo da rota��o no primeiro valor.

    glColor3f(0.0f, 1.0f, 1.0f);        // Determina a cor corrente para atribuir ao objeto.
	glutWireCone(2,10,10,15);           // Constroi um objeto aramado(wire): Cubo

	glFlush();                          // Executa os comandos OpenGL

}


void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) 		// Tecla ESC
		exit(0);
}



// Fun��o callback chamada para tratamento do Mouse
void GerenciaMouse(int button, int state, int x, int y)
{
     printf ("Tratamento de cliques do mouse");
           if(state==GLUT_DOWN)
              printf(">>> Botao %d pressionado \n", button);
           if(state==GLUT_UP)
              printf(">>> Botao %d liberado \n", button);
}



void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;
        glViewport(0, 0, w, h);
        fAspect = (GLfloat)w/(GLfloat)h;
        glMatrixMode(GL_PROJECTION);            // Define o tipo de proje��o e/ou com qual matriz vai se trabalhar: GL_PROJECTION:Matriz de proje��o
        glLoadIdentity();                       // Define o par�metro de visualiza��o. Inicializa o sistema de coordenadas antes da execu��o de qualquer opera��o da manipula��o de matrizes
        gluOrtho2D(0.0f, 450.0f, 450.0f, 0.0f); // Especifica que uma proje��o ortogonal ser� usada para mapear o conte�do de uma �rea Retangular 2D para a tela de v�deo.
}

void Inicializa (void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   // Especifica a cor de fundo da janela.
	glLineWidth(2.0);                       // Engrossa/Afina a linha do objeto.
}

int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Especifica o modelo de cor a ser usado no programa
	glutInitWindowPosition(5,5);                    // Especifica a posi��o do canto superior esquerdo da janela do programa na tela.
	glutInitWindowSize(450,450);                    // Especifica o tamanho, em pixels, da janela do programa.
	glutCreateWindow("Desenho de um cubo");         // Cria e nomeia uma janela para exibir a cena criada com o OpenGL.
	glutDisplayFunc(Desenha);                       //
	glutReshapeFunc(AlteraTamanhoJanela);           //
    glutKeyboardFunc (Teclado);
    glutMouseFunc(GerenciaMouse);
	Inicializa();                                   // Executa fun��o Inicializa
	glutMainLoop();                                 // Iniciar o processamento e aguarda poss�veis intera��es do usu�rio
	return 0;
}
