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


    Node* Tree::help(Node* root,Node* root2,int counter,string fORm)
        {
            // Base Cases: root is null or key is present at root
            if (HighRecursive(root->name,root2,0)==counter&&root->rank==fORm)
                return root;

                if(root->father!= nullptr)
                  return help(root->father,root2,counter,fORm);

                  if(root->mother!= nullptr)
                  return help(root->mother,root2,counter,fORm);

                 // cout<<root->rank<<root->name<<endl<<HighRecursive(root->name,root2,0)<<endl;


            /*    if(HighRecursive(root->name,root,0)==counter&&root->rank==fORm)
                    return root->name;
                if(root->father!= nullptr)
                  help(root->father,root2,counter,fORm);

                  if(root->mother!= nullptr)
                  help(root->mother,root2,counter,fORm);

                 // cout<<root->rank<<root->name<<endl<<HighRecursive(root->name,root2,0)<<endl;
          */

    }

/*
    void printPostorder(struct Node* node)
    {
        if (node == NULL)
            return;

        // first recur on left subtree
        printPostorder(node->left);

        // then recur on right subtree
        printPostorder(node->right);

        // now deal with the node
        cout << node->data << " ";
    }*/






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



        string Tree::find(string relation)
        {
            if(relation=="me")
            {
                if (root!= nullptr) return root->name;
                else  throw invalid_argument("no root");
            }

        else if(relation=="mother")
            {
            if (root!= nullptr&&root->mother!= nullptr)
            return root->mother->name;
            else  throw invalid_argument("no mother");
            }

        else if(relation=="father")
        {
                if (root != nullptr && root->father != nullptr)
                    return root->father->name;
                else throw invalid_argument("no mother");
        }
        else if(relation=="grandfather")
        {
        if(root != nullptr && root->father != nullptr && root->father->father!= nullptr)
         return root->father->father->name;
        else if (root != nullptr && root->mother != nullptr && root->mother->father!= nullptr)
            return root->mother->father->name;
        else throw invalid_argument("no grandfather");
        }
            else if(relation=="grandmother")
            {
                if(root != nullptr && root->father != nullptr && root->father->mother!= nullptr)
                    return root->father->mother->name;
                else if (root != nullptr && root->mother != nullptr && root->mother->mother!= nullptr)
                    return root->mother->mother->name;
                else throw invalid_argument("no grandmother");
            }
            else
            {
                string fORm="";
                int counter=2,saveLast=0;
                for(int i=0; i<relation.length();i++)
                {
                   if(relation.at(i)=='-')
                   {
                       counter++;
                       saveLast=i;
                   }
                }
                if (relation.at(saveLast+6)=='f') fORm="father";
                else fORm="mother";
                    Node* ans = help(root,root, counter, fORm);


                return ans->name;

            }
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
