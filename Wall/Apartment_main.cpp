#include "Apartment.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <iomanip>
using namespace std;
#pragma region Special_Abilities
extern void ClearScreanTask1() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\tRoom & Wallpaper" << endl;
}
void Enter() {
	string enter;
	cin.ignore();
	do {
		cout << "Нажмите enter что-бы выбрать другое действие/продолжить: "; getline(cin, enter);
	} while (!enter.empty());
}
#pragma endregion

#pragma region Room

int PrintAllRoom(Apartment& apartment) {
	int choice = 1, size = apartment.GetSizeRoom();

	do {

		ClearScreanTask1();

		for (int i = 0; i != size; i++)cout << i + 1 << " - " << apartment.GetListRoom(i) << endl;

		cout << "Information about which room we will display?" << endl;

		if (choice >= 1 && choice <= size)cout << "Enter your choice: ";
		else cout << "There is no such choice!\nEnter your choice again: ";

		cin >> choice;
	} while (choice < 1 || choice > size);

	return choice -= 1;
}

void AddRoom(Apartment& apartment, vector<Room>& room) {
	char newroom_name[30];
	double width = 1, length = 1, height = 1, ceiling = 0;

	cin.ignore();
	cout << "Enter name new room: "; cin.getline(newroom_name, 30);

	do {

		if (width > 0)cout << "Enter width new room(cm): ";
		else cout << "Width cannot be zero or less!\nEnter width new room again(cm): ";

		cin >> width;

	} while (width <= 0);

	do {

		if (length > 0)cout << "Enter length new room(cm): ";
		else cout << "Length cannot be zero or less!\nEnter length new room again(cm): ";

		cin >> length;

	} while (length <= 0);

	do {

		if (height > 0)cout << "Enter height new room(cm): ";
		else cout << "Height cannot be zero or less!\nEnter height new room again(cm): ";

		cin >> height;

	} while (height <= 0);

	do {

		ClearScreanTask1();
		cout << "Should we count the ceiling in the total area of the room?" << endl
			<< "[1] - No    |    [2] - Yes" << endl;

		if (ceiling >= 1 && ceiling <= 2)cout << "Enter your choice: ";
		else cout << "There is no such choice!\nEnter your choice again: ";

		cin >> ceiling;
	} while (ceiling < 1 || ceiling > 2);

	room.resize(apartment.GetSizeRoom() + 1, Room(newroom_name, width, length, height, --ceiling));
	apartment.AddListRoom(newroom_name);
}

void DeleteRoom(Apartment& apartment, vector<Room>& room) {
	int size = apartment.GetSizeRoom();

	if (size != 0) {

		int choice_deleteroom = PrintAllRoom(apartment), identical_rooms = 0;

		for (int i = 0; i != size; i++) {
			if (apartment.GetListRoom(i) == apartment.GetListRoom(choice_deleteroom))identical_rooms++;
		}

		cout << "Information about " << identical_rooms << "-th " << apartment.GetListRoom(choice_deleteroom)
			<< " successfully deleted" << endl;

		room.erase(room.begin() + choice_deleteroom);
		apartment.DeleteListRoom(choice_deleteroom);
	}
	else cout << "To delete out information about rooms you need to add them!" << endl;
}

void PrintInfoRoom(Apartment& apartment, vector<Room>& room) {
	int size = apartment.GetSizeRoom();

	if (size != 0) {

		int choice_room = PrintAllRoom(apartment), identical_rooms = 0;

		for (int i = 0; i != size; i++) {
			if (apartment.GetListRoom(i) == apartment.GetListRoom(choice_room))identical_rooms++;
		}

		ClearScreanTask1();
		cout << "Characteristics " << identical_rooms << "-th " << apartment.GetListRoom(choice_room) << endl;

		room[choice_room].GetCharactRoom();
	}
	else cout << "To find out information about rooms you need to add them!" << endl;
}

void PrintInfoAllRoom(Apartment& apartment) {
	int size = apartment.GetSizeRoom();

	if (size != 0) {
		for (int i = 0; i != size; i++)cout << i + 1 << " - " << apartment.GetListRoom(i) << endl;
	}
	else cout << "To display all rooms, at least one room must be included in the list!" << endl;
}

void AreaRoom(Apartment& apartment, vector<Room>& room) {
	if (apartment.GetSizeRoom != 0) {

		int choice_area = PrintAllRoom(apartment);
		double area = room[choice_area].RoomAreaCalculation();

		ClearScreanTask1();
		cout << "Area room equal to " << area << "cm^2(" << area * 0.0001 << "m^2)" << endl;
	}
	else cout << "You cannot find out the area of the room.The list of rooms is empty!" << endl;
}

void AreaAllRoom(Apartment& apartment, vector<Room>& room) {
	int size = apartment.GetSizeRoom();

	if (size != 0) {
		double area = 0;

		for (int i = 0; i != size; i++) {
			area += room[i].RoomAreaCalculation();
		}

		cout << "Area all room equal to " << area << "cm^2(" << area * 0.0001 << "m^2)" << endl;
	}
	else cout << "You cannot find out the area of the all room.The list of rooms is empty!" << endl;
}

#pragma endregion

#pragma region Wallpaper

int PrintAllWallpaper(vector<Wallpaper>& wallpaper) {
	int choice = 1;

	do {
		ClearScreanTask1();
		for (int i = 0; i != wallpaper.size(); i++)cout << i + 1 << " - " << wallpaper[i].GetNameWallp() << endl;

		cout << "Information about which wallpaper we will display?" << endl;

		if (choice >= 1 && choice <= wallpaper.size())cout << "Enter your choice: ";
		else cout << "There is no such choice!\nEnter your choice again: ";

		cin >> choice;
	} while (choice < 1 || choice >  wallpaper.size());
	return choice -= 1;
}

void AddWallpaper(vector<Wallpaper>& wallpaper) {
	char newwallp_name[30];

	double width = 1, length = 1, price = 1;

	cin.ignore();
	cout << "Enter name new wallpaper: "; cin.getline(newwallp_name, 30);

	do {

		if (width > 0)cout << "Enter width new wallpaper(cm): ";
		else cout << "Width cannot be zero or less!\nEnter width new wallpaper again(cm): ";

		cin >> width;

	} while (width <= 0);

	do {

		if (length > 0)cout << "Enter length new wallpaper(cm): ";
		else cout << "Length cannot be zero or less!\nEnter length new wallpaper again(cm): ";

		cin >> length;

	} while (length <= 0);

	do {

		if (price > 0)cout << "Enter price new wallpaper(dollar): ";
		else cout << "Сannot cost zero or less dollars!\nEnter price new wallpaper again(dollar): ";

		cin >> price;

	} while (price <= 0);

	wallpaper.push_back(Wallpaper(newwallp_name, width, length, price));
}

void DeleteWallpaper(vector<Wallpaper>& wallpaper) {
	if (wallpaper.size() != 0) {

		int choice_deletewallp = PrintAllWallpaper(wallpaper), identical_rooms = 0;

		ClearScreanTask1();

		for (int i = 0; i != wallpaper.size(); i++) {

			if (wallpaper[i].GetNameWallp() == wallpaper[choice_deletewallp].GetNameWallp())identical_rooms++;

		}

		cout << "Information about " << identical_rooms << "-th " << wallpaper[choice_deletewallp].GetNameWallp()
			<< " successfully deleted" << endl;

		wallpaper.erase(wallpaper.begin() + choice_deletewallp);
	}
	else cout << "To delete out information about wallpaper you need to add them!" << endl;
}

void PrintInfoWallpaper(vector<Wallpaper>& wallpaper) {
	if (wallpaper.size() != 0) {

		int choice_wallp = PrintAllWallpaper(wallpaper), identical_wallp = 0;

		for (int i = 0; i != wallpaper.size(); i++) {
			if (wallpaper[i].GetNameWallp() == wallpaper[choice_wallp].GetNameWallp())identical_wallp++;
		}

		ClearScreanTask1();
		cout << "Characteristics " << identical_wallp << "-th " << wallpaper[choice_wallp].GetNameWallp() << endl;

		wallpaper[choice_wallp].GetCharactRoom();
	}
	else cout << "To find out information about wallpaper you need to add them!" << endl;
}

void PrintInfoAllWallpaper(vector<Wallpaper>& wallpaper) {
	if (wallpaper.size() != 0) {
		for (int i = 0; i != wallpaper.size(); i++)cout << i + 1 << " - " << wallpaper[i].GetNameWallp() << endl;
	}
	else cout << "To display all wallpaper, at least one wallpaper must be included in the list!" << endl;
}

#pragma endregion

void AmountWallpaperForRoom(Apartment& apartment, vector<Room>& room, vector<Wallpaper>& wallpaper) {
	int size = apartment.GetSizeRoom();

	if (size != 0 && wallpaper.size() != 0) {

		int choice_room = PrintAllRoom(apartment), choice_wallp = PrintAllWallpaper(wallpaper), identical_rooms = 0;

		for (int i = 0; i != size; i++) {
			if (apartment.GetListRoom(i) == apartment.GetListRoom(choice_room))identical_rooms++;
		}

		double amount_wallp = room[choice_room].RoomAreaCalculation() / wallpaper[choice_wallp].WallpAreaCalculation();
		cout << "For " << identical_rooms << "-th " << apartment.GetListRoom(choice_room)
			<< " would need " << amount_wallp << " wallpaper(" << wallpaper[choice_wallp].GetNameWallp()
			<< "), which will cost " << amount_wallp * wallpaper[choice_wallp].GetPrice() << "dollars" << endl;
	}
	else cout << "To calculate the number of wallpapers per room, you need to have at least"
		<< " one room and one wallpaper in the list" << endl;
}

int Apartment::amount_room = 0;

int Apartment_main() {
	Apartment apartment;

	vector<Room> room;

	vector<Wallpaper> wallpaper;

	int choice = 0;

	do {
		do {

			ClearScreanTask1();
			cout << "[1] - Add a room(-s)\n[2] - Display information about the room\n[3] - Output all rooms\n"
				<< "[4] - Delete a room\n[5] - Find out the area of the room\n[6] - Find out the area of the all room\n"
				<< "[7] - Add a wallpaper\n[8] - Display information about the wallpaper\n[9] - Output all wallpaper\n"
				<< "[10] - Delete a wallpaper\n[11] - Quantity and cost of wallpaper for a room\n[0] - Exit" << endl;

			if (choice >= 0 && choice <= 11) cout << "Enter your choice: ";
			else cout << "There is no such choice!\nEnter your choice again: ";

			cin >> choice;

		} while (choice < 0 || choice > 11);

		ClearScreanTask1();
		switch (choice) {

		case 1:AddRoom(apartment, room); break;

		case 2:PrintInfoRoom(apartment, room); break;

		case 3:PrintInfoAllRoom(apartment); break;

		case 4:DeleteRoom(apartment, room); break;

		case 5:AreaRoom(apartment, room); break;

		case 6:AreaAllRoom(apartment, room); break;

		case 7:AddWallpaper(wallpaper); break;

		case 8:PrintInfoWallpaper(wallpaper); break;

		case 9:PrintInfoAllWallpaper(wallpaper); break;

		case 10:DeleteWallpaper(wallpaper); break;

		case 11:AmountWallpaperForRoom(apartment, room, wallpaper);
		}

		if(choice != 0)Enter();

	} while (choice != 0);

	return 0;
}