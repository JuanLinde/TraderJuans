#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include"menu.h"
#include "AVLTree.h"
#include "MaxHeap.h"
#include <chrono>
#include <string>
#include <unordered_set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;
using namespace std::chrono; 

int getFilterIndx();
Node* createNode(string, string);
bool getContinueResponse();
string createSymbol(unordered_set<string>&);
string chooseSector(string[], const int);
void countSector(string, unordered_map<string, int>&);
string createPE();
void generateData();

int main(int argc, char* argv[]) {

	char commandArgument =  *argv[1];

	generateData();

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
/*
	Output: A string containing a random PE ratio

	Comment: This function creates a random PE ratio using a random() function. It uses a random
			 number between 0 and 1 to determine if the created pe ratio should be positive or
			 negative because negative pe ratios are possible. The max pe ratio is 500 the min pe
			 ratio is -500;
*/
string createPE()
{
	int posOrNegChooser = rand() % 2;
	int peWhole = rand() % 500;
	float peDecimal = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float pe = peWhole + peDecimal;
	if (posOrNegChooser == 0) return to_string(pe);
	else return to_string(-1 * pe);
}

/*
	Input: - A string containing the sector
		   - A reference to an unordered mapping from sector to the frequency of the number of
			 times it appears in the data.

	Comment: This function maintains an unordered mapping from the sector name to the frequency
			 of times it appears in the data.
*/
void countSector(string sector, unordered_map<string, int>& sectorToFreq)
{
	bool sectorIsInMapping = (sectorToFreq.find(sector) != sectorToFreq.end());

	if (sectorIsInMapping)
	{
		sectorToFreq[sector] = sectorToFreq[sector] + 1;
	}
	else
	{
		sectorToFreq[sector] = 1;
	}
}

/*
	Input: An unordered set of strings containing the symbols that have already been used.

	Output: A string containing the created symbol

*/
string createSymbol(unordered_set<string>& usedSymbols)
{
	bool symbolHasBeenUsed;
	int asciiVal1;
	int asciiVal2;
	int asciiVal3;
	int asciiVal4;
	char firstChar;
	char secChar;
	char thrChar;
	char fourChar;
	string symbol;

	do
	{
		/* chooses a random capital letter fromASCII*/

		asciiVal1 = rand() % 26 + 65;
		asciiVal2 = rand() % 26 + 65;
		asciiVal3 = rand() % 26 + 65;
		asciiVal4 = rand() % 26 + 65;

		firstChar = asciiVal1;
		secChar = asciiVal2;
		thrChar = asciiVal3;
		fourChar = asciiVal4;

		string firstCharS(1, firstChar), secCharS(1, secChar), thrCharS(1, thrChar),
			forChar(1, fourChar);

		symbol = firstCharS + secCharS + thrCharS + forChar;
		symbolHasBeenUsed = (usedSymbols.find(symbol) != usedSymbols.end());
		if (!symbolHasBeenUsed) usedSymbols.insert(symbol);

	} while (symbolHasBeenUsed);
	return symbol;
}

/*
	Input: - A string array containing the sector  from which to choose
		   - An int with the number of sectors available

	Output: A randomly selected sector from the list of available sectors
*/
string chooseSector(string arr[], const int numOfSec)
{
	int indx = rand() % 10;
	string sector = arr[indx];
	return sector;
}

/*
	Comments: This function generates a data set of 100,000 tuples. The tuples are of the form
	          "symbol,sector,PE_Ratio." This data is randomly generated using a number of helper
			  functions.

			  The function prints a summary of the number of occurances of each sector at the end.
*/
void generateData()
{
	srand(time(NULL));

	const int NUM_OF_SECTORS = 10;
	int numOfTuples = 100000;

	unordered_set<string> usedSymbols;      // Set to hold the used symbols. No repetition.
	string listOfSectors[] = { "Industrials", "Health Care",
							  "Information Technology", "Consumer Discretionary",
							  "Consumer Staples", "Energy", "Financials","Utilities",
							  "Real Estate", "Telecommunication Services" };
	unordered_map<string, int> sectorToFrequency;
	string symbol = "";
	string sector = "";
	string pe = "";                          // Price earning ratio
	string tuple = "";
	int lineCounter = 0;                     // Used to avoid overwriting first line in file
	ofstream outputFile;
	outputFile.open("data.txt");

	for (int i = 0; i < numOfTuples + 1; i++)
	{

		if (lineCounter == 0)
		{
			outputFile << "Symbol,Sector,PE_Ratio" << endl;
			lineCounter++;
		}
		else
		{
			symbol = createSymbol(usedSymbols);
			sector = chooseSector(listOfSectors, NUM_OF_SECTORS);
			countSector(sector, sectorToFrequency);
			pe = createPE();
			tuple = symbol + "," + sector + "," + pe;
			outputFile << tuple << endl;
			lineCounter++;
		}
	}
	int freqTotSum = 0;
	for (auto it = sectorToFrequency.begin(); it != sectorToFrequency.end(); it++)
	{
		cout << it->first << ":" << it->second << endl;
		freqTotSum += it->second;
	}
	cout << freqTotSum << endl;
	outputFile.close();
}