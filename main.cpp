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
#define num_paredes 20
#define QTD_MOVIMENTO 5

#define TAMANHO_CELULA 10

#define DEBUG
///formula = j* 50 + i ---- j: coluna horizontal, i: coluna vertical
///formula inversa  =  id/ 50 = j (coluna horizontal), id%50 = i coluna vertical

Scene *scene;
Agente *agente;
Wall *objetos;
NavMesh *navMesh;
DStar *dstar;
int i=0;


void reshape(int, int);
void display(void);
void idle ();
void init();
void mouse(int button, int state, int x, int y);

///funcoes auxiliares
bool taOcupado(int id);
void auxilia(int i);

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

    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, TAM_CENARIO+2, -2, TAM_CENARIO+2, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    scene->drawScene(navMesh, dstar, objetos, agente,num_paredes);
    scene->drawObstacles(navMesh,objetos,num_paredes);


    glFlush ();
}


void idle()
{
    usleep(20000);

    for(int m=0; m <num_paredes; m++){
        objetos[m].atualizaPosicao(TAM_CENARIO, num_paredes);
        navMesh->removeGridObstaculos(objetos,m,num_paredes);
    }
    for(int m=0; m <num_paredes; m++){
        navMesh->criaGridObstaculos(objetos,m,num_paredes);
    }
    for(int i =0; i <dstar->closed.size(); i++){
        if (taOcupado(dstar->closed[i].id) == true) {
                dstar->DStarLite(agente, navMesh);
            }
    }
    glutPostRedisplay();

}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    scene = new Scene();
    agente = new Agente();
    objetos = new Wall[num_paredes];
    navMesh = new NavMesh(TAM_CENARIO);
   // navMesh->criaObjetos(num_paredes, TAM_CENARIO);
    for(int m=0; m <num_paredes; m++){
     //   std::cout  << "START | m: " << m << std::endl;
        objetos[m].geraPosicaoInicial(TAM_CENARIO, num_paredes);
        navMesh->criaGridObstaculos(objetos,m,num_paredes);


    }
    dstar = new DStar(navMesh, 50, agente, objetos);
    dstar->DStarLite(agente, navMesh);
    agente->atual = agente->start;
}


void clickCell(int x, int y) {


    dstar->updateCell(x, y, INT_MAX);


}
void mouse(int button, int state, int x, int y) {

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        clickCell(x, y);
    }


}
void auxilia(int i) {
    if (agente->atual.x != agente->end.x && agente->atual.y != agente->end.y) {
        if(dstar->closed[i+1].id != dstar->s_end.id) {
            if (taOcupado(dstar->closed[i + 1].id) == true) {
                dstar->DStarLite(agente, navMesh);
            }
        }
    }
}
bool taOcupado(int id){
    int j = id/50;
    int i = id%50;
    if(navMesh->_meshes[i][j]==1){
        return true;
    }return false;
}