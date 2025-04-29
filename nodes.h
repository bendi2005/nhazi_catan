#pragma once
#include "coord.h"
#include "magic_const.h"
#include <vector>
class Edge;
class Node
{
public: //TODO public

    std::vector<Edge*> own_edges; //ez honnan tudja hogy mi az az Edge lol?
    
    Coordinate pos;
    
    std::set<char> resources;  //nyilvan nem char hanem Resource osztaly
    
    
    Node();
    

    Node(Coordinate,int,GameBoard*);


    void AddResource(char); //nyilvan nem char hanem resource osztaly


    
    void CheckEdges();
};