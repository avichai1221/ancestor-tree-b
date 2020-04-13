//
// Created by avichai on 4/6/20.
//

#include "FamilyTree.hpp"
using namespace std;
namespace family {


    Tree::Tree(string root) {
        this->root = new Node(root);
        this->counter = 1;

    }


    Tree::~Tree() {
        delete this->root;
    }

    //tree high
    int Tree::HighRecursive(string name, Node *node, int level)
    {
        if (node == nullptr)
            return 0;
        if (node->name == name)
            return level;

        int downlevel = HighRecursive(name, node->father, level + 1);

        if (downlevel != 0)
            return downlevel;

        downlevel = HighRecursive(name, node->mother, level + 1);

        return downlevel;
    }

    void Tree::searchFather(string son, string father, Node *root)
    {

        if (root == nullptr)
            return ;
        else
            {

            if (root->name == son) // we found the son
            {
                if (root->father == nullptr) // No father, so add
                {
                    root->father = new Node(father);
                    int level = 0;
                  //  int num = HighRecursive(father, root, level);
                        root->father->rank = "father";
                    /*if (num == 2)
                        root->father->rank = "grandfather";
                    if (num > 2) {

                        for (int i = 2; i < num; i++) {
                            root->father->rank = root->father->rank + "great-";
                        }
                        root->father->rank = root->father->rank + "grandfather";
                    }*/
                    counter++;
                } else   //have a father so replace
                {
                    root->father->name = father;
                    root->father->rank = "father";
                    counter++;
                }

            }
            else {
                searchFather(son, father, root->father);
                searchFather(son, father, root->mother);
            }
        }

    }

    Tree &Tree::addFather(string son, string father)
    {
        searchFather(son,father,root);
        return *this;

    }

    void Tree::searchMother(string son,string mother,Node* root)
    {
        if(root==nullptr)
            return;
        else
        {
            if (root->name == son) // we found the son
            {
                if (root->mother == nullptr) // No mother, so add
                {
                    root->mother = new Node(mother);
                  //  int level = 0;
                  //  int num = HighRecursive(mother, root, level);
                   // if (num == 1)
                        root->mother->rank = "mother";
                    /*if (num == 2)
                        root->mother->rank = "grandmother";
                    if (num > 2) {

                        for (int i = 2; i < num; i++) {
                            root->mother->rank = root->mother->rank + "great-";
                        }
                        root->mother->rank = root->mother->rank + "grandmother";*/
                   // }
                    counter++;
                } else   //have a mother so replace
                {
                    root->mother->name = mother;
                    root->mother->rank = "mother";
                    counter++;
                }
            }
            searchMother(son, mother, root->father);
            searchMother(son, mother, root->mother);

               }

    }

    Tree &Tree::addMother(string son, string mother)
    {
        searchMother(son,mother,root);
        return *this;
    }


    void Tree::display() //help from geeksforgeeks
    {
        cout << "notice! the mothers is up and fathers is down!" << endl;
        // Root without spaces
        print(root, 0);
    }
    void Tree::print(Node* root, int space) //Print (right,root,left)--> (mather,child,father)
    {
    if (root == NULL) // Nothing to print
    return;

    //  For know how much space to take (We want it be clear for show)
    space =space+ counter;

    // mother first
        print(root->mother, space);


    cout<<endl;
    for (int i = counter; i < space; i++)
    cout<<" ";
    cout<<root->name<<"\n\n";

    // father
        print(root->father, space);
    }


    Node* Tree::help(string name,Node* temp) {
        return temp;
    }

//The function returns the reference between the input and root.
    string Tree::relation(string name)
    {
        string ans = "";

if(root!= nullptr)
{
    if(root->name==name) ans= "me";
    else if(root->mother!= nullptr&&root->mother->name==name) ans="mother";
    else if(root->father->name==name) ans="father";
    else if((root->mother->mother!= nullptr&&root->mother->mother->name==name)||(root->father->mother!= nullptr&&root->father->mother->name==name)) ans="grandmother";
    else if((root->mother->father!= nullptr&&root->mother->father->name==name)||(root->father->father!= nullptr&&root->father->father->name==name)) ans="grandfather";
    else
        {
              int num = HighRecursive(name, root, 0);
              if(num==0) ans="unrelated"; //no name like this
            if (num > 2)
            {
                for (int i = 2; i < num; i++)
                {
                    ans="great-"+ans;
                }
                Node* help=findNodeName(name,root);
                if(help->rank=="mother")
               ans=ans+"grandmother";
                else ans=ans+"grandfather";
             }


    }

}

            return ans;
    }


    Node* Tree:: findNodeName(string name,Node* node)
    {
        if(node==nullptr)
            return nullptr;
        if(node->name==name)
            return node;

        Node* found=findNodeName(name,node->father);

        if(found!=nullptr)
            return found;

        return findNodeName(name,node->mother);
    }
   /* string Tree:: relation(string name)
    {

        if(root->name==name)
            cout <<root->rank;;

       Node* node=findNodeName(name,root);
        if(node!=NULL&&node->name==name)
            cout << node->rank<< " ";
        else
            cout << "unrelated" << " ";
    }*/




        string Tree::find(string relation)
        {
            return "Dsds";
        }
        void Tree::remove(string name)
        {


        }


    Node::Node(std::string root)
        {
            name = root;
            mother = NULL;
            father = NULL;
            rank ="me";

        }
        Node::~Node()
        {
            delete mother;
            delete father;
        }


    };
