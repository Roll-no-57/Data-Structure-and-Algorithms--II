// Offline 5
// Red Black Tree
//  Mosharaf Hossain Apurbo
//  Roll : 2105057

// #include "../include/color.hpp"
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
    string name;
};

typedef Node *NodePtr;

class RedBlackTree
{
private:
    NodePtr root;
    NodePtr NILLNode;
    int size;

    //----------------------------------------traversal helper functions----------------------------------------

    // Inorder
    void inOrderHelper(NodePtr node)
    {
        if (node != NILLNode)
        {
            inOrderHelper(node->left);
            cout << node->data << " "
                 << "=>" << node->name << endl;
            inOrderHelper(node->right);
        }
    }

    //----------------------------------------search helper functions----------------------------------------
    NodePtr searchTreeHelper(NodePtr node, int key)
    {
        if (node == NILLNode || key == node->data)
        {
            return node;
        }

        if (key < node->data)
        {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    //----------------------------------------deletion helper functions----------------------------------------

    NodePtr minimum(NodePtr node)
    {
        while (node->left != NILLNode)
        {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != NILLNode)
        {
            node = node->right;
        }
        return node;
    }


    // For balancing the tree after deletion
    void deleteFix(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                //type1
                s = x->parent->right;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                }
                
                //type2
                if (s->left->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    //type3 
                    if (s->right->color == 0)
                    {
                        s->left->color = 0;
                        s->color = 1;
                        rotateRight(s);
                        s = x->parent->right;
                    }
                    //type4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    rotateRight(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == 0)
                    {
                        s->right->color = 0;
                        s->color = 1;
                        rotateLeft(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void transfar(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key)
    {
        NodePtr z = NILLNode;
        NodePtr x, y;
        while (node != NILLNode)
        {
            if (node->data == key)
            {
                z = node;
            }

            if (node->data <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == NILLNode)
        {
            cout << key << " not found" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == NILLNode)
        {
            x = z->right;
            transfar(z, z->right);
        }
        else if (z->right == NILLNode)
        {
            x = z->left;
            transfar(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                transfar(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transfar(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0)
        {
            deleteFix(x);
        }
    }

    //-----------------------------------insertion helper functions-----------------------------------
    void rotateLeft(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != NILLNode)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rotateRight(NodePtr x)
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != NILLNode)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == 1)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rotateRight(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rotateLeft(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        rotateLeft(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rotateRight(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = 0;
    }
    void insertHelper(int key, string nam)
    {
        size++;
        NodePtr node = new Node;
        node->name = nam;
        node->parent = nullptr;
        node->data = key;
        node->left = NILLNode;
        node->right = NILLNode;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != NILLNode)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->left;
            }
            else if (node->data > x->data)
            {
                x = x->right;
            }
            else
            {
                // when the key is already in the tree
                deleteNode(key);
            }
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        insertFix(node);
    }

    //-----------------------------------clearAll helper functions-----------------------------------
    void deleteSubtree(NodePtr node)
    {

        if (node == NILLNode)
        {
            return;
        }

        deleteSubtree(node->left);
        deleteSubtree(node->right);

        delete node;
    }
    //-----------------------------------printing helper functions-----------------------------------
    string preorderString(NodePtr root)
    {

        if (root == NILLNode)
        {
            return "";
        }

        string colourNode = root->color ? "R" : "B";

        string result;
        if(colourNode == "R"){
            // colourNode = "\033[1;31m" + colourNode + "\033[0m";
             result ="\033[1;31m"+ to_string(root->data) + "_" + root->name + "\033[0m";
        }else{
            // colourNode = "\033[1;34m" + colourNode + "\033[0m";
             result =to_string(root->data) + "_" + root->name ;

        }
        

        if (root->left == NILLNode && root->right == NILLNode)
        {
            return result;
        }

        return result + "(" + preorderString(root->left) + "," + preorderString(root->right) + ")";
    }

    void printHelper(NodePtr root)
    {
        cout << preorderString(root) << endl;
    }

public:
    RedBlackTree()
    {
        NILLNode = new Node;
        NILLNode->color = 0;
        NILLNode->left = nullptr;
        NILLNode->right = nullptr;
        root = NILLNode;
        size = 0;
    }
    //---1
    // will return the size of the tree
    int getSize()
    {
        return size;
    }

    //---2
    // will return true if the tree is empty
    void isEmpty()
    {
        cout << (getSize() == 0 ? "yes" : "no") << endl;
    }

    //---3
    // will iterate through the tree and print the nodes in ascending order
    void inorder()
    {
        inOrderHelper(this->root);
    }

    //---4
    // will search for a node in the tree
    void searchTree(int k)
    {

        NodePtr temp = searchTreeHelper(this->root, k);

        if (temp == NILLNode)
        {
            cout << k << " not found" << endl;
        }
        else
        {
            cout << temp->data << " "
                 << "found" << endl;
        }
    }

    //---5
    // Inserting a node
    void insert(int key, string name)
    {
        insertHelper(key, name);
    }

    //---6
    void deleteNode(int data)
    {
        size--;

        deleteNodeHelper(this->root, data);
    }

    //---7
    // will clear the tree
    void clearAll()
    {

        if (getSize() == 0)
        {
            cout << "Unsuccessful" << endl;
        }
        else
        {
            cout << "Successful" << endl;
            deleteSubtree(root);
            root = NILLNode;
            size = 0;
        }
    }

    // will print the tree in preorder
    void printTree()
    {
        if (root)
        {
            printHelper(this->root);
        }
    }
};

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    RedBlackTree bst;

    while (true)
    {
        string command;
        cin >> command;

        if (command == "I")
        {
            int key;
            string name;
            cin >> key >> name;
            bst.insert(key, name);
            bst.printTree();
        }
        else if (command == "E")
        {
            int key;
            cin >> key;
            bst.deleteNode(key);
            bst.printTree();
        }
        else if (command == "F")
        {
            int key;
            cin >> key;
            bst.searchTree(key);
        }
        else if (command == "Itr")
        {
            bst.inorder();
        }
        else if (command == "S")
        {
            cout << bst.getSize() << endl;
        }
        else if (command == "Em")
        {
            bst.isEmpty();
        }
        else if (command == "Clr")
        {
            bst.clearAll();
        }
        else if (command == "END")
        {
            break;
        }
    }
}
