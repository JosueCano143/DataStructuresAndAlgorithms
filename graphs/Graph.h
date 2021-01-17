/**
 * @file Graph.h
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

#include "Vertex.h"
#include <algorithm>

class Graph
{
public:
    Graph(vector<string> labels);
    list<shared_ptr<Vertex>> vertices; // Container for vertices as lists of connections
    void addEdge(string u, string v);
    int getSize(){ return this->vertices.size(); }
    void printGraph();
    void getAnswers();
    list<shared_ptr<Vertex>> ipVector;
    list<shared_ptr<Vertex>> portVector;
};

/**
 * @brief Construct a new Graph:: Graph object
 * 
 * @param labels 
 * 
 * Complexity: O(n)
 */
Graph::Graph(vector<string> labels){
    for(const string it : labels){
        this->vertices.emplace_back(make_shared<Vertex>(it));
    }
}

/**
 * @brief Adds an edge between two vertices
 * 
 * @param u A string representing the label of a vertex
 * @param v A string representing the label of a vertex
 * 
 * Complexity: O(n)
 */
void Graph::addEdge(string u, string v){

    list<shared_ptr<Vertex>>::iterator pu, pv;
    pu = find_if(this->vertices.begin(), this->vertices.end(),
                    [u](shared_ptr<Vertex> x){return x->getName() == u;});
    pv = find_if(this->vertices.begin(), this->vertices.end(),
                    [v](shared_ptr<Vertex> x){return x->getName() == v;});

    if (pu == this->vertices.end() && pv == this->vertices.end()){
        // if they don't exist, add them

        this->vertices.emplace_back(make_shared<Vertex>(u));
        shared_ptr<Vertex> U = this->vertices.back();
        this->vertices.emplace_back(make_shared<Vertex>(v));
        shared_ptr<Vertex> V = this->vertices.back();

        U->addConnection(weak_ptr<Vertex>(V));
        V->addConnection(weak_ptr<Vertex>(U));

        this->ipVector.emplace_back(U);
        this->portVector.emplace_back(V);

    }
    else if(pv == this->vertices.end()){
        //only pu exists, so create pv and find U
        shared_ptr<Vertex> U(*pu);  // this increases the counter of the smart pointer of the object at pu
        this->vertices.emplace_back(make_shared<Vertex>(v));
        shared_ptr<Vertex> V = this->vertices.back();

        U->addConnection(weak_ptr<Vertex>(V));
        V->addConnection(weak_ptr<Vertex>(U));

        //sumar 1 a ip
        U->addCounter();
        this->portVector.emplace_back(V);
        
    }
    else if(pu == this->vertices.end()){
        //only pv exists, so add pu and find V
        shared_ptr<Vertex> V(*pv);  // this increases the counter of the smart pointer of the object at pu
        this->vertices.emplace_back(make_shared<Vertex>(u));
        shared_ptr<Vertex> U = this->vertices.back();

        U->addConnection(weak_ptr<Vertex>(V));
        V->addConnection(weak_ptr<Vertex>(U));

        V->addCounter();
        this->ipVector.emplace_back(U);
    }
    else{
        //both exist, so find them both
        // these two generate a normal pointer to the object at pu and pv, which is scope-dependent
        shared_ptr<Vertex> U(*pu); 
        shared_ptr<Vertex> V(*pv);

        U->addConnection(weak_ptr<Vertex>(V));
        V->addConnection(weak_ptr<Vertex>(U));

        U->addCounter();
        V->addCounter();
    }
}
/**
 * @brief Prints the graph by adjacency lists
 * 
 * Complexity: O(n)
 */
void Graph::printGraph(){

    for(const shared_ptr<Vertex> current : this->vertices){
        cout << current->getName() << " has the following connections: [";
        //each vertex prints its neighbors
        current->printNeighborhood();
        cout << "]" << endl;
    }
} 

void Graph::getAnswers() {
    int auxIp = 0, auxPort = 0;  
    string theIp, thePort; 

    for (const shared_ptr<Vertex> current : this->ipVector) {
        if (current->getCounter() > auxIp) {
            auxIp = current->getCounter();
            theIp = current->getName();
        }
    }
    for (const shared_ptr<Vertex> current : this->portVector) {
        if (current->getCounter() > auxPort) {
            auxPort = current->getCounter();
            thePort = current->getName();
        }
    }
    cout << "La ip mas atacada es: " << theIp << " con: " << auxIp << " ataques" << endl;
    cout << "El puerto mas atacado es: " << thePort << " con: " << auxPort << " ataques" << endl;
}