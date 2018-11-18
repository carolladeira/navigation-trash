//
// Created by carol on 11/17/18.
//
  /* time */

#include "NavMesh.h"

//------------------------- Obstaculos------------------------------------
void Wall::geraPosicaoInicial(float tam_cenario, int num_paredes) {

    this->atual.x = rand() % (int)tam_cenario;
    this->atual.y = rand() % (int)tam_cenario;
    this->width= rand() % MAX_LARGURA_PAREDE + MIN_LARGURA_PAREDE;
    this->height= rand() % MAX_LARGURA_PAREDE + MIN_LARGURA_PAREDE;
    this->ang = rand() % 360;
}
