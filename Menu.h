#pragma once
#include<string>
#include<iostream>

class Menu {
private:
	std::string comments, prompt, title, result, response;
	bool isResponseValid(std::string, std::string);
public:
	Menu(std::string, std::string result = "");
	std::string getComments() { return comments; }
	std::string getPrompt() { return prompt; }
	std::string getTitle() { return title; }
	std::string getResult() { return result; }
	int getResponse(std::string);

	void printMenu();
};

bool Menu::isResponseValid(std::string a, std::string type) {
	if (type == "main") {

		for (auto chr : a) {
			if (!isdigit(chr)) return false;
		}
		if (stoi(a) < 0 || stoi(a) > 9) return false;
		return true;
	}
	else if (type == "filter") {
		for (auto chr : a) {
			if (!isdigit(chr)) return false;
		}
		if (stoi(a) < -1 || stoi(a) > 12) return false;
		return true;
	}
}

int Menu::getResponse(std::string type) {
	if (type == "main") {
		bool responseIsValid = false;
		std::string response = "";
		do {
			std::cin >> response;
			responseIsValid = isResponseValid(response, type);
			if (!responseIsValid) {
				std::cout << "Answer not valid. Try again." << std::endl;
				std::cout << getPrompt();
			}
		} while (!responseIsValid);
		std::cout << std::endl;
		return stoi(response);
	}
	else if ("filter") {
		bool responseIsValid = false;
		std::string response = "";
		do {
			std::cin >> response;
			responseIsValid = isResponseValid(response, type);
			if (!responseIsValid) {
				std::cout << "Answer not valid. Try again." << std::endl;
				std::cout << getPrompt();
			}
		} while (!responseIsValid);
		std::cout << std::endl;
		return stoi(response);
	}
}

Menu::Menu(std::string type, std::string r) {
	if (type == "main") {

		title = "Main Menu";

		comments = "Please type the number corresponding to the property by which you wish "
			"to sort the data: \n"
			"0: Quit Program\n"
			"1: Price\n"
			"2: Price/earnings\n"
			"3: Dividend Yield\n"
			"4: Earnings/Share\n"
			"5: 52 week low\n"
			"6: 52 week high\n"
			"7: Market Cap\n"
			"8: EBITDA\n"
			"9: Main Menu\n"
			"0: Quit Program\n";

		prompt = "Rank by: ";

		result = r;
	}
	else if (type == "results") {
		title = "Results: ";
		result = r;
		prompt = "Type 0 to quit or 1 to return to main menu: ";
		comments = "";
	}

	else if (type == "filter") {
		title = "Filter Menu";

		prompt = "Filter by: ";

		comments = "Please type an option for filtering your results: \n"
			"12: Return to choose property\n"
			"0: Quit Program\n"
			"1: None\n"
			"2: Industrials\n"
			"3: Health Care\n"
			"4: Information Technology\n"
			"5: Consumer Discretionary\n"
			"6: Consumer Staples\n"
			"7: Energy\n"
			"8: Financials\n"
			"9: Utilities\n"
			"10: Real State\n"
			"11: Telecommunications\n"
			"12: Return to choose property\n"
			"0: Quit Program\n";

		result = r;

	}
}

void Menu::printMenu() {
	std::cout << getTitle() << std::endl;
	std::cout << getComments() << std::endl;
	std::cout << getPrompt();
}