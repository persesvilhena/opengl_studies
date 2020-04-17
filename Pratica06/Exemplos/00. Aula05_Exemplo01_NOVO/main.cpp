// Inclusão das bibliotecas com as funções utilizadas;
// Nos programas desenvolvidos para SO Windows é necessário incluir...
// ...a biblioteca <windows.h> antes das bibliotecas do OpenGL

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat fAspect;

void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   // Limpa a janela de visualização com a cor de fundo especificada

/*
    glColor3f(0.0f, 0.0f, 1.0f);    // Determina a cor que serão construídos os objetos
    glBegin(GL_TRIANGLES);          // Determina o início da construção dos objetos (Triângulos)
               glVertex2i(100,100);     // Especifica as coordenadas X,Y do primeiro ponto,
               glVertex2i(200,300);     // Especifica as coordenadas X,Y do segundo ponto,
               glVertex2i(300,100);     // Especifica as coordenadas X,Y do terceiro ponto,
    glEnd();
*/

    glMatrixMode(GL_PROJECTION);        // Define o tipo de projeção e/ou com qual matriz vai se trabalhar: GL_PROJECTION:Matriz de projeção
	glLoadIdentity();                   // Define o parâmetro de visualização. Inicializa o sistema de coordenadas antes da execução de qualquer operação da manipulação de matrizes

	gluPerspective(20,fAspect,0.5,500);
	// fovY = Especifica o ângulo de visualização em graus, na direção y.
	// fAspect = É a razão de aspecto que determina a area de visualização na direção x.
	// zNear = Define a distância do observador até o plano frontal
	// zFar = Define a distância do observador até o plano traseiro

	gluLookAt(150,100,50, 0,0,0, 0,0,1);
	// obsX, obsY, obsZ = Define as coordenadas x,y,z da posição da câmera
	// alvoX, alvoY, alvoZ = Define as coordenadas x,y,z do alvo (ou do ponto onde o observador está olhando)
	// upX, upY, upZ = Define as coordenadas x,y,z do vetor UP (ou posição SUPERIOR da câmera)
	// Mudar para: gluLookAt(225,225,225, 0,0,0, 0,1,0);
    // Deixando sem Rotação e Translação... Alterando somente a escala dos objetos para valor = 3.0

    // glColor3f(1.0f, 0.0f, 0.0f);        // Determina a cor corrente para atribuir ao objeto.
	// glutWireCube(10);                   // Constroi um objeto aramado(wire): Cubo

    // glTranslatef(50.0f, 50.0f, 100.0f);   // Define uma nova Posição para o Objeto (em 150.0 nos eixos x,y,z).
    // Se modificarmos muito os eixos (como:0.0f,50.0f,50.0f), ele modifica essas coordenadas.
    // Por isso, dependendo dos valores corre-se o risco de não visualizar o objeto devido à sua localização...
    // Mudar para: (0.0f, 10.0f, 50.0f); (0.0f, 80.0f, 60.0f);

	// glScalef(3.0f, 3.0f, 3.0f);       // Define uma nova Escala para o Objeto (em 2.0 nos eixos x,y,z).
	// Se modificarmos muito os eixos (como:2.0f,0.0f,0.0f), corre-se o risco de não visualizar o eixo/objeto devido à sua proporção...
	// Mudar para: (4.0f, 3.0f, 3.0f); (1.0f, 2.0f, 3.0f);

    // glRotatef(45.0f, 1.0f, 0.0f, 0.0f); // Define uma nova Rotação para o Objeto (em N graus no eixo x,y,z).
	// Se modificarmos muito o angulo em um eixo (ou em dois ou três eixos) pode ser que não se consiga visualizar o objeto.
	// Porém, pode-se especificar a rotação nos eixos pretendidos (para rotação) mencionando valor 1.0 nos eixos e o valor do ângulo da rotação no primeiro valor.

    glColor3f(0.0f, 1.0f, 1.0f);        // Determina a cor corrente para atribuir ao objeto.
	glutWireCone(2,10,10,15);           // Constroi um objeto aramado(wire): Cubo

	glFlush();                          // Executa os comandos OpenGL

}


void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) 		// Tecla ESC
		exit(0);
}



// Função callback chamada para tratamento do Mouse
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
        glMatrixMode(GL_PROJECTION);            // Define o tipo de projeção e/ou com qual matriz vai se trabalhar: GL_PROJECTION:Matriz de projeção
        glLoadIdentity();                       // Define o parâmetro de visualização. Inicializa o sistema de coordenadas antes da execução de qualquer operação da manipulação de matrizes
        gluOrtho2D(0.0f, 450.0f, 450.0f, 0.0f); // Especifica que uma projeção ortogonal será usada para mapear o conteúdo de uma área Retangular 2D para a tela de vídeo.
}

void Inicializa (void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);   // Especifica a cor de fundo da janela.
	glLineWidth(2.0);                       // Engrossa/Afina a linha do objeto.
}

int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Especifica o modelo de cor a ser usado no programa
	glutInitWindowPosition(5,5);                    // Especifica a posição do canto superior esquerdo da janela do programa na tela.
	glutInitWindowSize(450,450);                    // Especifica o tamanho, em pixels, da janela do programa.
	glutCreateWindow("Desenho de um cubo");         // Cria e nomeia uma janela para exibir a cena criada com o OpenGL.
	glutDisplayFunc(Desenha);                       //
	glutReshapeFunc(AlteraTamanhoJanela);           //
    glutKeyboardFunc (Teclado);
    glutMouseFunc(GerenciaMouse);
	Inicializa();                                   // Executa função Inicializa
	glutMainLoop();                                 // Iniciar o processamento e aguarda possíveis interações do usuário
	return 0;
}
