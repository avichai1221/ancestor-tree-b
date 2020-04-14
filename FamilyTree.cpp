#include <iostream>
#include <stdexcept>
#include"FamilyTree.hpp"
using namespace std;




namespace family {

    Tree::treenode *Tree::creatNode(string name) {
        treenode *n = new treenode;
        n->name = name;
        n->left = NULL;
        n->right = NULL;
        return n;
    }

    Tree::Tree(string Name) {
        root = creatNode(Name);
        root->rank = "me";
    }

    bool Tree::equal(string a, string b) {
        if (a.length() != b.length())
            return false;
        for (int i = 0; i < a.length(); i++) {
            if (a[i] != b[i])
                return false;

        }
        return true;
    }


    int Tree::HighRecursive(string name, treenode *node, int level) {
        if (node == NULL)
            return 0;
        if (equal(node->name, name))
            return level;

        int downlevel = HighRecursive(name, node->left, level + 1);

        if (downlevel != 0)
            return downlevel;

        downlevel = HighRecursive(name, node->right, level + 1);

        return downlevel;
    }

    void Tree::addFatherRecursive(string child, string father, treenode *node) {

        if (node == NULL)
            return;
        if (node != NULL) {
            if (node->name != "" && equal(node->name, child)) {
                if (node->left == NULL) {
                    node->left = creatNode(father);
                    int level = 0;
                    int num = HighRecursive(father, root, level);
                    if (num == 1)
                        node->left->rank = "father";
                    if (num == 2)
                        node->left->rank = "grandfather";
                    if (num > 2) {

                        for (int i = 2; i < num; i++) {
                            node->left->rank = node->left->rank + "great-";
                        }
                        node->left->rank = node->left->rank + "grandfather";
                    }
                }
            }

        }

        addFatherRecursive(child, father, node->left);
        addFatherRecursive(child, father, node->right);
    }


    void Tree::addMotherRecursive(string child, string mother, treenode *node) {

        if (node == NULL)
            return;
        if (node != NULL) {
            if (node->name != "" && equal(node->name, child)) {
                if (node->right == NULL) {
                    node->right = creatNode(mother);
                    int level = 0;
                    int num = HighRecursive(mother, root, level);

                    if (num == 1)
                        node->right->rank = "mother";
                    if (num == 2)
                        node->right->rank = "grandmother";
                    if (num > 2) {

                        for (int i = 2; i < num; i++) {
                            node->right->rank = node->right->rank + "great-";
                        }
                        node->right->rank = node->right->rank + "grandmother";
                    }

                }
            }
        }
        addMotherRecursive(child, mother, node->left);
        addMotherRecursive(child, mother, node->right);

    }


    Tree::treenode *Tree::findNodeName(string name, treenode *node) {
        if (node == NULL)
            return NULL;
        if (node != NULL && equal(node->name, name))
            return node;

        treenode *found = findNodeName(name, node->left);

        if (found != NULL)
            return found;

        return findNodeName(name, node->right);
    }


    Tree::treenode *Tree::findNodeRank(string name, treenode *node) {
        if (node == NULL)
            return NULL;

        if (equal(node->rank, name))
            return node;

        treenode *found = findNodeRank(name, node->left);

        if (found != NULL)
            return found;

        return findNodeRank(name, node->right);
    }


    void Tree::DeleteNodeAndChildrean(treenode *node) {
        if (node == NULL)
            return;

        DeleteNodeAndChildrean(node->left);
        DeleteNodeAndChildrean(node->right);


        if (node != NULL) {

            node->left = NULL;
            node->right = NULL;
            node->name = "";
            node->rank = "";
            delete node;
        }


    }

    Tree &Tree::addFather(string child, string father) {

        addFatherRecursive(child, father, root);
        return *this;

    }


    Tree &Tree::addMother(string child, string mother) {

        addMotherRecursive(child, mother, root);
        return *this;
    }

    string Tree::relation(string name) {

        string s = "unrelated";
        if (equal(root->name, name))
            return root->rank;

        treenode *node = findNodeName(name, root);
        if (node != NULL && equal(node->name, name))
            return node->rank;
        else
            return s;
    }


    void Tree::remove(string name) {
        treenode *node = findNodeName(name, root);

        DeleteNodeAndChildrean(node);

    }

    string Tree::find(string name) {
        treenode *node = findNodeRank(name, root);
        if (node==NULL) throw invalid_argument("no relation");
        return node->name;

    }

    void Tree::printpostorderprivate(treenode *ptr) {
        if (ptr != NULL) {
            if (ptr->left != NULL) {
                printpostorderprivate(ptr->left);
            }
            cout << ptr->name << " ";

            if (ptr->right != NULL) {
                printpostorderprivate(ptr->right);
            }

        } else
            cout << "emty" << " ";
    }

    void Tree::printPostorder() {

        printpostorderprivate(root);

    }
};
