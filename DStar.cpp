//
// Created by nao on 21/11/18.
//

#include "DStar.h"
#include <iostream>
#include <algorithm>    // std::find


Node::Node() {
    this->g = INT_MAX;
    this->h = 0;
    this->f = 0;
//    this->estado = 0;

}

Node::~Node() {

}

DStar::DStar(NavMesh *nav, int tamanho, Agente *agente) {
    int m = 0;

    std::vector<Node> temp;
//
//    int j = 0;
//    Node nox;
//    nox.pontos.x = 15;
//    nox.pontos.y = 495;
//    nox.id = m;
//    if (nox.pontos.x == agente->start.x && nox.pontos.y == agente->start.y) {
//        pessoa.start.id = m;
//    }
//    if (nox.pontos.x == agente->end.x && nox.pontos.y == agente->end.y) {
//        pessoa.end.id = m;
//    }
//    temp = nosVizinhos(nox, 0, 10);
//    listaAdj.push_back(temp);
//    temp.clear();
    //m++;

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {

            Node nox;
            nox.pontos.x = (i * 10) + 5;
            nox.pontos.y = (j * 10) + 5;
            nox.id = m;
            if (nox.pontos.x == agente->start.x && nox.pontos.y == agente->start.y) {
                pessoa.start.id = m;
            }
            if (nox.pontos.x == agente->end.x && nox.pontos.y == agente->end.y) {
                pessoa.end.id = m;
            }
            temp = nosVizinhos(nox, 0, 50);
            listaAdj.push_back(temp);
            temp.clear();
            m++;
        }
    }
    imprime();
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


void DStar::ligaTodosNos() {

/*    while(!listaAdj.end()) {
        Node novo = listaAd;
        ///coluna da esquerda
        if(no[i].x == 5){
            ///baixo
            if(no[y].y == 5){

             //cima
            }else if(no.y == 45){

            }else{
                listaAdj[i].push_back(No)

            }

        }
    }*/

}

std::vector<Node> DStar::nosVizinhos(Node n, int tipo, int tamanho) {


    std::vector<Node> vizinhos;
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
            return vizinhos;

        }
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
            return vizinhos;
        }

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

            return vizinhos;

        }


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
            return vizinhos;
        }
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

        current = menorFScore(open);
        if (current.pontos.x == pessoa.end.x && current.pontos.y == pessoa.end.y) {
            ///encontrou caminho
            return reconstructPath(mapPath, current);
        }


        open.erase(open.begin()); //remove de open
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
            if (std::find(closed.begin(), closed.end(), vizinhos[i]) != closed.end()) {
                if (g >= vizinhos[i].g) {
                    continue;
                }
            } else {
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
    totalPath.push_back(current);
    for (int i = 0; i < mathPath[current.id].size(); i++) {
        current = mathPath[current.id][i];
        totalPath.push_back(current);
    }
    return totalPath;

    //return mathPath[current.id];
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
    sort(open.begin(), open.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.f < rhs.f;
    });
    for (std::vector<Node>::iterator it = open.begin(); it != open.end(); ++it)
     //   std::cout << ' ' << it->id;
  //  std::cout << '\n';

    return open[0];

}

std::vector<Node> DStar::expand(Node current) {
    int id = current.id;

    std::vector<Node> temp;
    temp = listaAdj[id];
    return temp;
}

