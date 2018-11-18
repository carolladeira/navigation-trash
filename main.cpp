#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include "Scene.h"
#include "NavMesh.h"


#define TAM_CENARIO 500
#define num_paredes 10

Scene *scene;
Agente *agente;
Wall *obstaculos;

void reshape(int, int);
void display(void);
void idle ();
void init();

int main(int argc, char** argv) {
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

    scene->drawScene(agente,num_paredes, obstaculos);

    glFlush ();
}

void idle()
{

}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    agente = new Agente();
    scene = new Scene();
    obstaculos = new Wall[num_paredes];
    for(int i=0; i< num_paredes; i++)
    {
        obstaculos[i].geraPosicaoInicial(TAM_CENARIO, num_paredes);
    }


}
