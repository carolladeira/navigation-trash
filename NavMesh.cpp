//
// Created by carol on 11/17/18.
//
  /* time */

#include "NavMesh.h"

#include <iostream>

using namespace std;
#define DEBUG


//-------------------------Agente------------------------------------
Agente::Agente() {
    this->start.x =rand() % (int)500;
    this->start.y =rand() % (int)500;

    this->end.x = rand() % (int)500;
    this->end.y = rand() % (int)500;

//    this->start.x =15;
//    this->start.y =15;
//
//    this->end.x = 5;
//    this->end.y = 35;


}


//-------------------------Obstaculos------------------------------------
//void Wall::geraPosicaoInicial(float tam_cenario, int num_paredes) {
//
//    this->atual.x = rand() % (int)tam_cenario;
//    this->atual.y = rand() % (int)tam_cenario;
//    this->width= rand() % MAX_LARGURA_PAREDE + MIN_LARGURA_PAREDE;
//    this->height= rand() % MAX_LARGURA_PAREDE + MIN_LARGURA_PAREDE;
//
//    this->pontos[0].x = this->atual.x;		            this->pontos[0].y = this->atual.y;
//    this->pontos[1].x = this->atual.x + this->width;    this->pontos[1].y = this->atual.y;
//    this->pontos[2].x = this->atual.x + this->width;	this->pontos[2].y = this->atual.y + this->height;
//    this->pontos[3].x = this->atual.x;		            this->pontos[3].y = this->atual.y + this->height;
//}


Mesh::Mesh(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int t, int parede_pai){
    this->tipo = t;
    this->pontos[0].x = (int)(10*x1) / 10.0;		this->pontos[0].y = (int)(10*y1) / 10.0;
    this->pontos[1].x = (int)(10*x2) / 10.0;		this->pontos[1].y = (int)(10*y2) / 10.0;
    this->pontos[2].x = (int)(10*x3) / 10.0;		this->pontos[2].y = (int)(10*y3) / 10.0;
    this->pontos[3].x = (int)(10*x4) / 10.0;		this->pontos[3].y = (int)(10*y4) / 10.0;
    this->parede_pertence = parede_pai;

}
//-----------------------------------NavMesh----------------------------------------------------------------------
void NavMesh::Cria_Mesh_Cobertura( ){
   // nObstacles = 10;
    int j=0, i=0;
   // Mesh m;
    float dx1, dx2, dy1, dy2;
   // while(this->obstacles[i]. != NULL){
    for(int i=0; i < nObstacles; i++){

        float x1 = obstacles[i].pontos[0].x;
        float y1 = obstacles[i].pontos[0].y;
        float x2 = obstacles[i].pontos[1].x;
        float y2 = obstacles[i].pontos[1].y;
        float x3 = obstacles[i].pontos[2].x;
        float y3 = obstacles[i].pontos[2].y;
        float x4 = obstacles[i].pontos[3].x;
        float y4 = obstacles[i].pontos[3].y;

        dx1 = LARGURA_MESH_COVER;
        dx2 = 0;
        dy1 = 0;
        dy2 = LARGURA_MESH_COVER;

        ///superior esquerda
        Mesh *m = new Mesh(	x4 - dx1 - dx2, 	y4 - dy1 + dy2,
                            x4 - dx2, 			y4 + dy2,
                            x4 - dx1, 			y4 - dy1,
                            x4, 				y4, 2, i);
        meshes.push_back(m);
        //superior
        m = new Mesh(   x4 - dx2, 	y4 + dy2,
                        x3 - dx2,   y3 + dy2,
                        x4, 		y4,
                        x3, 		y3, 1, i);
        meshes.push_back(m);

        //superior direita
        m= new Mesh(	x3 - dx2, 			y3 + dy2,
                        x3 - dx2 + dx1, 	y3 + dy1 + dy2,
                        x3, 				y3,
                        x3 + dx1, 			y3 + dy1, 2, i);
        meshes.push_back(m);

        //direita
        m = new Mesh(	x3, 				y3,
                        x3 + dx1, 			y3 + dy1,
                        x2, 				y2,
                        x2 + dx1, 			y2 + dy1, 1, i);
        meshes.push_back(m);
        //inferior direita
        m = new Mesh(	x2, 				y2,
                        x2 + dx1, 			y2 + dy1,
                        x2 + dx2,			y2 - dy2,
                        x2 + dx1 + dx2, 	y2 - dy2 + dy1, 2, i);
        meshes.push_back(m);
        //inferior
        m = new Mesh(	x1,					y1,
                        x2, 				y2,
                        x1 + dx2, 			y1 - dy2,
                        x2 + dx2,			y2 - dy2, 1, i);
        meshes.push_back(m);
        //inferior esquerda
        m = new Mesh(	x1 - dx1,			y1 - dy1,
                        x1,					y1,
                        x1 - dx1 + dx2, 	y1 - dy1 - dy2,
                        x1 + dx2,			y1 - dy2, 2, i);
        meshes.push_back(m);
        //esquerda
        m = new Mesh(	x1 - dx1, 			y1 - dy1,
                        x1,					y1,
                        x4 - dx1,			y4 - dy1,
                        x4,					y4, 1, i);
        meshes.push_back(m);
    }


}

void NavMesh::atualizaObstacles(Wall *obstacles, int size) {
    this->obstacles = obstacles;
    nObstacles = size;

}

void NavMesh::criaNavMesh(Wall *obstacles) {
    Cria_Mesh_Cobertura();
}

NavMesh::NavMesh(int tam_cenario) {
    //std::vector<Mesh*> meshes;
 //   obstacles = NULL;
   // nObstacles = 0;
   tamanho = tam_cenario/QUANTIDADE_CELULA;
  // cout << tamanho;
   for (int i=0; i<tamanho; i++){
       for(int j=0;j<tamanho; j++)
       {
           //std::cout <<  i << "-"<<  j << std::endl;

           _meshes[i][j]=0;
       }
   }

}

void NavMesh::criaGrid(Wall *obstacles, float tam_cenario) {
//    int x=0, y=0;
//    int tamanho = tam_cenario/QUANTIDADE_CELULA;
//    for (int i=0; i< QUANTIDADE_CELULA; i++){
//
//        for (int j=0; j< QUANTIDADE_CELULA; j++){
//
//            Mesh *m = new Mesh(x, y, x+ tamanho, y, x + tamanho, y+tamanho, x, y+tamanho,4, 0);
//            meshes.push_back(m);
//            x+= tamanho;
//
//            _meshes[i][j] =
//        }
//        x=0;
//        y+=tamanho;
//
//    }

}

void NavMesh::criaObjetos(int num_paredes, int tam_cenario) {
    objects= new Wall[num_paredes];

    this->objects[0].pontos[0].x = 22;		            this->objects[0].pontos[0].y = 22;
    this->objects[0].pontos[1].x = 32;           this->objects[0].pontos[1].y = 22;
    this->objects[0].pontos[2].x = 32;	        this->objects[0].pontos[2].y = 32;
    this->objects[0].pontos[3].x = 22;		            this->objects[0].pontos[3].y = 32;

    int ax = (int)objects[0].pontos[0].x / tamanho;     int ay =(int) objects[0].pontos[0].y / tamanho;
    int bx = (int)objects[0].pontos[1].x / tamanho;     int by = (int)objects[0].pontos[1].y / tamanho;
    int cx = (int)objects[0].pontos[2].x / tamanho;     int cy = (int)objects[0].pontos[2].y / tamanho;
    int dx = (int)objects[0].pontos[3].x / tamanho;     int dy = (int)objects[0].pontos[3].y / tamanho;

  //  std::cout  << " " << ax << " " << ay << std::endl;

    for (int _x = ax;_x<=cx; _x++){
        for(int _y=ay;_y<=cy;_y++){
         //   std::cout  << " " << _x << " " << _y << std::endl;

            _meshes[_x][_y] = 1;
            cells[_x][_y].cost = INT_MAX;
        }
    }
    for(int i=1; i < num_paredes;  i++){
        float x = rand() % (int)tam_cenario -1 + 1;
        float y = rand() % (int)tam_cenario -1 + 1;
        float width= rand() % MAX_LARGURA_PAREDE + MIN_LARGURA_PAREDE;
        float height= rand() % MAX_LARGURA_PAREDE + MIN_LARGURA_PAREDE;

        this->objects[i].pontos[0].x = x;		            this->objects[i].pontos[0].y = y;
        this->objects[i].pontos[1].x = x + width;           this->objects[i].pontos[1].y = y;
        this->objects[i].pontos[2].x = x + width;	        this->objects[i].pontos[2].y = y + height;
        this->objects[i].pontos[3].x = x;		            this->objects[i].pontos[3].y = y + height;
//
//#ifdef DEBUG
//        std::cout <<this->objects[i].pontos[0].x << ","<<this->objects[i].pontos[0].y<< " --- ";
//        std::cout <<this->objects[i].pontos[1].x << ","<<this->objects[i].pontos[1].y<< " --- ";
//        std::cout <<this->objects[i].pontos[2].x << ","<<this->objects[i].pontos[2].y<< " --- ";
//        std::cout <<this->objects[i].pontos[3].x << ","<<this->objects[i].pontos[3].y<<std::endl;
//#endif

        int ax = (int)objects[i].pontos[0].x / tamanho;     int ay =(int) objects[i].pontos[0].y / tamanho;
        int bx = (int)objects[i].pontos[1].x / tamanho;     int by = (int)objects[i].pontos[1].y / tamanho;
        int cx = (int)objects[i].pontos[2].x / tamanho;     int cy = (int)objects[i].pontos[2].y / tamanho;
        int dx = (int)objects[i].pontos[3].x / tamanho;     int dy = (int)objects[i].pontos[3].y / tamanho;

      //  std::cout  << " " << this->objects[i].pontos[0].x  << " " << y << std::endl;

    //    std::cout  << " " << ax << " " << ay << std::endl;

        for (int _x = ax;_x<=cx; _x++){
            for(int _y=ay;_y<=cy;_y++){
             //   std::cout  << " " << _x << " " << _y << std::endl;

                _meshes[_x][_y] = 1;
                cells[_x][_y].cost = INT_MAX;
            }
        }


    }

}

void NavMesh::atualizaPosicao() {
    this->objects[0].pontos[0].x = this->objects[0].pontos[0].x + 0.101;		            this->objects[0].pontos[0].y = this->objects[0].pontos[0].y + 0.101;
    this->objects[0].pontos[1].x = this->objects[0].pontos[1].x + 0.101;                    this->objects[0].pontos[1].y = this->objects[0].pontos[1].y+ 0.101;
    this->objects[0].pontos[2].x = this->objects[0].pontos[2].x+ 0.101;	                this->objects[0].pontos[2].y = this->objects[0].pontos[2].y+ 0.101;
    this->objects[0].pontos[3].x = this->objects[0].pontos[3].x+ 0.101;		            this->objects[0].pontos[3].y = this->objects[0].pontos[3].y+ 0.101;

    int ax = (int)objects[0].pontos[0].x / tamanho;     int ay =(int) objects[0].pontos[0].y / tamanho;
    int bx = (int)objects[0].pontos[1].x / tamanho;     int by = (int)objects[0].pontos[1].y / tamanho;
    int cx = (int)objects[0].pontos[2].x / tamanho;     int cy = (int)objects[0].pontos[2].y / tamanho;
    int dx = (int)objects[0].pontos[3].x / tamanho;     int dy = (int)objects[0].pontos[3].y / tamanho;


#ifdef DEBUG
    std::cout  << " " << objects[0].pontos[0].x << " " << ay << std::endl;

#endif

    for (int _x = ax;_x<=cx; _x++){
        for(int _y=ay;_y<=cy;_y++){
            //   std::cout  << " " << _x << " " << _y << std::endl;

            _meshes[_x][_y] = 1;
        }
    }
}
