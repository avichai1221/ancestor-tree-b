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


    Tree& Tree::searchFather(string son,string father,Node* root)
    {

        while ( root != NULL) {
            if (root->name == son) // we found the son
            {
                if (root->father == NULL) // No father, so add
                {
                    root->father = new Node(father);
                    counter++;
                } else   //have a father so replace
                {
                    root->father->name = father;
                    counter++;
                }
            }
            else //Keep searching
                {

                if (root->father != NULL)
                    searchFather(son, father, root->father);
                if (root->mother != NULL)
                    searchFather(son, father, root->mother);
                }

            return *this;
        }

        return *this;
    }
    Tree &Tree::addFather(string son, string father)
    {
        Node *save = root;
        searchFather(son,father,root);
        root = save;
        return *this;
    }

    Tree& Tree::searchMother(string son,string mother,Node* root)
    {



        while ( root != NULL)
        {
            if (root->name == son) // we found the son
            {
                if (root->mother == NULL)
                { // No mother, so add
                    root->mother = new Node(mother);
                    counter++;
                }
                else //have a mother so replace
                {
                    root->mother->name = mother;
                    counter++;
                }

            }
            else //Keep searching
                {
                if (root->father != NULL)
                    searchMother(son, mother, root->father);
                 if (root->mother != NULL)
                    searchMother(son, mother, root->mother);

               }

            return *this;
        }
        return *this;
    }

    Tree &Tree::addMother(string son, string mother)
    {
        Node *save = root;
        searchMother(son,mother,root);
        root = save;
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
        string ans = "unrelated";


    if(root->name==name) ans= "me";
    else if(root->mother->name==name) ans="mother";
    else if(root->father->name==name) ans="father";
    else if((root->mother->mother->name==name)||(root->father->mother->name==name)) ans="grandmother";
    else if((root->father->father->name==name)||(root->mother->father->name==name)) ans="grandfather";
    else
       help(name,root);
            return ans;
    }





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
        }
        Node::~Node()
        {
            delete mother;
            delete father;
        }


    };
