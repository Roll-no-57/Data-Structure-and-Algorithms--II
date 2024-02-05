
#include <bits/stdc++.h>
using namespace std;

// Node structure for Fibonacci Heap
class Node
{
public:
    // values
    int key;
    int value;
    int degree;
    bool mark;
    char vis;

    // pointers
    Node *parent;
    Node *child;
    Node *left;
    Node *right;

    // constructor
    Node(int key, int value)
    {
        this->key = key;
        this->value = value;
        degree = 0;
        mark = false;
        vis = 'N';
        parent = NULL;
        child = NULL;
        left = this;
        right = this;
    }
};

// Fibonacci Heap class
class FibonacciHeap
{
private:
    // number of nodes in the heap
    int n;
    // pointer of the root list
    Node *root;
    // pointer of the min node
    Node *maxNode;

    // Helper function to merge the new node with the root list
    void mergeToRootList(Node *newNode)
    {

        if (root == NULL)
        {
            root = newNode;
        }
        else
        {
            newNode->right = root;
            newNode->left = root->left;
            root->left->right = newNode;
            root->left = newNode;
        }
    }

    // Helper function to iterate through the children of a node
    void iterate(Node *node, vector<Node *> &children)
    {
        Node *temp = node;
        if (temp == NULL)
        {
            return;
        }
        do
        {
            children.push_back(temp);
            temp = temp->right;
        } while (temp != node);
    }

    // Helper function to remove a node from the root list
    void removeNodeFromRootList(Node *node)
    {
        if (node == root)
        {
            root = node->right;
        }

        node->left->right = node->right;
        node->right->left = node->left;
    }

    // Helper function to consolidate the heap
    void consolidate()
    {
        // calculate the maximum degree of the root list nodes
        int maxDegree = (int)ceil(log2(n)) + 1;

        vector<Node *> degreeTable(maxDegree, NULL);
        vector<Node *> rootNodes;

        // iterate through the root list
        iterate(root, rootNodes);

        for (int i = 0; i < rootNodes.size(); i++)
        {
            Node *x = rootNodes[i];
            int d = x->degree;

            // if there is another node with the same degree, then merge them
            // until there is no other node with the same degree--important
            while (degreeTable[d] != NULL)
            {
                Node *y = degreeTable[d];

                // make sure x is the greater node
                if (x->key < y->key)
                {
                    Node *temp = x;
                    x = y;
                    y = temp;
                }

                // link between x and y where x is the parent and y is child
                HeapLink(y, x);
                degreeTable[d] = NULL;
                d++;
            }
            degreeTable[d] = x;
        }

        // find the Maximum node in the root list
        for (int i = 0; i < maxDegree; i++)
        {
            if (degreeTable[i] != NULL)
            {
                if (degreeTable[i]->key > maxNode->key)
                {
                    maxNode = degreeTable[i];
                }
            }
        }

        // at the end no need to reconstruct the root list as the root list is already constructed
        // when we linking the nodes in the HeapLink function we are actually removing the nodes from the root list
        // so it doesn't affect the root list
    }

    // Helper function to link two nodes in the heap
    void HeapLink(Node *y, Node *x)
    {
        // remove y from the root list
        removeNodeFromRootList(y);
        y->left = y->right = y;

        // merge y with the child list of x
        mergeToChildList(x, y);

        // set parent of y to x;
        y->parent = x;
        x->degree++;
        y->mark = false;
    }

    // Helper function to merge a node with the child list of another node
    void mergeToChildList(Node *bap, Node *put)
    {
        if (bap->child == NULL)
        {
            bap->child = put;
        }
        else
        {
            put->right = bap->child->right;
            put->left = bap->child;
            bap->child->right->left = put;
            bap->child->right = put;
        }
    }

    // Helper function to cut a node from its parent
    void cut(Node *put, Node *bap)
    {
        removeNodeFromChildList(bap, put);
        bap->degree--;
        mergeToRootList(put);
        put->parent = NULL;
        put->mark = false;
    }

    // Helper function to remove a node from the child list of another node
    void removeNodeFromChildList(Node *bap, Node *put)
    {
        if (bap->child == bap->child->right)
        {
            bap->child = NULL;
        }
        else if (bap->child == put)
        {
            bap->child = put->right;
            put->right->parent = bap;
        }
        put->left->right = put->right;
        put->right->left = put->left;
    }

    // Helper function to perform cascading cut
    void cascadingCut(Node *y)
    {
        Node *bap = y->parent;
        if (bap != NULL)
        {
            if (y->mark == false)
            {
                y->mark = true;
            }
            else
            {
                cut(y, bap);
                cascadingCut(bap);
            }
        }
    }

    Node *findNode(Node *root, int k)
    {
        Node *x = root;
        x->vis = 'Y';
        Node *p = NULL;

        if (x->value == k)
        {
            p = x;
            x->vis = 'N';
            return p;
        }

        if (p == NULL)
        {
            if (x->child != NULL)
                p = findNode(x->child, k);
            if ((x->right)->vis != 'Y')
                p = findNode(x->right, k);
        }

        x->vis = 'N';
        return p;
    }

    // decrease the key of a node

    void increaseKey(Node *x, int k)
    {
        if (k < x->key)
        {
            cout << "New key is smaller than the current key" << endl;
            return;
        }

        x->key = k;
        Node *bap = x->parent;
        if (bap != NULL && x->key > bap->key)
        {
            cut(x, bap);
            cascadingCut(bap);
        }

        if (x->key > maxNode->key)
        {
            maxNode = x;
        }
    }

public:
    // Make Heap by initializing the values
    FibonacciHeap()
    {
        n = 0;
        root = NULL;
        maxNode = NULL;
    }

    // returns the number of nodes in the heap
    int size()
    {
        return n;
    }

    // return true if the heap is empty
    bool isEmpty()
    {
        return root == NULL;
    }

    // returns the pointer of the maximum node
    Node *maximum()
    {
        return maxNode;
    }

    // insert a node into the heap
    void insert(int key, int value)
    {

        Node *newNode = new Node(key, value);
        // points to itself first beacuse it always added to the root list
        newNode->left = newNode;
        newNode->right = newNode;

        // merge the new node with the root list
        mergeToRootList(newNode);

        // if the new node is smaller than the min node, update the min node
        if (maxNode == NULL || newNode->key > maxNode->key)
        {
            maxNode = newNode;
        }

        // increase the number of nodes
        n++;
    }

    // Meld two fibonacci heap operation
    FibonacciHeap *meld(FibonacciHeap *h2)
    {
        // create a new Heap and set the root of the new Heap to the root of the first Heap
        FibonacciHeap *newHeap = new FibonacciHeap();
        newHeap->root = this->root;

        // set the maxNode of the new node to the maximum of the two heaps
        if ((this->maxNode == NULL) || (h2->maxNode != NULL && h2->maxNode->key > this->maxNode->key))
        {
            newHeap->maxNode = h2->maxNode;
        }
        else
        {
            newHeap->maxNode = this->maxNode;
        }

        // Merge the root list of the two heaps
        Node *h2Left = h2->root->left;
        h2->root->left = this->root->left;
        this->root->left->right = h2->root;
        h2Left->right = this->root;
        this->root->left = h2Left;

        // update the number of nodes
        newHeap->n = this->n + h2->n;

        // return the new heap
        return newHeap;
    }

    // remove the maximum node from the heap
    // extract max consolidates max-heap-ordered trees

    Node *extractmax()
    {
        Node *extractNode = maxNode;

        // We can extract the max node if it is not NULL
        if (extractNode != NULL)
        {
            // if the max node has children, add them to the root list
            if (extractNode->child != NULL)
            {

                // extract the children of the max node
                vector<Node *> children;
                iterate(extractNode->child, children);

                // merge all children with the root list
                for (int i = 0; i < children.size(); i++)
                {
                    mergeToRootList(children[i]);
                    children[i]->parent = NULL;
                }
            }

            removeNodeFromRootList(extractNode);

            // if the max Node is the only node in the root list then set the root to NUll and maxNode to Null
            if (extractNode == extractNode->right)
            {
                root = NULL;
                maxNode = NULL;
            }
            else
            {
                // set the maxNode to the right of the extractNode
                maxNode = extractNode->right;
                // consolidate the heap and update the maxNode
                consolidate();
            }

            // decrease the number of nodes
            n--;
        }

        return extractNode;
    }

    void increase(int value, int newKey)
    {

        Node *ptr = findHeap(value);
        if (ptr != NULL)
            increaseKey(ptr, newKey);
    }


    //deletes the node
    void deleteNode(int value)
    {
        Node *ptr = findHeap(value);
        if (ptr != NULL)
        {
            increaseKey(ptr, INT_MAX);
            Node *extracted = extractmax();
        }
    }

    // find the pointer of a key in the heap
    Node *findHeap(int value)
    {
        // cout << "key : " << root->key << endl;
        if (findNode(root, value) == NULL)
        {
            cout << "value not found" << endl;
            return NULL;
        }
        return findNode(root, value);
    }

    // print the heap

    void print(bool print_marked = false)
    {
        deque<Node *> unvisited;
        vector<int> root_keys;
        vector<int> marked_nodes;

        if (root)
        {
            Node *current = root;
            do
            {
                root_keys.push_back(current->key);
                unvisited.push_back(current);
                current = current->right;
            } while (current != root);
        }

        int rootKeyIndex =0;

        while (!unvisited.empty())
        {
            Node *node = unvisited.front();

            if(node->key==root_keys[rootKeyIndex]){
                cout << "Tree " << ++rootKeyIndex<<": " << endl;
            }

            unvisited.pop_front();
            if (node->mark && (find(marked_nodes.begin(), marked_nodes.end(), node->key) == marked_nodes.end()))
            {
                marked_nodes.push_back(node->key);
            }
            Node *child = node->child;
            cout<<"       ("<<node->key<<","<<node->value<<")-->";
            if (child)
            {
                Node *current_child = child;
                do
                {
                    // cout << "Children of " << node->key << ": " << current_child->key << " ";
                    cout<<"   ("<<current_child->key<<","<<current_child->value<<")";
                    if (current_child->child)
                    {
                        unvisited.push_back(current_child);
                    }
                    if (current_child->mark && (find(marked_nodes.begin(), marked_nodes.end(), current_child->key) == marked_nodes.end()))
                    {
                        marked_nodes.push_back(current_child->key);
                    }
                    current_child = current_child->right;
                } while (current_child != child);
                cout << endl;
            }
            else
            {
                cout<<endl;
            }
        }
        if (print_marked)
        {
            cout << "Marked nodes: ";
            for (int key : marked_nodes)
            {
                cout << key << " ";
            }
            cout << endl;
        }
        cout<<endl;
    }
};

