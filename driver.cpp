#include<iostream>
#include<fstream>
#include<vector>
#include"menu.h"
#include"Node.h"
using namespace std;

pair<int, int> getResponses();
Node* createNode(string);

int main() {

	string filePath = "Text.txt";
	ifstream data;
	data.open(filePath);
	string line;
	int counter = 0;
	getline(data, line);

	while (data) {

		if (counter != 0) {
			Node* companyInfo = createNode(line);
			counter++;
		}
		else {
			counter++;
		}
		getline(data, line);
	}
	data.close();

	pair<int, int> responses = getResponses();
	int mainMenuResponse = responses.first;
	int filterMenuResponse = responses.second;
	return 0;
}

pair<int, int> getResponses() {
	Menu mainMenu("main");
	int mainResponse;
	int filterResponse;
	pair<int, int> responses;

	do {
		do {
			mainMenu.printMenu();
			mainResponse = mainMenu.getResponse("main");
			if (mainResponse == 0) {
				cout << "Goodbye!" << endl;
				responses.first = -1;
				responses.second = -1;
				return responses;
			}
		} while (mainResponse == 9);

		Menu filterMenu("filter");
		filterMenu.printMenu();
		filterResponse = filterMenu.getResponse("filter");
		if (filterResponse == 0) {
			cout << "Goodbye!" << endl;
			responses.first = -1;
			responses.second = -1;
			return responses;
		}
	} while (filterResponse == 12);

	return responses;
}
Node* createNode(string line) {

	vector<string> companyProperties;

	while (line.size() != 0) {

		size_t commaPosition = line.find(','); 
		bool commaFound = (commaPosition != std::string::npos); 
		if (commaFound) { 
			string property = line.substr(0, commaPosition);
			companyProperties.push_back(property);
			line.erase(0, commaPosition + 1); 
		}
		else {
			string property = line;
			companyProperties.push_back(property);
			line.clear();  
		}
	}
	Node* companyNode = new Node(companyProperties);
	return companyNode;
}