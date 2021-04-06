#pragma once
#include"Node.h"
#include <string>
#include <queue>
#include <iostream>
class AVLTree {

private:

	Node* root;
	int numOfNodes;
	Node* insertHelper(Node* nodeStart, Node* nodeInsert);

public:

	AVLTree(int ff) { root = nullptr; numOfNodes = 0;}
	void insert(Node*);

};
