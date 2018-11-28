#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include "Scene.h"
#include "NavMesh.h"
#include "DStar.h"
#include <unistd.h>


#define TAM_CENARIO 500
#define num_paredes 5
#define TAMANHO_CELULA 10

//#define DEBUG


Scene *scene;
Agente *agente;
Wall *obstaculos;
NavMesh *navMesh;
DStar *dstar;

void reshape(int, int);
void display(void);
void idle ();
void init();
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {
   // std:: cout << "   "<<__cplusplus ;
   // start = clock();

    srand (time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Navigation Mesh");

    //acoes de callback
    glutDisplayFunc(display); //quando um pixel na janela precisa ser atualizado
    glutIdleFunc(idle); //funcao de callback chamada quando nada esta acontecendo
    glutReshapeFunc(reshape); //chamado quando a janela 'e redimensionada
  //  glutMotionFunc(mouseMotionFunc);
    glutMouseFunc(mouse);

    init();




    glutMainLoop();

    return 0;
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, (float)w, (float)h, 0.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display (void)
{
    usleep(2000);
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, TAM_CENARIO+2, -2, TAM_CENARIO+2, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    scene->drawScene(navMesh, dstar, agente,num_paredes);




#ifdef DEBUG
        std::cout<<agente->atual.x << ","<<  agente->atual.y << std::endl;
    #endif



    glFlush ();
}


void idle()
{
   // dstar->DStarLite(agente);

    navMesh->atualizaPosicao();
    scene->drawPathAtual(agente);
   // scene->drawPathDStar(dstar);


    glutPostRedisplay();


}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    agente = new Agente();
    scene = new Scene();
    navMesh = new NavMesh(TAM_CENARIO);
    navMesh->criaObjetos(num_paredes, TAM_CENARIO);
    dstar = new DStar(navMesh, 50, agente);
    dstar->DStarLite();
  //  scene->drawScene(navMesh, dstar, agente,num_paredes);
}
void clickCell(int x, int y) {


    dstar->updateCell(x, y, INT_MAX);


}
void mouse(int button, int state, int x, int y) {

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        clickCell(x, y);
    }


}
//void auxilia(){
//
//    while(agente->atual.x != agente->end.x){
//        scene->drawPathAtual(agente);
//        for(int i=0; i < dstar->closed.size(); i++){
//            //agente.atual = closed[i].pontos;
//            if(veSetaocupado(dstar->closed[i+1].id)){
//                dstar->DStarLite();
//            }
//        }
//
//    }
//
//}