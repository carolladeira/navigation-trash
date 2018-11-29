//
// Created by nao on 21/11/18.
//

#include "DStar.h"
#include <iostream>
#include <algorithm>    // std::find, min
#include <stdlib.h>
#include <GL/glut.h>

#define DEBUG


Node::Node() {
    this->g = INT_MAX;
    this->h = 0;
    this->f = INT_MAX;
    this->rhs = INT_MAX;
    this->estado = NULL;
    this->ocupado = false;
}

Node::~Node() {

}

DStar::DStar(NavMesh *nav, int tamanho, Agente *agente, Wall *objetos) {
    int m = 0;
    std::vector<Node> temp;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {


            Node nox;
            nox.pontos.x = (i * 10) + 5;
            nox.pontos.y = (j * 10) + 5;
            nox.id = m;
            if(nav->_meshes[i][j] == 1){
                obstacles.push_back(nox);
                custo[nox.id].ocupado = true;
#ifdef DEBUG
                std::cout  << " :  " << nox.id;
#endif
                //continue;
            }
            if (((agente->start.x - 5) <= nox.pontos.x == true) && (((agente->start.x + 5) >= nox.pontos.x == true))){
                if (((agente->start.y - 5) <= nox.pontos.y == true) && (((agente->start.y + 5) >= nox.pontos.y == true))){
                    this->s_start.id = m;
                    this->s_start.pontos = agente->start;
//#ifdef DEBUG
//    std::cout<<std::endl;
//    std::cout<<"--------------D Star Lite-----------------------" <<std::endl;
//    std::cout  << "START | m: " << m << std::endl;
//    std::cout  << "agente: " << agente->start.x << " " << agente->start.y << " - ";
//    std::cout  << "nox: " << nox.pontos.x << " " << nox.pontos.y<< std::endl;
//#endif
                }
            }
            if (((agente->end.x - 5) <= nox.pontos.x == true) && (((agente->end.x + 5) >= nox.pontos.x == true))){
                if (((agente->end.y - 5) <= nox.pontos.y == true) && (((agente->end.y + 5) >= nox.pontos.y == true))){
                 //   pessoa.end.id = m;
                    this->s_end.id = m;
                    this->s_end.pontos = agente->end;
//#ifdef DEBUG
//    std::cout<<std::endl;
//    std::cout  << "END | m: " << m << std::endl;
//    std::cout  << "agente: " << agente->start.x << " " << agente->start.y << " - ";
//    std::cout  << "nox: " << nox.pontos.x << " " << nox.pontos.y<< std::endl;
//#endif
                }
            }
            temp = nosVizinhos(nox, 0, 50);
            listaAdj.push_back(temp);
            temp.clear();
            m++;
        }
    }
#ifdef DEBUG
    std::cout<<std::endl;
    std::cout<<"START: "<<this->s_start.id<<" " ;
    std::cout<<" END: "<<this->s_end.id<<" " ;

#endif
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

std::vector<Node> DStar::AStar() {
    open1.clear();
    closed1.clear();
    mapPath->clear();
    totalPath.clear();
    Node node;
    node.g = 0;
    node.pontos = s_start.pontos;
    node.id = s_start.id;
    node.f = calculaDistancia(s_start, s_end);
    open1.push_back(node);

    std::vector<Node> vizinhos;
    std::vector<Node> temp;


    float g =0;
    Node current;
    while (!open1.empty()) {

        current = menorFScore(this->open1);
        if (current.id == s_end.id) {
            ///encontrou caminho
            return reconstructPath(mapPath, current);
        }

        this->open1.erase(this->open1.begin()); //remove de open
        closed1.push_back(current); //adiciona em closed

        vizinhos = expand(current); //descobrir o sucessor e gerar os pais dele de bestNode

        for (int i = 0; i < vizinhos.size(); i++) ///para cada vizinho do atual
        {

            /// Ignore the neighbor which is already evaluated.
            if (std::find(closed1.begin(), closed1.end(), vizinhos[i]) != closed1.end()) {
                continue;
            }

            // The distance from start to a neighbor
            g = current.g + calculaDistancia(current, vizinhos[i]);


            // if neighbor not in openSet,  Discover a new node
            if (std::find(open1.begin(), open1.end(), vizinhos[i]) != open1.end()) {
                if (g >= vizinhos[i].g) {
                    continue;
                }
            } else {
                vizinhos[i].g = g;
                vizinhos[i].h = calculaDistancia(vizinhos[i], s_end);
                vizinhos[i].f = vizinhos[i].g + vizinhos[i].h;
                open1.push_back(vizinhos[i]);
            }

            //temp.push_back(current);
///            cameFrom[vizinhos[i].id].push_back(current);
            mapPath[vizinhos[i].id].push_back(current);
            //mapPath[vizinhos[i].id] = current;
            vizinhos[i].g = g;
            vizinhos[i].h = calculaDistancia(vizinhos[i], s_end);
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

    while(n.id != s_start.id) {
        temp = mathPath[current.id];
        n = temp[0];
        current = temp[0];

    //    std::cout << ' ' << current.id;
        this->totalPath.push_back(temp[0]);
    }
  //  imprimiPath();
//    std::cout << std::endl;

    return totalPath;

    //return mathPath[current.id];
}

void DStar:: imprimiPath(){
    std::cout << " imprimi path"<< std::endl;
    for(int i =0; i < closed.size(); i++){
        std::cout << ' ' << closed[i].id;

    }
}

float DStar::calculaDistancia(Node atual, Node destino) {

    if(custo[atual.id].ocupado == true || custo[destino.id].ocupado == true){
        return INT_MAX;
    }else{
        float dx, dy;
        dx = abs(atual.pontos.x - destino.pontos.x);
        dy = abs(atual.pontos.y - destino.pontos.y);

        float dist = sqrt(dx * dx + dy * dy);

        return dist;
    }


}

Node DStar::menorFScore(std::vector<Node> open) {

    //  std::sort (open.begin(), open.end(), compara());
    sort(this->open1.begin(), this->open1.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.f < rhs.f;
    });
    for (std::vector<Node>::iterator it = this->open1.begin(); it != this->open1.end(); ++it)
     //   std::cout << ' ' << it->id;
  //  std::cout << '\n';

    return this->open1[0];

}

std::vector<Node> DStar::expand(Node current) {
    int id = current.id;

    std::vector<Node> temp;
    temp = listaAdj[id];
    return temp;
}

void DStar:: DStarLite(Agente* agente, NavMesh *navMesh){
    if(s_start.id == s_end.id){
        return;
    }

    closed.clear();
    int km=0;
    float c_old;

    s_end.pontos = s_end.pontos;
    s_end.id = s_end.id;
    s_end.rhs = 0;
    s_end.h = calculaDistancia(s_start, s_end);
    Pair m;
    m.first = s_end.h;
    m.second = 0;
    s_end.key = m;
    open.push_back(s_end);
    closed.push_back(s_start);

    Node s_last, s_inicio;
    s_inicio.pontos = s_start.pontos;
    s_inicio.id = s_start.id;
    s_last = s_inicio;
    Node u, v;
    custo[s_end.id].rhs = 0;
    custo[s_end.id].estado=1;
    computeShortestPath(km);

    while(s_inicio.id != s_end.id){
       s_inicio = min_succ(s_inicio);
       this->closed.push_back(s_inicio);
      // agente->atualizaPosicao(s_inicio.pontos);
       ///VERIFICA CAMINHO
       // atualizaCaminho(navMesh);

#ifdef DEBUG
        std::cout  << "id:  " << s_inicio.id<< std::endl;
#endif
       km = km + calculaDistancia(s_last,s_inicio);
       s_last = s_inicio;
       u = s_last;
       for (int i = 0; i < listaAdj[s_last.id].size(); i++) ///para cada vizinho do s_last
       {
            v = listaAdj[s_last.id][i];
            c_old = calculaDistancia(u,v);
            if(c_old > calculaDistancia(u,v)){
                if(u.id != s_end.id) {
                    custo[u.id].rhs = std::min(getRhs(u), calculaDistancia(u, v) + getG(v));
                    custo[u.id].g = getG(u);
                    custo[u.id].estado=1;
                    u.rhs = custo[u.id].rhs;
                }

            }else if(u.rhs == c_old + getG(v)){
                if(u.id != s_end.id) {
                    custo[u.id].rhs = min_succ(u).rhs;
                    custo[u.id].g = getG(u);
                    custo[u.id].estado=1;
                    u.rhs = custo[u.id].rhs;

                }
            }
           updateVertex(u, km);

       }
        computeShortestPath(km);

    }
}
void DStar::atualizaCaminho(NavMesh *navMesh){
    int m=0;
    for(int i=0; i <50; i++){
        for(int j=0; j<50; j++){
            if(navMesh->_meshes[i][j]==true){
                this->custo[m].ocupado = true;
            }
            m++;
        }
    }
}

void DStar::computeShortestPath(float km){
    if(this->s_start.id == this->s_end.id){
        return;
    }
    Node u, s;
    int m;
    float g_old;
    Pair k_old, k_new;
    while(!this->open.empty() && (compara(ordena(this->open).key,calculateKey(s_start,km)) == true) || (custo[s_start.id].rhs > custo[s_start.id].g)){
        u = this->open[0];
        k_old = u.key;
        k_new = calculateKey(u,km);
        if(compara(k_old, k_new) == true){
            m= findI(u);
            u.key = k_new;
            this->open[m] = u;
        }else if(getG(u) > getRhs(u)){
            custo[u.id].g = getRhs(u);
            custo[u.id].estado=1;
            m=findI(u);
            this->open.erase(open.begin() + m);
            for(int i = 0; i < listaAdj[u.id].size(); i++){
                s = listaAdj[u.id][i];
                if(s.id != s_end.id){
                    s.rhs = std::min(custo[s.id].rhs, calculaDistancia(s,u) + custo[u.id].g);
                    custo[s.id].rhs = std::min(custo[s.id].rhs, calculaDistancia(s,u) + custo[u.id].g);
                    custo[s.id].g = getG(s);
                    custo[s.id].estado=1;
                }
                updateVertex(s,km);
            }
        }else{
            g_old = getG(u);
            custo[u.id].g= INT_MAX;
            custo[u.id].estado=1;
            for(int i = 0; i < listaAdj[u.id].size(); i++){
                s = listaAdj[u.id][i];
                if(getRhs(s)== calculaDistancia(s, u) + g_old){
                    if(s.id != this->s_end.id){
                        custo[s.id].rhs = min_succ(s).rhs;
                        custo[s.id].g = getG(s);
                        custo[s.id].estado=1;
                        s.rhs = custo[s.id].rhs;
                    }
                }
                updateVertex(s, km);
            }
        }
    }
}
void DStar::updateVertex(Node u, float km){
    Pair key;
    int m;

    ///u pertence a open
    if(getG(u) != getRhs(u) && std::find(this->open.begin(), this->open.end(), u) != this->open.end()){
        u.key = calculateKey(u,km);
        m= findI(u);
        this->open[m] = u;
    ///u nao pertence a open
    }else if(getG(u) != getRhs(u) ){
        if(std::find(this->open.begin(), this->open.end(), u) != this->open.end()){

        }else{
            u.key = calculateKey(u, km);
            this->open.push_back(u);
        }
    ///u pertence a open
    }else if(getG(u) == getRhs(u)&& std::find(this->open.begin(), this->open.end(), u) != this->open.end()){
        m=findI(u);
        this->open.erase(this->open.begin()+m);
    }
}
Pair DStar::calculateKey(Node s, float km){

    Pair k;
    float h = calculaDistancia(s, this->s_start);
    float val = std::min(getG(s), getRhs(s));
    k.first = val + h + km;
    k.second = val;
    return k;
}

int DStar::findI(Node u)
{
    for(int i=0;i<this->open.size(); i++){
        if(open[i].id == u.id){
            return i;
        }
    }
    return NULL;
}
Node DStar::min_succ(Node u)
{
    Node s;
    float c, custo_final = INT_MAX;
    Node final;
    float g1, dist;
    for(int i=0; i< this->listaAdj[u.id].size(); i++){
        s = this->listaAdj[u.id][i];
        dist = calculaDistancia(u, s);
        g1 = getG(s);
        c= dist + g1;
        if(c < custo_final){
            custo_final = c;
            final = s;
            final.rhs = custo_final;
        }
    }
    return final;
}
Node DStar::ordena(std::vector<Node> open) {
   //u < v if (u.first < v.first OR u.first == v.first AND u.second < v.second)
    sort(this->open.begin(), this->open.end(), [](const auto &u, const auto &v) {
         if (u.key.first < v.key.first || (u.key.first == v.key.first && u.key.second < v.key.second)){
             return true;
         }
    });
    for (std::vector<Node>::iterator it = this->open.begin(); it != this->open.end(); ++it)

        return this->open[0];

}
bool DStar::compara(Pair u, Pair s){
    if (u.first < s.first || (u.first == s.first && u.second < s.second)){
        return true; //u < s
    }
    return false;

}

float DStar::getG(Node u){
    if(this->custo[u.id].estado==NULL){
        return calculaDistancia(u, s_end);
    }else return custo[u.id].g;
}
float DStar::getRhs(Node u){
    if(u.id == s_end.id) return 0;
    if(this->custo[u.id].estado==NULL){
        return calculaDistancia(u, s_end);
    }else return custo[u.id].rhs;
}

void DStar::updateCell(int x, int y, float val) {
//#ifdef DEBUG
//    std::cout  << "id:  " <<x <<" " <<y<< std::endl;
//#endif
//    this->custo[53].ocupado= true;
//    Node n;
//    n.pontos = custo[53].pontos;
//    n.id = 53;
//    n.ocupado = true;
//    updateVertex(n,0);
//    DStarLite(age);
//    AStar();

}

void DStar::criaObstaculos(){
    int i=0;
    while(i<50){
        int id = rand() % (int)500;
        int j = id/50;
        int i = id%50;
        glPointSize((GLfloat)10.0f);
        glColor3f(0.0,0.0,1.0); //blue
        glBegin(GL_POINTS);
        glVertex2f(i, j);
        glEnd();

        this->custo[id].ocupado == true;

        int idlivre = rand() % (int)500;
        this->custo[idlivre].ocupado == true;
        i++;


    }

}
void DStar::updateStart(Node novo){
    s_start.pontos.x = novo.pontos.x;
    s_start.pontos.y = novo.pontos.y;
    s_start.id = novo.id;

    s_start.key = calculateKey(s_start,0);
}
