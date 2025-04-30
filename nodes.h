#pragma once
#include "coord.h"
#include "magic_const.h"
#include <vector>
#include <set>
class Edge;
class GameBoard;
class Node
{
private:
    
public: //TODO public
Node();
    std::vector<Edge*> own_edges; //ez honnan tudja hogy mi az az Edge lol?
    
    Coordinate pos;
    
    GameBoard* p_GB;


    std::set<char> resources;  //nyilvan nem char hanem Resource osztaly
    
    
    
    

    Node(Coordinate,GameBoard*);


    void AddResource(char); //nyilvan nem char hanem resource osztaly

    std::vector<Node*> GetNeighbours();
};