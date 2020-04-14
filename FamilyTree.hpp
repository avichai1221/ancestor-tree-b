#include <iostream>
#include <stdexcept>
using namespace std;


namespace family {

    class Tree {

    private:
        struct treenode {
            string name;
            string rank;
            treenode *left;
            treenode *right;
        };

        treenode *root;

        bool equal(string a, string b);

        void addFatherRecursive(string child, string father, treenode *node);

        void addMotherRecursive(string child, string mother, treenode *node);

        void printpostorderprivate(treenode *node);

        treenode *findNodeName(string name, treenode *node);

        void DeleteNodeAndChildrean(treenode *node);

        treenode *findNodeRank(string name, treenode *node);

    public:
        Tree(string name);

        treenode *creatNode(string name);

        int HighRecursive(string name, treenode *node, int level);

        Tree &addFather(string child, string father);

        Tree &addMother(string child, string mother);

        void printPostorder();

        string relation(string name);

        void remove(string name);

        string find(string name);

    };
};