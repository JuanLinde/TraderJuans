#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include"menu.h"
#include "AVLTree.h"
#include "MaxHeap.h"
#include <chrono>
using namespace std;
using namespace std::chrono; 

int getFilterIndx();
Node* createNode(string, string);
bool getContinueResponse();

int main(int argc, char* argv[]) {

	char commandArgument = *argv[1];

	if (commandArgument == '1')
	{
		std::cout << "FUNCTIONALITY WITH AVL TREE" << endl;
		bool userWantsToContinue = true;
		do
		{
			string filterOptions[] = { "None", "Industrials", "Health Care", 
				                       "Information Technology", "Consumer Discretionary",
									   "Consumer Staples", "Energy", "Financials",
									   "Utilities", "Real Estate", "Telecommunication Services" };
									   
			int filterIndex = getFilterIndx();
			bool userWantsToQuit = (filterIndex == -1);
			if (userWantsToQuit) return 0;

			string filterBy = filterOptions[filterIndex - 1];

			AVLTree tree;

			string filePath = "Text.txt";
			ifstream data;
			data.open(filePath);
			string line;
			int counter = 0;
			std::getline(data, line);
			auto start = high_resolution_clock::now();
			while (data) {

				if (counter != 0)
				{
					Node* companyInfo = createNode(line, filterBy);
					if (companyInfo != nullptr && companyInfo->getPriceEarnings() != "")
					{
						tree.insert(companyInfo);
					}
					counter++;
				}
				else
				{
					counter++;
				}
				std::getline(data, line);
			}
			data.close();
			tree.print();
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(end - start);
			std::cout << duration.count() << endl;
			userWantsToContinue = getContinueResponse(); 
		} while (userWantsToContinue);

		std::cout << "Goodbye!" << endl;
		return 0;
	}
	if (commandArgument == '2') {
		cout << "FUNCTIONALITY WITH MAXHEAP" << endl;
		bool userWantsToContinue = true;
		do
		{
			string filterOptions[] = { "None", "Industrials", "Health Care",
									   "Information Technology", "Consumer Discretionary",
									   "Consumer Staples", "Energy", "Financials",
									   "Utilities", "Real Estate", "Telecommunication Services" };

			int filterIndex = getFilterIndx();
			bool userWantsToQuit = (filterIndex == -1);
			if (userWantsToQuit) return 0;

			string filterBy = filterOptions[filterIndex - 1];
			string filePath = "Text.txt";
			ifstream data;
			data.open(filePath);
			string line;
			// Reads the data and inserts it into the heap
			int counter = 0;
			getline(data, line);
			MaxHeap heap;
			auto start = high_resolution_clock::now();
			while (data) {
				//Skips the first line of the file
				if (counter != 0)
				{
					Node* companyInfo = createNode(line, filterBy);
					if (companyInfo != nullptr && companyInfo->getPriceEarnings() != "")
					{
						heap.insert(companyInfo);
					}
					counter++;
				}
				else counter++;
				getline(data, line);
			}
			heap.sortAndDisplay();
			auto end = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(end - start);
			cout << duration.count() << endl;
			userWantsToContinue = getContinueResponse();
		} while (userWantsToContinue);

		std::cout << "Goodbye!" << endl;
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
			std::cout << "Goodbye!" << endl;
			return -1;
		}
		else if (filterResponse < 0 || filterResponse > 11) {

			std::cout << "Invalid input. Try a number between 0 and 11" << endl << endl;
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
bool getContinueResponse()
{
	bool userAnsweredIncorrectly = true;
	char answer;
	do
	{
		cout << "Do you want to continue(y/n)? ";
		cin >> answer;
		userAnsweredIncorrectly = (answer != 'y' && answer != 'n');
		if (userAnsweredIncorrectly)
		{
			cout << "invalid input. Type y for yes or n for no." << endl;
		}
	} while (userAnsweredIncorrectly);

	bool userWantsToContinue = (answer == 'y');

	if (userWantsToContinue) return true;
	else return false;
}