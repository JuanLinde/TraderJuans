#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include"menu.h"
#include "AVLTree.h"
#include "MaxHeap.h"
using namespace std;

int getFilterIndx();
Node* createNode(string, string);

int main(int argc, char* argv[]) {

	char commandArgument = *argv[1];

	if (commandArgument == '1')
	{
		string filterOptions[] = { "None", "Industrials", "Health Care", "IT", "Consumer Discretionary", "Consumer Staples",
								  "Energy", "Financials", "Utilities", "Real Estate", "Telecommunications" };

		string filterBy = filterOptions[getFilterIndx() - 1];

		AVLTree tree;

		string filePath = "Text.txt";
		ifstream data;
		data.open(filePath);
		string line;
		int counter = 0;
		getline(data, line);

		while (data) {

			if (counter != 0)
			{
				Node* companyInfo = createNode(line, filterBy);
				if (companyInfo != nullptr) tree.insert(companyInfo);
				counter++;
			}
			else
			{
				counter++;
			}
			getline(data, line);
		}
		data.close();
		tree.print();
		return 0;
	}
	if (commandArgument == '2') {
		// The following collapsed comments contain data reading code

		//string filterOptions[] = { "None", "Industrials", "Health Care", "IT", "Consumer Discretionary", "Consumer Staples",
		//				  "Energy", "Financials", "Utilities", "Real Estate", "Telecommunications" };
		//string filterBy = filterOptions[getFilterIndx() - 1];
		//string filePath = "Text.txt";
		//ifstream data;
		//data.open(filePath);
		//string line;
		//// Reads the data and inserts it into the heap
		//int counter = 0;
		//getline(data, line);
		//while (data) {
		//	//Skips the first line of the file
		//	if (counter != 0)
		//	{
		//		Node* companyInfo = createNode(line, filterBy);
		//		if (companyInfo != nullptr) 
		//		counter++;
		//	}
		//	else
		//	{
		//		counter++;
		//	}
		//	getline(data, line);
		//}
		//data.close();
		MaxHeap heap;
		Node* node = new Node(1);
		Node* node2 = new Node(2);
		Node* node3 = new Node(3);
		Node* node10 = new Node(10);
		Node* node5 = new Node(5);
		Node* node100 = new Node(100);
		Node* node4 = new Node(4);

		heap.insert(node);
		heap.insert(node2);
		heap.insert(node3);
		heap.insert(node10);
		heap.insert(node5);
		heap.insert(node100);
		heap.insert(node4);
		heap.print();

		return 0;
	}
	else {
		cout << "no arguments" << endl;
		return 0;
	}


}

int getFilterIndx() {
	Menu mainMenu("main");
	int filterResponse;

	do {
		Menu filterMenu("filter");
		filterMenu.printMenu();
		filterResponse = filterMenu.getResponse("filter");
		if (filterResponse == 0) {
			cout << "Goodbye!" << endl;
			return -1;
		}
		else if (filterResponse < 0 || filterResponse > 11) {

			cout << "Invalid input. Try a number between 0 and 11" << endl << endl;
		}
	} while (filterResponse < 0 || filterResponse > 11);

	return filterResponse;
}
Node* createNode(string line, string filterBy) {

	// Set of company's financial indicators
	vector<string> companyProperties;

	// Checks to see if name of company has comma inside
	int firstCommaPos = line.find(',');
	bool nameHasSpaces = (line[firstCommaPos + 1] == '\"');
	string sector = "";
	// Ignores the characters of name with spaces as they might be commas
	if (nameHasSpaces) {
		int secondQuotePos = line.find('\"', firstCommaPos + 2);
		int secondCommaPos = line.find(',', secondQuotePos + 1);
		int thirdCommaPos = line.find(',', secondCommaPos + 1);
		sector = line.substr(secondCommaPos + 1, thirdCommaPos - secondCommaPos - 1);
	}
	else {
		int secondCommaPos = line.find(',', firstCommaPos + 1);
		int thirdCommaPos = line.find(',', secondCommaPos + 1);
		sector = line.substr(secondCommaPos + 1, thirdCommaPos - secondCommaPos - 1);
	}

	// Creates node only if sector is the correct one
	if (sector == filterBy || filterBy == "None") {
		while (line.size() != 0) {

			//Names with spaces might have commas in them
			if (nameHasSpaces) 
			{
				int firstQuotePos = line.find('\"');
				int secondQuotePos = line.find('\"', firstQuotePos + 1);
				size_t commaPosition = line.find(',');
				bool commaFound = (commaPosition != std::string::npos);

				// Ignores commas in between the quotes of the name
				if (commaFound && (commaPosition < firstQuotePos || 
					commaPosition > secondQuotePos)) 
				{
					string property = line.substr(0, commaPosition);
					companyProperties.push_back(property);
					line.erase(0, commaPosition + 1);
				}
				else {
					// Erases the name of the company with quotes after pushing it to vector
					string property = line.substr(firstQuotePos + 1, secondQuotePos);
					companyProperties.push_back(property);
					line.erase(firstQuotePos, secondQuotePos + 2);
					nameHasSpaces = false;
				}
			}
			else 
			{
				size_t commaPosition = line.find(',');
				bool commaFound = (commaPosition != std::string::npos);
				if (!commaFound) line.clear();
				else
				{
					string property = line.substr(0, commaPosition);
					companyProperties.push_back(property);
					line.erase(0, commaPosition + 1);
				}
			}
		}

		Node* companyNode = new Node(companyProperties);
		return companyNode;
	}
	else return nullptr;
}