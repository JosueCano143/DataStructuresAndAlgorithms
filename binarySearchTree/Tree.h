#ifndef BST_H
#define BST_H

#include <string>
using namespace std; 
  
class Tree { 
    private:
        Tree *pLeft, *pRight;   
        int counter;
        string ip; 
  
    public: 
        Tree(); 
        Tree(string); 

        void preorder(Tree *);
        Tree* insert(Tree *, string);
        void top5(Tree *root, vector <Tree*> &top);
        int getCounter();
        string getIp();     
}; 
  
Tree :: Tree() {
    ip = ""; 
    counter = 1;  
    pLeft = nullptr;
    pRight = nullptr;
} 

Tree :: Tree(string myValue) { 
    ip = myValue; 
    pLeft = pRight = NULL; 
    counter = 1; 
} 

/**
 * @brief Inserts a new node, if is repeated the counter increases +1
 * 
 * Complexity: O(h)
 * 
 * @param root 
 * @param myValue 
 * @return Tree* 
 */
Tree* Tree :: insert(Tree *root, string myValue) { 
    if (!root) {
        return new Tree(myValue); 
    }
  
    if (myValue > root->ip)  // Insert right node data if value is greater
        root->pRight = insert(root->pRight, myValue); 

    else if (myValue < root->ip)  // Insert left node data if value is less
        root->pLeft = insert(root->pLeft, myValue);
    
    else if (myValue == root->ip) // Counter +1
    {
        root->counter += 1;
    }  
    return root; 
}

// Allows access to private data
int Tree::getCounter() { return this->counter; }
string Tree::getIp() { return this->ip; }

/**
 * @brief Inserts all the nodes into a vector
 * 
 * Complexity: O(n)
 * 
 * @param root 
 * @param top 
 */
void Tree::top5(Tree *root, vector <Tree*> &top){ 

    if (root != nullptr) {
        
        top.push_back(root);

        top5(root->pLeft, top); 
        top5(root->pRight, top);       
    }
}
#endif 