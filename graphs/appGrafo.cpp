/**
 * @file appGrafo.cpp
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

#include "Graph.h"
#include <fstream>

/**
 * @brief Application of the created classes
 * 
 * @return nothing
 */
int main()
{
  string str;
  string nameFile = "bitacora.txt";

  vector<string> V = {};
  Graph graph = Graph(V);

  ifstream in(nameFile.c_str());
  while (getline(in, str)) {
    //createNewLine(str); 
    string ip = "", port = "";
    int aux1 = 0, aux2 = 0;

    ip = str.substr(16);
    // Count ip length
    while(ip[aux1] != ':') 
      aux1++; 

    port = str.substr(aux1 + 17);
    while(port[aux2] != ' ')  
      aux2++;

    ip = ip.substr(0, aux1);
    port = port.substr(0, aux2);

    graph.addEdge(ip, port);    
  }
  in.close();
  graph.getAnswers();
}