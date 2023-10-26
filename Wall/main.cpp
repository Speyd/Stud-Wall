#include "Apartment_main.h"
#include "Group_main.h"
#include <iostream>
#include <string>

using namespace std;

void ClearScrean() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\tRoom & Wallpaper | Student magazine" << endl;
}

int main() {
	int choice = 1;
	do {
		do {

			ClearScrean();
			cout << "Choose homework\n[1] - Room & Wallpaper\n[2] - Student magazine\n[0] - Exit" << endl;

			if (choice >= 0 && choice <= 2) cout << "Enter your choice: ";
			else cout << "There is no such choice!\nEnter your choice again: ";

			cin >> choice;

		} while (choice < 0 && choice > 2);

		ClearScrean();

		if (choice == 1)Apartment_main();
		else if (choice == 2)Group_main();

	} while (choice != 0);

	ClearScrean();
	cout << "The program closed successfully!";

	return 0;
}