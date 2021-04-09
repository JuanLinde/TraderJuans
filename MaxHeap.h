#pragma once
#include "Node.h"
#include <vector>

class MaxHeap
{
private:
    std::vector<Node*> heap; 
    int numOfElements;
    void heapifyUp();
    void heapifyDown();
    bool compareNodes(Node*, Node*);

public:
    MaxHeap() { numOfElements = 0; }
    void insert(Node*);
    void sortAndDisplay();
    void print();
};

void MaxHeap::insert(Node* n) 
{
    bool heapIsEmpty = (numOfElements == 0);

    if (heapIsEmpty) 
    {
        heap.push_back(n);
        numOfElements++;
    }
    else 
    {
        heap.push_back(n);
        numOfElements++;
        heapifyUp();
        
    }
}

void MaxHeap::heapifyUp() 
{
    int nodeToHeapifyIndx = numOfElements - 1;
    Node* nodeToHeapify = heap[nodeToHeapifyIndx];
    int parentIndx = (nodeToHeapifyIndx - 1) / 2;
    Node* parent = heap[parentIndx];

    bool nodeToHeapifyIsGreaterThanParent = compareNodes(nodeToHeapify, parent);
    bool nodeToHeapifyIsNotRoot = (nodeToHeapifyIndx != 0);
    
    while (nodeToHeapifyIsGreaterThanParent && nodeToHeapifyIsNotRoot) 
    {
        std::swap(heap[nodeToHeapifyIndx], heap[parentIndx]);
        nodeToHeapifyIndx = parentIndx;
        parentIndx = (nodeToHeapifyIndx - 1) / 2;
        nodeToHeapify = heap[nodeToHeapifyIndx];
        if (parentIndx >= 0) parent = heap[parentIndx];
        nodeToHeapifyIsGreaterThanParent = compareNodes(nodeToHeapify, parent);
        nodeToHeapifyIsNotRoot = (nodeToHeapifyIndx != 0);
    }
    
}

bool MaxHeap::compareNodes(Node* l, Node* r) 
{
    float leftPriceEarnings = stof(l->getPriceEarnings());
    float rightPriceEarnings = stof(r->getPriceEarnings());
    if (leftPriceEarnings > rightPriceEarnings) return true;
    else return false;
}

void MaxHeap::sortAndDisplay()
{
    
    int counter = 0;
    while (numOfElements != 0)
    {
        // Displays the info of the current largest tuple
        std::cout << (++counter) << ": " << heap[0]->symbol << ": " << heap[0]->sector << ": " <<
            heap[0]->getPriceEarnings() << std::endl;

        // Updates first element in the heap
        int lastIndx = heap.size() - 1;
        Node* lastElement = heap[lastIndx];
        heap[0] = lastElement;
        heap.pop_back();
        numOfElements--;

        // Performs heapify down
        heapifyDown();
    }
}

void MaxHeap::heapifyDown()
{
    // Initializes indices and starting conditions
    int heapSize = heap.size();
    if (heapSize == 0) return;

    int parentPos = 0;
    int leftChildPos = 2 * parentPos + 1;
    int rightChildPos = 2 * parentPos + 2;
    Node* parent = heap[parentPos];
    Node* leftChild = nullptr;
    Node* rightChild = nullptr;
    bool parentHasNoLeftChild;
    bool parentHasNoRightChild;
    bool parentGreaterThanLeftChild;
    bool parentGreaterThanRightChild;
    bool parentIsGreaterThanChildren = false;
    bool nodeIsLeaf = false;

    do 
    {
        // Current parent has two children
        if (leftChildPos < heapSize && rightChildPos < heapSize) {

            leftChild = heap[leftChildPos];
            rightChild = heap[rightChildPos];

            parentGreaterThanLeftChild = compareNodes(parent, leftChild);
            parentGreaterThanRightChild = compareNodes(parent, rightChild);
            parentIsGreaterThanChildren = (parentGreaterThanLeftChild &&
                parentGreaterThanRightChild);
            
            if (parentIsGreaterThanChildren) break;

            else 
            {
                bool leftChildIsLarger = compareNodes(leftChild, rightChild);
                if (leftChildIsLarger) 
                {
                    // Swap parent with left child and update
                    std::swap(heap[parentPos], heap[leftChildPos]); 
                    parentPos = leftChildPos;
                    leftChildPos = 2 * parentPos + 1;
                    rightChildPos = 2 * parentPos + 2;
                    parent = heap[parentPos];
                }
                else 
                {
                    // Swap parent with right child and update
                    std::swap(heap[parentPos], heap[rightChildPos]);
                    parentPos = rightChildPos;
                    leftChildPos = 2 * parentPos + 1;
                    rightChildPos = 2 * parentPos + 2;
                    parent = heap[parentPos];
                }
            }
        }
        // Current parent is not leaf and has one child to left
        else if (leftChildPos < heapSize && rightChildPos >= heapSize) 
        {
            leftChild = heap[leftChildPos];
            parentGreaterThanLeftChild = compareNodes(parent, leftChild);
            if (parentGreaterThanLeftChild) break;
            else 
            {
                // Swap parent with left child and update
                std::swap(heap[parentPos], heap[leftChildPos]);
                parentPos = leftChildPos;
                leftChildPos = 2 * parentPos + 1;
                rightChildPos = 2 * parentPos + 2;
                parent = heap[parentPos];
            }
        }
        // Current node is leaf
        else nodeIsLeaf = true;
    } while (!parentIsGreaterThanChildren && !nodeIsLeaf);
}

void MaxHeap::print()
{
    for (int i = 0; i < heap.size(); i++)
    {
        std::cout << heap[i]->getPriceEarnings() << ", ";
    }
    std::cout << std::endl;
}