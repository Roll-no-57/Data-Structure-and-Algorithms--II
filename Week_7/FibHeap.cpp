/*
    * File:   FibHeap.hpp
    Offline 7
    Implementing Fibonacci Heap
    Aurthor: Mosharaf Hossain Apurbo
    CSE, 2nd Year, BUET
    Roll : 2105057
*/

#include <bits/stdc++.h>
using namespace std;

// Node structure for Fibonacci Heap
class Node
{
public:
    // values
    int key;
    int degree;
    bool mark;

    // pointers
    Node *parent;
    Node *child;
    Node *left;
    Node *right;

    // constructor
    Node(int key)
    {
        this->key = key;
        degree = 0;
        mark = false;
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
    Node *minNode;

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

                // make sure x is the smaller node
                if (x->key > y->key)
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

        // find the minimum node in the root list
        for (int i = 0; i < maxDegree; i++)
        {
            if (degreeTable[i] != NULL)
            {
                if (degreeTable[i]->key < minNode->key)
                {
                    minNode = degreeTable[i];
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

    // Helper function to find a node with a key
    Node *findNode(Node *node, int key)
    {
        if (node == NULL)
        {
            return NULL;
        }

        if (node->key == key)
        {
            return node;
        }

        // if the node has children, then search the children
        Node *foundNode = findNode(node->child, key);
        if (foundNode != NULL)
        {
            return foundNode;
        }

        // if the node has siblings, then search the siblings
        return findNode(node->right, key);
    }

    // decrease the key of a node

    void decreaseKey(Node *x, int k)
    {
        if (k > x->key)
        {
            cout << "New key is greater than the current key" << endl;
            return;
        }
        x->key = k;
        Node *bap = x->parent;
        if (bap != NULL && x->key < bap->key)
        {
            cut(x, bap);
            cascadingCut(bap);
        }
        if (x->key < minNode->key)
        {
            minNode = x;
        }
    }

public:
    // Make Heap by initializing the values
    FibonacciHeap()
    {
        n = 0;
        root = NULL;
        minNode = NULL;
    }

    // returns the pointer of the minimum node
    Node *minimum()
    {
        return minNode;
    }

    // insert a node into the heap
    void insert(int key)
    {

        Node *newNode = new Node(key);
        // points to itself first beacuse it always added to the root list
        newNode->left = newNode;
        newNode->right = newNode;

        // merge the new node with the root list
        mergeToRootList(newNode);

        // if the new node is smaller than the min node, update the min node
        if (minNode == NULL || newNode->key < minNode->key)
        {
            minNode = newNode;
        }

        // increase the number of nodes
        n++;
    }

    // Meld two fibonacci heap operation
    FibonacciHeap *meld(FibonacciHeap *h2, FibonacciHeap *h1)
    {
        // create a new Heap and set the root of the new Heap to the root of the first Heap
        FibonacciHeap *newHeap = new FibonacciHeap();
        newHeap->root = h1->root;

        // set the minNode of the new node to the minimum of the two heaps
        if ((h1->minNode == NULL) || (h2->minNode != NULL && h2->minNode->key < h1->minNode->key))
        {
            newHeap->minNode = h2->minNode;
        }
        else
        {
            newHeap->minNode = h1->minNode;
        }

        // Merge the root list of the two heaps
        Node *h2Left = h2->root->left;
        h2->root->left = h1->root->left;
        h1->root->left->right = h2->root;
        h2Left->right = h1->root;
        h1->root->left = h2Left;

        // update the number of nodes
        newHeap->n = h1->n + h2->n;

        // return the new heap
        return newHeap;
    }

    // remove the minimum node from the heap
    // extract min consolidates min-heap-ordered trees

    Node *extractMin()
    {
        Node *extractNode = minNode;

        // We can extract the min node if it is not NULL
        if (extractNode != NULL)
        {
            // if the min node has children, add them to the root list
            if (extractNode->child != NULL)
            {

                // extract the children of the min node
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

            // if the min Node is the only node in the root list then set the root to NUll and minNode to Null
            if (extractNode == extractNode->right)
            {
                root = NULL;
                minNode = NULL;
            }
            else
            {
                // set the minNode to the right of the extractNode
                minNode = extractNode->right;
                // consolidate the heap and update the minNode
                consolidate();
            }

            // decrease the number of nodes
            n--;
        }

        return extractNode;
    }

    void decrease(int key, int newKey)
    {
        Node *ptr = findHeap(key);
        decreaseKey(ptr, newKey);
    }

    // delete a node from the heap
    Node *deleteNode(Node *node)
    {
        decreaseKey(node, INT_MIN);
        Node *extracted = extractMin();
        return extracted;
    }

    // find the pointer of a key in the heap
    Node *findHeap(int key)
    {
        return findNode(root, key);
    }

    void printHeap()
    {
        vector<Node *> root;
        iterate(this->root, root);
        for (int i = 0; i < root.size(); i++)
        {
            cout << root[i]->key << "(degree:" << root[i]->degree << ")"
                 << " ";
        }
        cout << endl;
    }

    void print_fibonacci_heap(bool print_marked = false)
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

        cout << "--------------------" << endl;
        cout << "-- Fibonacci Heap --" << endl;
        cout << "--------------------" << endl;
        cout << "Total nodes: " << n << endl;
        cout << "Minimum: " << (minNode->key) << endl;
        cout << "Root list node: " << (root ? root->key : -1) << endl;
        cout << "Root list: ";
        for (int key : root_keys)
        {
            cout << key << " ";
        }
        cout << endl;

        while (!unvisited.empty())
        {
            Node *node = unvisited.front();
            unvisited.pop_front();
            if (node->mark && (find(marked_nodes.begin(), marked_nodes.end(), node->key) == marked_nodes.end()))
            {
                marked_nodes.push_back(node->key);
            }
            Node *child = node->child;
            if (child)
            {
                Node *current_child = child;
                do
                {
                    cout << "Children of " << node->key << ": " << current_child->key << " ";
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
        cout << "--------------------" << endl
             << endl;
    }
};

int main()
{
    FibonacciHeap fh1, fh2;
    fh1.insert(545);
    fh1.insert(345);
    fh1.insert(445);
    fh1.insert(245);
    fh1.insert(145);
    fh1.insert(7);
    fh2.insert(40);
    fh2.insert(50);
    fh2.insert(60);
    fh1.insert(100);
    fh2.insert(200);
    fh2.insert(300);
    fh2.insert(400);
    fh2.insert(500);
    fh2.insert(600);

    cout << "Heap 1:" << endl;
    fh1.printHeap();
    cout << "Heap 2:" << endl;
    fh2.printHeap();

   cout<< fh1.findHeap(100)->key<<endl;
   fh1.decrease(100, 10);
   fh1.printHeap();
   fh1.extractMin();
    fh1.printHeap();
    fh1.decrease(245,1);
    fh1.print_fibonacci_heap();

   // Melding heap fh2 into fh1
    FibonacciHeap *meldedHeap = fh1.meld(&fh2, &fh1);

    cout << "Melded Heap:" << endl;
    meldedHeap->printHeap();

    // Extracting minimum from melded heap
    Node *min = meldedHeap->minimum();
    cout << "Minimum value in the melded heap: " << min->key << endl;

    Node *extracted_min = meldedHeap->extractMin();
    cout << "Extracted minimum value: " << extracted_min->key << endl;

    cout << "Heap after extraction:" << endl;
    meldedHeap->print_fibonacci_heap();

    delete meldedHeap;

    return 0;
}
