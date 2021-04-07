#pragma once
#include "Node.h"
#include <vector>

class MaxHeap
{
private:
	std::vector<Node*> heap; 
	int numOfElements;
	void heapifyUp();
	bool compareNodes(Node*, Node*);

public:
	MaxHeap() { numOfElements = 0; }
	void insert(Node*);
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
	int leftPriceEarnings = stoi(l->getPriceEarnings());
	int rightPriceEarnings = stoi(r->getPriceEarnings());
	if (leftPriceEarnings > rightPriceEarnings) return true;
	else return false;
}

void MaxHeap::print() 
{
	for (auto node : heap) 
	{
		std::cout << node->getPriceEarnings() << ", ";
	}
	std::cout << std::endl;
}