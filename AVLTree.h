#pragma once
#include"Node.h"
#include <string>
#include <queue>
#include <iostream>
class AVLTree 
{

private:

	Node* root;
	int numOfNodes;
	Node* insertHelper(Node* nodeStart, Node* nodeInsert);
	int getBalanceFactor(Node*);
	int getHeight(Node*);
	bool isBalancefactorValid(int);
	int checkCase(Node*);
	Node* rotateRight(Node*);
	Node* rotateLeft(Node*);
	Node* rotateLeftRight(Node*);
	Node* rotateRightLeft(Node*);
	void printInOrder(Node*);


public:

	AVLTree() { root = nullptr; numOfNodes = 0;}
	void insert(Node*);
	void print();
	

};

/*
	Input:		nodeStart  - node from which to insert the new node, usually the root
				nodeInsert - pointer to node to insert into the tree

	Output:		void

	Comments:   The function inserts, using a helper function, a node into the tree in BST order. It also makes sure
				that the tree remains balanced following the AVL tree conventions. The function
				makes sure that the ID and Name in nodeInsert are valid before doing the insertion.
				If the insertion fails, 'unsuccessful' is printed. If it succeeds, 'successful' is
				printed.
*/
void AVLTree::insert(Node* nodeInsert) 
{
	insertHelper(root, nodeInsert);
	numOfNodes++;
}

// Insert helper function to avoid recursion in the isIDValid part
// Inserts nodeInsert recursively into the tree. If the function is
// called, the insert values are valid.
Node* AVLTree::insertHelper(Node* nodeStart, Node* nodeInsert) 
{
	// If tree is empty, create root
	if (root == nullptr) {
		root = nodeInsert;
	}
	// If tree is not empty, recursively find the spot to insert node
	else {
		// Base case for recursion, which means the spot is found
		if (nodeStart == nullptr) {
			// Create node to insert
			return nodeInsert;
		}
		else {
			// If key is less than current node's key, insert to the left recursively
			if (stoi(nodeInsert->getPriceEarnings()) <= stoi(nodeStart->getPriceEarnings())) {

				nodeStart->setLeft(insertHelper(nodeStart->getLeft(), nodeInsert));

				int balanceFactor = getBalanceFactor(nodeStart);


				if (!isBalancefactorValid(balanceFactor)) {
					// Checks for the type of case for rotation
					int kse = checkCase(nodeStart);
					// kse = 0 -> left left case -> right rotation
					if (kse == 0) {
						if (nodeStart == root) {
							root = rotateRight(nodeStart);
						}
						else return rotateRight(nodeStart);
					}
					// kse = 1 -> left right case -> left right rotation
					else if (kse == 1) {
						if (nodeStart == root) {
							root = rotateLeftRight(nodeStart);
						}
						else return rotateLeftRight(nodeStart);
					}
				}
				else {
					return nodeStart;
				}
			}
			// If key is greater than current node's key, insert to the right recursively
			else {
				nodeStart->setRight(insertHelper(nodeStart->getRight(), nodeInsert));

				int balanceFactor = getBalanceFactor(nodeStart);


				if (!isBalancefactorValid(balanceFactor)) {
					// Checks for the type of case for rotation
					int kse = checkCase(nodeStart);

					// kse = 2 -> right right case -> left rotation
					if (kse == 2) {
						if (nodeStart == root) {
							root = rotateLeft(nodeStart);
						}
						else return rotateLeft(nodeStart);
					}
					// kse = 3 -> right left case -> right left rotation
					else if (kse == 3) {
						if (nodeStart == root) {
							root = rotateRightLeft(nodeStart);
						}
						else return rotateRightLeft(nodeStart);
					}
				}
				else {
					return nodeStart;
				}
			}
		}
	}
}

/*
	Inputs: Node - Pointer to the node whose balance factor is needed

	Output: int - The balance factor of the current node

	Comments:	This function calls the getHeight() function for the left
				and right subtree and gets the balance factor of the node
				based on those heights.

*/
int AVLTree::getBalanceFactor(Node* node) {

	int heightLeftSubtree = 0;
	int heightRightSubtree = 0;
	int balanceFactor = 0;

	if (node == nullptr) return -1;
	// Leaf nodes have balance factor of 0
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return 0;

	}
	else if (node->getRight() == nullptr && node->getLeft() != nullptr) {
		heightRightSubtree = 0;
		heightLeftSubtree = getHeight(node->getLeft());
		balanceFactor = heightLeftSubtree - heightRightSubtree;
		return balanceFactor;
	}
	else if (node->getRight() != nullptr && node->getLeft() == nullptr) {
		heightRightSubtree = getHeight(node->getRight());
		heightLeftSubtree = 0;
		balanceFactor = heightLeftSubtree - heightRightSubtree;
		return balanceFactor;
	}
	else {
		heightRightSubtree = getHeight(node->getRight());
		heightLeftSubtree = getHeight(node->getLeft());
		balanceFactor = heightLeftSubtree - heightRightSubtree;
		return balanceFactor;
	}
}

/*
	Inputs: Node - pointer from which to start calculating height

	Ouput:	int  - The height of the tree from the passed node

	Comments:	This function calculates the height of a tree from the
				passed node. It does so by recursively calling itself.
*/
int AVLTree::getHeight(Node* node) {

	if (node == nullptr) {
		return 0;
	}
	else {
		Node* nodeToLeft = node->getLeft();
		Node* nodeToRight = node->getRight();
		return 1 + std::max(getHeight(nodeToLeft), getHeight(nodeToRight));
	}
}

/*
	inputs: balanceFactor - The balance factor of the node under consideration

	outputs: bool         - If balance factor < -1 or > 1 returns false

*/
bool AVLTree::isBalancefactorValid(int bf) {
	if (bf < -1 || bf > 1) return false;
	else return true;
}

/*
	input:	nodeOutOfBalance - Node on which to check the case

	output:	int - 0 -> left left case
				  1 -> left right case
				  2 -> right right case
				  3 -> right left case
*/
int AVLTree::checkCase(Node* nodeOutOfBalance) {
	int balanceFactorPrimaryNode = getBalanceFactor(nodeOutOfBalance);
	int BFPrimaryNodeLeftChild = getBalanceFactor(nodeOutOfBalance->getLeft());
	int BFPrimaryNodeRightChild = getBalanceFactor(nodeOutOfBalance->getRight());

	//Checks left left case
	if (balanceFactorPrimaryNode == 2 && BFPrimaryNodeLeftChild == 1) return 0;
	// Checks left right case
	else if (balanceFactorPrimaryNode == 2 && BFPrimaryNodeLeftChild == -1) return 1;
	// Checks right right case
	else if (balanceFactorPrimaryNode == -2 && BFPrimaryNodeRightChild == -1) return 2;
	// Checks right left case
	else if (balanceFactorPrimaryNode == -2 && BFPrimaryNodeRightChild == 1) return 3;
	// For completeness
	else return -1;

}

/*
	Inputs:	node - pointer from which the rotation starts

	Output: node* - pointer to the new 'root' of rotated subtree

*/
Node* AVLTree::rotateRightLeft(Node* node) {
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	else {
		node->setRight(rotateRight(node->getRight()));
		Node* newParent = rotateLeft(node);
		return newParent;
	}
}

/*
	Inputs:	node - Pointer from the node where the rotation starts

	Output: node* - Pointer to the new 'root' of the rotated subtree

*/
Node* AVLTree::rotateLeftRight(Node* node) {
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	else {
		node->setLeft(rotateLeft(node->getLeft()));
		Node* newParent = rotateRight(node);
		return newParent;
	}
}

/*
	Inputs:	node - Node from which the rotation starts

	Output: node* - Node pointer to the new 'root' of the rotated subtree

*/
Node* AVLTree::rotateLeft(Node* node) {
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	else {
		Node* newParent = node->getRight();
		Node* newParentOldLeft = newParent->getLeft();
		newParent->setLeft(node);
		node->setRight(newParentOldLeft);
		return newParent;
	}
}

/*
	Inputs:	node - pointer from where to start the rotation to the right

	Outputs: Node* - pointer to the new 'root' after rotation

*/
Node* AVLTree::rotateRight(Node* node) {

	// If passed node has no children, return passed node
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return node;
	}
	// If passed node has one children to the left
	else {
		Node* newParent = node->getLeft();
		Node* newParentOldRight = newParent->getRight();
		newParent->setRight(node);
		node->setLeft(newParentOldRight);
		return newParent;
	}
}

// Prints an inorder version of the tree recursively. 
// The values are separated by commas
void AVLTree::printInOrder(Node* node) {

	static int nodesTraversed = 0;

	if (root == nullptr) {
		std::cout << "Tree is empty" << std::endl;
	}
	//Base case for recursion
	else if (node == nullptr) {
		return;
	}
	else {
		// Visit left
		printInOrder(node->getLeft());
		// Ending hasn't been reached: print comma
		if (nodesTraversed + 1 != numOfNodes) {
			std::cout << "( " << node->getSymbol() << ":" << node->getSector() << ":" << 
				node->getPriceEarnings() << " )" << ", ";
				
			nodesTraversed++;

		}
		// End reached: do not print comma
		else {
			std::cout << "( " << node->getSymbol() << ":" << node->getSector() << ":" <<
				node->getPriceEarnings() << " )" << std::endl;
			nodesTraversed++;
		}
		// Visit Right
		printInOrder(node->getRight());
		// Resets static variable to zero for subsequent function calls
		if (nodesTraversed >= numOfNodes) nodesTraversed = 0;
	}
}

void AVLTree::print() {
	printInOrder(root);
}



