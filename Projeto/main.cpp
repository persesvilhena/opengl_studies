#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

int x, y, cont=0, var_barreira=0;
float cor=0, mud=0, ang=400;

typedef struct{
    int x;
    int y;
}coco;
std::vector<coco>cocos;

void cria_coco(){
    int aleatorio = rand()%400;
    coco c;
    c.x = aleatorio;
    c.y = 400;
    cocos.push_back(c);
}





void xadrez(void){
    cor = 0;
    int tam = 50;
    for(x=0; x<8; x++){
            for(y=0; y<8; y++){
                    if(mud == 0){
                        mud = 1;
                    }else{
                        mud = 0;
                    }
                    glColor3f(mud, (cor/64), 1.0f);
                    glBegin(GL_QUADS);
                    glVertex2i(tam*x,tam*y);
                    glVertex2i(tam*x,tam*(y+1));
                    glVertex2i(tam*(x+1),tam*(y+1));
                    glVertex2i(tam*(x+1),tam*y);
                    glEnd();
                    cor++;

            }
            if(mud == 0){
                mud = 1;
            }else{
                mud = 0;
            }
        }
}


void desenha_coco(int x, int y){
    int tam = 30;
    glEnable(GL_BLEND);
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
        glVertex2i(x,y);
        glVertex2i(x,y+tam);
        glVertex2i(x+tam,y+tam);
        glVertex2i(x+tam,y);
    glEnd();

   /*glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2i(x,y+tam);
        glVertex2i(x+(tam/2),y+(1.5*tam));
        glVertex2i(x+tam,y+tam);
    glEnd();*/
}

void barreira(int x){
    y = 50;
    int lar = 50;
    int alt = 10;
    glEnable(GL_BLEND);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2i(x,y);
        glVertex2i(x,y+alt);
        glVertex2i(x+lar,y+alt);
        glVertex2i(x+lar,y);
    glEnd();
}

void move_barreira(int val){
    if(((var_barreira + val) < 392) && ((var_barreira + val) > -4)){
        var_barreira = var_barreira + val;
    }

}



void Desenha(void){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    ang-= 0.3f;
    xadrez();
    cont++; //contador do fps

    for(int i =0 ; i < cocos.size(); i++){
        int coco_x = cocos.at(i).x;
        int coco_y = cocos.at(i).y;
        coco_y-=2;
        cocos.at(i).y = coco_y;
        desenha_coco(coco_x, coco_y);

        if(coco_y < 50){
            if((((coco_x) > var_barreira) && ((coco_x) < (var_barreira + 50))) || (((coco_x + 30) > var_barreira) && ((coco_x + 30) < (var_barreira + 50)))){
                exit(0);
            }
        }


        if(coco_y < 0){
            cocos.erase(cocos.begin() + i);
        }
    }

    if(cont>1500){
        ang=0.0f;
        cont=0;
    }
        //coco(100,ang,10);
        barreira(var_barreira);

    glFlush();
}


void tick(int t){
    if(t == 0){
        Desenha();
        glutPostRedisplay();
        glutTimerFunc(33.33, tick, 0);
    }else{
        if(t == 1){
            //system("cls");
            printf("FPS: %d\n", cont);
            cont = 0;
            glutTimerFunc(1000, tick, 1);
        }else{
            cria_coco();
            glutTimerFunc(300, tick, 2);
        }
    }
}



void Inicializa (void){
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
}


void AlteraTamanhoJanela(GLsizei w, GLsizei h){
                   if(h == 0) h = 1;
                   glViewport(0, 0, w, h);
                   glMatrixMode(GL_PROJECTION);
                   glLoadIdentity();
                   if (w <= h)
                           gluOrtho2D (0.0f, 400.0f, 0.0f, 400.0f*h/w);
                   else
                           gluOrtho2D (0.0f, 400.0f*w/h, 0.0f, 400.0f);
}


void Teclado (unsigned char tecla, int x, int y){
	if(tecla==100){
        move_barreira(15);
	}
	if(tecla==97){
        move_barreira(-15);
	}
}

int main(void){
     srand(time(NULL));
     //printf("%d", rand()%400);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(400,400);
     glutInitWindowPosition(100,100);
     glutCreateWindow("Coco da galera");

     glutDisplayFunc(Desenha);
     glutKeyboardFunc(Teclado);
     glutReshapeFunc(AlteraTamanhoJanela);

     Inicializa();
     glutTimerFunc(33.33, tick, 0);
     glutTimerFunc(1000, tick, 1);
     glutTimerFunc(1000, tick, 2);
     glutMainLoop();

}

