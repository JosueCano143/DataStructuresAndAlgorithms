/**
 * @file Vertex.h
 * @authors
 *  Carolina Gómez Manzano                  A01632229
 *  Alejandra Guadalupe Olivas Altamirano   A01741389
 *  Josue Salvador Cano Martinez            A00829022
 * @brief 
 * @version 0.1
 * @date 2020-11-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <list>

using namespace std;

class Vertex
{
private:
    string label;
    int counter;
public:
    Vertex(string name);
    //Vertex(int counter);
    list<weak_ptr<Vertex>> connections;

    string getName(){ return this->label; };
    int getCounter(){ return this->counter; };
    void addConnection(weak_ptr<Vertex> who);
    void addCounter(); 
    bool operator==(weak_ptr<Vertex> who) { return who.lock()->getName() == this->getName(); };

    void printNeighborhood();
};

/**
 * @brief Construct a new Vertex:: Vertex object
 * 
 * @param name 
 */
Vertex::Vertex(string name){
    this->label = name;
    this->counter = 1;
}

/**
 * @brief Adds who as a connection in this vertex
 * 
 * @param who A weak pointer to a Vertex object
 */
void Vertex::addConnection(weak_ptr<Vertex> who){
    this->connections.push_back(who);
}
void Vertex::addCounter() {
    this->counter += 1; 
}

/**
 * @brief Print the neighbors of a node 
 * 
 * Complexity: O(n)
 */
void Vertex::printNeighborhood(){

    for(const weak_ptr<Vertex> conn : this->connections){
        cout << conn.lock()->getName() << " ";
    }
}