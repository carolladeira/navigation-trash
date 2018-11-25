//
// Created by nao on 21/11/18.
//

#include "DStar.h"
#include <iostream>
#include <algorithm>    // std::find


Node::Node() {
    this->g = INT_MAX;
    this->h = 0;
    this->f = INT_MAX;
}

Node::~Node() {

}

DStar::DStar(NavMesh *nav, int tamanho, Agente *agente) {
    int m = 0;
    this->pessoa = *agente;
    std::vector<Node> temp;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {


            Node nox;
            nox.pontos.x = (i * 10) + 5;
            nox.pontos.y = (j * 10) + 5;
            nox.id = m;
            if(nav->_meshes[i][j] == 1){
                obstacles.push_back(nox);
                //continue;
            }
            if (((agente->start.x - 5) <= nox.pontos.x == true) && (((agente->start.x + 5) >= nox.pontos.x == true))){
                if (((agente->start.y - 5) <= nox.pontos.y == true) && (((agente->start.y + 5) >= nox.pontos.y == true))){
                    pessoa.start.id = m;
                   // std::cout  << " " << m << std::endl;
                   // std::cout  << " " << agente->start.x << " " << agente->start.y << std::endl;
                   // std::cout  << " " << nox.pontos.x << " " << nox.pontos.y<< std::endl;
                }
            }
          //  if ((nox.pontos.x <= agente->start.x + 10|| agente->start.x >= nox.pontos.x) && (nox.pontos.y <= agente->start.y || agente->start.y >= nox.pontos.y)) {

            if (((agente->end.x - 5) <= nox.pontos.x == true) && (((agente->end.x + 5) >= nox.pontos.x == true))){
                if (((agente->end.y - 5) <= nox.pontos.y == true) && (((agente->end.y + 5) >= nox.pontos.y == true))){
                    pessoa.end.id = m;
                }
            }

            temp = nosVizinhos(nox, 0, 50);
            listaAdj.push_back(temp);
            temp.clear();
            m++;
        }
    }
    //imprime();
}
void DStar::imprime(){
    for (int i=0; i<listaAdj.size(); i++){
        std::cout << ' ' << i;
        for(int j=0; j<listaAdj[i].size(); j++){
            std::cout << ' ' << listaAdj[i][j].id;
            std::cout << "(" << listaAdj[i][j].pontos.x << ',' << listaAdj[i][j].pontos.y << ')' ;
        }
        std::cout  << " " << std::endl;
    }
}

std::vector<Node> DStar::nosVizinhos(Node n, int tipo, int tamanho) {


    std::vector<Node> vizinhos;
///===========================================================================================
    if (n.pontos.x == 5)//Nos da esquerda
    {
        if (n.pontos.y == 5)//de baixo
        {
            Node novo;
            novo.pontos.x = n.pontos.x + 10; //direita
            novo.pontos.y = n.pontos.y;
            novo.id = n.id + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x; //cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 + tamanho;
            vizinhos.push_back(novo);
            return vizinhos;

        } else if (n.pontos.y == 495)// de cima
        {
            Node novo;
            novo.pontos.x = n.pontos.x + 10; //direita
            novo.pontos.y = n.pontos.y;
            novo.id = n.id + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x; //baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 + tamanho;
            vizinhos.push_back(novo);
            return vizinhos;
        } else {
            Node novo;
            novo.pontos.x = n.pontos.x + 10; //direita
            novo.pontos.y = n.pontos.y;
            novo.id = n.id + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x; //de cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x; //de baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 + tamanho;
            vizinhos.push_back(novo);
            return vizinhos;

        }
///====================================================================================
    } else if (n.pontos.y == 5) //Nos de baixo
    {
        if (n.pontos.x == 5)//esquerda
        {
            Node novo;
            novo.pontos.x = n.pontos.x; //de cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //direita
            novo.pontos.y = n.pontos.y;
            novo.id = n.id + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 + tamanho;
            vizinhos.push_back(novo);
            return vizinhos;

        } else if (n.pontos.x == 495)// direita
        {
            Node novo;
            novo.pontos.x = n.pontos.x; //de cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //esquerda
            novo.pontos.y = n.pontos.y;
            novo.id = n.id - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 - tamanho;
            vizinhos.push_back(novo);
            return vizinhos;
        } else {
            Node novo;
            novo.pontos.x = n.pontos.x + 10; //direita
            novo.pontos.y = n.pontos.y;
            novo.id = n.id + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x; //de cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //esquerda
            novo.pontos.y = n.pontos.y;
            novo.id = n.id - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 - tamanho;
            vizinhos.push_back(novo);
            return vizinhos;
        }
///===========================================================================================================================
    } else if (n.pontos.y == 495) //Nos de cima
    {
        if (n.pontos.x == 5)//esquerda
        {
            Node novo;
            novo.pontos.x = n.pontos.x + 10; //direita
            novo.pontos.y = n.pontos.y;
            novo.id = n.id + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x;  //baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 + tamanho;
            vizinhos.push_back(novo);
            return vizinhos;

        } else if (n.pontos.x == 495)// direita
        {
            Node novo;
            novo.pontos.x = n.pontos.x - 10; //esquerda
            novo.pontos.y = n.pontos.y;
            novo.id = n.id - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x;  //baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 - tamanho;
            vizinhos.push_back(novo);
            return vizinhos;
        }else{
            Node novo;
            novo.pontos.x = n.pontos.x + 10; //direita
            novo.pontos.y = n.pontos.y;
            novo.id = n.id + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //esquerda
            novo.pontos.y = n.pontos.y;
            novo.id = n.id - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x;  //baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x + 10; //diagonal direita-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 + tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 - tamanho;
            vizinhos.push_back(novo);
            return vizinhos;

        }

//=============================================================================================
    } else if (n.pontos.x == 495) //Nos da direita
    {
        if (n.pontos.y == 5)//de baixo
        {
            Node novo;
            novo.pontos.x = n.pontos.x - 10; //esquerda
            novo.pontos.y = n.pontos.y;
            novo.id = n.id - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x; //cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 - tamanho;
            vizinhos.push_back(novo);
            return vizinhos;

        } else if (n.pontos.y == 495)// de cima
        {
            Node novo;
            novo.pontos.x = n.pontos.x - 10; //esquerda
            novo.pontos.y = n.pontos.y;
            novo.id = n.id - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x;  //baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 - tamanho;
            vizinhos.push_back(novo);
            return vizinhos;
        } else {
            Node novo;
            novo.pontos.x = n.pontos.x - 10; //esquerda
            novo.pontos.y = n.pontos.y;
            novo.id = n.id - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x; //cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x;  //baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-baixo
            novo.pontos.y = n.pontos.y - 10;
            novo.id = n.id - 1 - tamanho;
            vizinhos.push_back(novo);

            novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-cima
            novo.pontos.y = n.pontos.y + 10;
            novo.id = n.id + 1 - tamanho;
            vizinhos.push_back(novo);
            return vizinhos;
        }
///===================================================================================
    }else{
        Node novo;
        novo.pontos.x = n.pontos.x - 10; //esquerda
        novo.pontos.y = n.pontos.y;
        novo.id = n.id - tamanho;
        vizinhos.push_back(novo);

        novo.pontos.x = n.pontos.x + 10; //direita
        novo.pontos.y = n.pontos.y;
        novo.id = n.id + tamanho;
        vizinhos.push_back(novo);

        novo.pontos.x = n.pontos.x; //cima
        novo.pontos.y = n.pontos.y + 10;
        novo.id = n.id + 1;
        vizinhos.push_back(novo);

        novo.pontos.x = n.pontos.x;  //baixo
        novo.pontos.y = n.pontos.y - 10;
        novo.id = n.id - 1;
        vizinhos.push_back(novo);

        novo.pontos.x = n.pontos.x + 10; //diagonal direita-cima
        novo.pontos.y = n.pontos.y + 10;
        novo.id = n.id + 1 + tamanho;
        vizinhos.push_back(novo);

        novo.pontos.x = n.pontos.x + 10; //diagonal direita-baixo
        novo.pontos.y = n.pontos.y - 10;
        novo.id = n.id - 1 + tamanho;
        vizinhos.push_back(novo);
//
        novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-baixo
        novo.pontos.y = n.pontos.y - 10;
        novo.id = n.id - 1 - tamanho;
        vizinhos.push_back(novo);

        novo.pontos.x = n.pontos.x - 10; //diagonal esquerda-cima
        novo.pontos.y = n.pontos.y + 10;
        novo.id = n.id + 1 - tamanho;
        vizinhos.push_back(novo);
        return vizinhos;


    }

}

//entrada: start, goal
std::vector<Node> DStar::AStar() {
    Node node;
    node.g = 0;
    node.pontos = pessoa.start;
    node.id = pessoa.start.id;
    node.f = calculaDistancia(pessoa.start, pessoa.end);
    open.push_back(node);

    std::vector<Node> vizinhos;
    std::vector<Node> temp;


    float g =0;
    Node current;
    while (!open.empty()) {

        current = menorFScore(this->open);
        if (current.id == pessoa.end.id) {
            ///encontrou caminho
            return reconstructPath(mapPath, current);
        }


        this->open.erase(this->open.begin()); //remove de open
        closed.push_back(current); //adiciona em closed

        vizinhos = expand(current); //descobrir o sucessor e gerar os pais dele de bestNode

        for (int i = 0; i < vizinhos.size(); i++) ///para cada vizinho do atual
        {

            /// Ignore the neighbor which is already evaluated.
            if (std::find(closed.begin(), closed.end(), vizinhos[i]) != closed.end()) {
                continue;
            }

            // The distance from start to a neighbor
            g = current.g + calculaDistancia(current.pontos, vizinhos[i].pontos);


            // if neighbor not in openSet,  Discover a new node
            if (std::find(open.begin(), open.end(), vizinhos[i]) != open.end()) {
                if (g >= vizinhos[i].g) {
                    continue;
                }
            } else {
                vizinhos[i].g = g;
                vizinhos[i].h = calculaDistancia(vizinhos[i].pontos, pessoa.end);
                vizinhos[i].f = vizinhos[i].g + vizinhos[i].h;
                open.push_back(vizinhos[i]);
            }

            //temp.push_back(current);
///            cameFrom[vizinhos[i].id].push_back(current);
            mapPath[vizinhos[i].id].push_back(current);
            //mapPath[vizinhos[i].id] = current;
            vizinhos[i].g = g;
            vizinhos[i].h = calculaDistancia(vizinhos[i].pontos, pessoa.end);
            vizinhos[i].f = vizinhos[i].g + vizinhos[i].h;
        }
    }
}

std::vector<Node> DStar::reconstructPath(std::vector<Node> mathPath[], Node current) {
    //std::vector<Node> totalPath;
//    totalPath.push_back(current);
//    for (int i = 0; i < cameFrom[current.id].size(); i++) {
//        current = cameFrom[current.id][i];
//        totalPath.push_back(current);
//    }
//    return totalPath;
    std::vector<Node> totalPath;
    std::vector<Node> temp;

    this->totalPath.push_back(current);
 //   std::cout << ' ' << current.id;
    //current.id = -1;
/*    int x;
    while(x<20){
        temp = mathPath[current.id];
        std::cout << ' ' << current.id;
        current = mathPath[current.id][0];
        for(int i=0; i < temp.size(); i ++){
            this->totalPath.push_back(temp[i]);

        }
        x++;
    }*/
    Node n;

    while(n.id != pessoa.start.id) {
        temp = mathPath[current.id];
        n = temp[0];
        current = temp[0];

        std::cout << ' ' << current.id;
        this->totalPath.push_back(temp[0]);
    }
  //  imprimiPath();
    std::cout << std::endl;

    return totalPath;

    //return mathPath[current.id];
}

void DStar:: imprimiPath(){
    std::cout << " imprimi path"<< std::endl;
    for(int i =0; i < totalPath.size(); i++){
        std::cout << ' ' << i;

    }
}

float DStar::calculaDistancia(Map atual, Map destino) {

    float dx, dy;
    dx = atual.x - destino.x;
    dy = atual.y - destino.y;

    float dist = sqrt(dx * dx + dy * dy);

    return dist;

}

Node DStar::menorFScore(std::vector<Node> open) {

    //  std::sort (open.begin(), open.end(), compara());
    sort(this->open.begin(), this->open.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.f < rhs.f;
    });
    for (std::vector<Node>::iterator it = this->open.begin(); it != this->open.end(); ++it)
     //   std::cout << ' ' << it->id;
  //  std::cout << '\n';

    return this->open[0];

}

std::vector<Node> DStar::expand(Node current) {
    int id = current.id;

    std::vector<Node> temp;
    temp = listaAdj[id];
    return temp;
}

