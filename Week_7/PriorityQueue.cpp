/*
    * File:   FibHeap.hpp
    Offline 7
    Implementing Fibonacci Heap
    Aurthor: Mosharaf Hossain Apurbo
    CSE, 2nd Year, BUET
    Roll : 2105057
*/

#include <bits/stdc++.h>
#include "FibHeap.cpp"
using namespace std;

class priorityQueue
{

public:
    FibonacciHeap *make_heap();
    bool is_empty(FibonacciHeap *heap);
    void insert(FibonacciHeap *heap, int key, int value);
    int extract_max(FibonacciHeap *heap);
    void increase_key(FibonacciHeap *heap, int value, int new_key);
    void delete_key(FibonacciHeap *heap, int value);
    FibonacciHeap *meld(FibonacciHeap *heap1, FibonacciHeap *heap2);
    int find_max(FibonacciHeap *heap);
    void print(FibonacciHeap *heap);
    void test();
};

FibonacciHeap *priorityQueue::make_heap()
{
    FibonacciHeap *heap = new FibonacciHeap();

    return heap;
}

bool priorityQueue::is_empty(FibonacciHeap *heap)
{
    return heap->isEmpty();
}

void priorityQueue::insert(FibonacciHeap *heap, int key, int value)
{
    heap->insert(key, value);
}

int priorityQueue::extract_max(FibonacciHeap *heap)
{
    Node *extracted = heap->extractmax();
    if (extracted == NULL)
    {
        cout << "Heap is empty" << endl;
    }
    return extracted->key;
}


void priorityQueue::increase_key(FibonacciHeap *heap, int value, int new_key)
{
    heap->increase(value, new_key);
}

void priorityQueue::delete_key(FibonacciHeap *heap, int value)
{
    heap->deleteNode(value);
}

FibonacciHeap *priorityQueue::meld(FibonacciHeap *heap1, FibonacciHeap *heap2)
{

    return heap1->meld(heap2);
}

int priorityQueue::find_max(FibonacciHeap *heap)
{
    if (heap->maximum() != NULL)
    {
        return heap->maximum()->key;
    }
    else
    {
        cout << "Heap is empty" << endl;
        return -1;
    }
}

void priorityQueue::print(FibonacciHeap *heap)
{
    heap->print();
}

void priorityQueue::test()
{
    
    priorityQueue pq;
    FibonacciHeap *heap = pq.make_heap();

    
    assert(pq.is_empty(heap) == true);

    
    pq.insert(heap, 5, 50);
    pq.insert(heap, 3, 30);
    pq.insert(heap, 7, 70);
    pq.insert(heap, 2, 20);
    pq.insert(heap, 4, 40);

    cout<<"Heap 1: after insert operation"<<endl;
    pq.print(heap);

    
    assert(pq.is_empty(heap) == false);

    
    assert(pq.find_max(heap) == 7);

   
    assert(pq.extract_max(heap) == 7);

    cout<<"Heap 1: after extract max operation"<<endl;
    pq.print(heap);

    
    assert(pq.find_max(heap) == 5);

    
    pq.increase_key(heap, 20, 12);
    assert(pq.find_max(heap) == 12);

    cout<<"Heap 1: after increase key operation"<<endl;
    pq.print(heap);


    
    pq.delete_key(heap, 20);

    cout<<"Heap 1: after delete operation"<<endl;
    pq.print(heap);
    assert(pq.find_max(heap) == 5); 

    cout<<"Heap 1: after delete and increase key operation and before meld"<<endl;
    pq.print(heap);
    
    FibonacciHeap *heap2 = pq.make_heap();
    pq.insert(heap2,8, 80);
    pq.insert(heap2,1, 10);
    pq.insert(heap2,6, 60);
    pq.insert(heap2,9, 90);
    FibonacciHeap *meldedHeap = pq.meld(heap, heap2);
    assert(pq.find_max(meldedHeap) == 9); 

    cout<<"Heap after meld operation"<<endl;
    pq.print(heap);

    cout<<"Heap 2: after meld operation"<<endl;
    pq.print(heap2);

    
    cout << "All test cases passed!" << endl;
}

int main()
{
    priorityQueue pq;
    pq.test();
    return 0;
}
