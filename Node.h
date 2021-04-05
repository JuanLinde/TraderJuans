#pragma once
#include<vector>

class Node {
public:
	std::string symbol;
	std::string name;
	std::string sector;
	std::string price;
	std::string priceEarningsRatio;
	std::string dividendYield;
	std::string earningsShareRatio;
	std::string weekLow52;
	std::string weekHigh52;
	std::string marketCap;
	std::string ebitda;

	Node* left, *right;

	Node(std::vector<std::string>);
};

Node::Node(std::vector<std::string> v) {
	symbol = v[0];
	name = v[1];
	sector = v[2];
	price = v[3];
	priceEarningsRatio = v[4];
	dividendYield = v[5];
	earningsShareRatio = v[6];
	weekLow52 = v[7];
	weekHigh52 = v[8];
	marketCap = v[9];
	ebitda = v[10];
	left = nullptr;
	right = nullptr;
}