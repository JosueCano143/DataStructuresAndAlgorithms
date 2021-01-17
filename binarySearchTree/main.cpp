/**
 * @file main.cpp
 * @authors
 * Alejandra Guadalupe Olivas Altamirano  A01741389
 * Carolina Gómez Manzano                 A01632229 
 * Josue Salvador Cano Martinez           A00829022 
 * 
 * @brief Act 3.4 - Actividad Integral de BST (Evidencia Competencia)
 * @version 0.1
 * @date 2020-10-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#include "Tree.h"

using namespace std;

/**
 * @brief Changes ip format
 * 
 * @param ip 
 */
void createNewIp(string &ip) {
    string currentblock, newIpAddress;
    int index;

    // Create a new ip
    for (int i = 0;i < 4; i++) {

        index = ip.find("."); 
        currentblock = ip.substr(0,index);  // Get the new block

        if (currentblock.length() < 3) {
            currentblock.insert(0,3-currentblock.length(),'0');
        }

        newIpAddress.append(currentblock);
        if(i < 3)
            newIpAddress.append(".");

        // Set the beginning of the next block
        ip = ip.substr(index+1);
    }
    
    ip = newIpAddress;
}

/**
 * @brief Changes the line (just ip address is needed)
 * 
 * @param line 
 */
void createNewLine(string &line) {
    string ip = "";
    int c = 0;

    ip = line.substr(16);
    
    // Count ip length
    while(ip[c] != ':') {
        c++;
    }    
    ip = ip.substr(0,c);
    createNewIp(ip);

    line = ip;
}

/**
 * @brief Gets back into original ip format
 * 
 * @param line 
 * @return string 
 */
string revertLine(string line) {
    int k = 0, index = 0;
  
    // Delete zeros
    for(int i = 0; i <= line.length(); i++) {
        if (line[k] == '0') {
            if (line[k-1] == '0' || line[k-1] == '.' || k == 0) {
                line.erase(k,1);
            } else {
                k++;
            }
        } else {
            k++;
        }
    }
    return line;
}

/**
 * @brief Reads the file and inserts each ip into a BST
 * 
 * Complexity O(n)
 * 
 * @param archivo 
 * @param tree 
 * @param root 
 */
void readFile(string archivo, Tree tree, Tree *&root) {
    ifstream in(archivo.c_str());
    string str;
    int c = 0;

    while (getline(in, str)) {
        createNewLine(str);
        if (c == 0) {
            root = tree.insert(root, str);
            c++;
        } else
        {
            tree.insert(root, str); // O(h)
        }       
    }
    in.close();
}

/**
 * @brief Compares two Tree nodes by its counter
 * 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
bool compare(Tree* &a, Tree* &b) {
    return a->getCounter() < b->getCounter();
}

int main() {
    Tree tree, *root = NULL;
    vector <Tree*> top;

    readFile("bitacora.txt", tree,root);

    tree.top5(root, top);

    // Make a heap from top vector
    // Complexity: 3*std::distance (first, last) where distance is linear
    make_heap(top.begin(), top.end(), compare);
   
    cout << "Direcciones ip con mayor cantidad de accesos (Puesto | No. de accesos | Dirección)" << endl;
    
    // Get heap top and pop
    for(int i = 1; i <= 5; i++) {
        cout << i << ". " << top.front()->getCounter() << " " << revertLine(top.front()->getIp()) << endl;
        
        // 2*log(n) comparisons, where n = std::distance (linear)
        pop_heap(top.begin(), top.end(), compare);
        top.pop_back();    
    
    }

    // Delete vector of pointers
    for (int i =0; i< top.size();i++){
     delete (top[i]);
    } 
    top.clear();
           
}

