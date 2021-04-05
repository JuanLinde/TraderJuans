#include<iostream>
#include"menu.h"
using namespace std;

int main() {

	Menu mainMenu("main");
	int mainResponse;
	int filterResponse;

	do {
		do {
			mainMenu.printMenu();
			mainResponse = mainMenu.getResponse("main");
			if (mainResponse == 0) {
				cout << "Goodbye!" << endl;
				return 0;
			}
		} while (mainResponse == 9);

		Menu filterMenu("filter");
		filterMenu.printMenu();
		filterResponse = filterMenu.getResponse("filter");
		if (filterResponse == 0) {
			cout << "Goodbye!" << endl;
			return 0;
		}
	} while (filterResponse == 12);


	return 0;
}