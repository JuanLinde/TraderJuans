#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include"menu.h"
#include "AVLTree.h"
using namespace std;

int getFilterIndx();
Node* createNode(string, string);

int main() {

	string filterOptions[] = { "None", "Industrials", "Health Care", "IT", "Consumer Discretionary", "Consumer Staples",
							  "Energy", "Financials", "Utilities", "Real Estate", "Telecommunications" };

	string filterBy = filterOptions[getFilterIndx()-1];

	AVLTree tree();

	string filePath = "Text.txt";
	ifstream data;
	data.open(filePath);
	string line;
	int counter = 0;
	getline(data, line);

	while (data) {

		if (counter != 0) {
			Node* companyInfo = createNode(line, filterBy);
			counter++;
		}
		else {
			counter++;
		}
		getline(data, line);
	}
	data.close();
	return 0;
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