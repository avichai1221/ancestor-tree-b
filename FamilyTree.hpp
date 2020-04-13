//
// Created by avichai on 4/6/20.
//

/*#ifndef CPPMATALA_FAMILYTREE_HPP
#define CPPMATALA_FAMILYTREE_HPP

#endif //CPPMATALA_FAMILYTREE_HPP*/
#include <stdbool.h>
#include <iostream>

namespace family{

class Node{
public:
    std::string name;
    Node* mother;
    Node* father;
    std::string rank;

//constractor+destractor

        Node (std::string root);
        ~Node();

};

class Tree{

public:
    Node* root;
    int counter;


    Tree& addFather(std::string son,std::string father);
    void searchFather(std::string son,std::string father,Node* root);
    void searchMother(std::string son,std::string mother,Node* root);
    Tree& addMother(std::string son,std::string mother);
    int HighRecursive(std::string name, Node* node,int level);
    void display();
    void print(Node* root, int level);



    std::string relation(std::string name);
    Node* findNodeName(std::string name,Node* node);
    Node* help(std::string name,Node* root);
    std::string find(std::string relation);
    void remove(std::string name);

//constractor+destractor

Tree (std::string root);
~Tree();

    };
};