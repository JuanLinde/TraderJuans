#pragma once
#include<vector>

class Node {
public:
	std::string priceEarningsRatio;
	std::string symbol;
	std::string sector;

	Node* left, *right;

	Node(std::vector<std::string>);
	Node(int pe) { priceEarningsRatio = std::to_string(pe); }
	std::string getPriceEarnings() { return priceEarningsRatio; }
	std::string getSymbol() { return symbol; }
	std::string getSector() { return sector; }
	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	void setLeft(Node* n) { left = n; }
	void setRight(Node* n) { right = n; }
};

Node::Node(std::vector<std::string> v) {
	symbol = v[0];
	sector = v[1];
	priceEarningsRatio = v[2];
	left = nullptr;
	right = nullptr;
}