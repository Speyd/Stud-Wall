#include "Apartment.h"
#include <iostream>
using namespace std;

void Apartment::SetSizeRoom(const int amount_roomP) { amount_room = amount_roomP; }

void Apartment::AddListRoom(const char* name_roomP) {
	int size = GetSizeRoom();
	SetSizeRoom(size + 1);

	if (list_room != nullptr) {

		string* templist_room = new string[size];
		for (int i{ 0 }; i != size; i++)templist_room[i] = list_room[i];

		delete[]list_room;
		list_room = new string[size + 1];

		for (int i{ 0 }; i != size; i++)list_room[i] = templist_room[i];
		delete[]templist_room;

		list_room[size] = name_roomP;
	}
	else {

		delete[]list_room;
		list_room = new string[size + 1];

		list_room[size] = name_roomP;
	}
}

void Apartment::DeleteListRoom(const int index_delete) {
	if (list_room != nullptr) {

		int size = GetSizeRoom() - 1;
		SetSizeRoom(size);

		if (size != 0) {
			string* templist_room = new string[size];

			for (int i{ 0 }, index{ 0 }; i != size + 1; i++, index++) {
				if (i != index_delete) templist_room[index] = list_room[i]; 
				else index--;
			}
			
			delete[]list_room;
			

			list_room = new string[size];

			for (int i{ 0 }; i != size; i++)list_room[i] = templist_room[i];

			delete[]templist_room;
		}
		else {
			delete[]list_room;
			string* list_room = new string[0];
		}
	}
}



void Room::GetCharactRoom() {

	cout << "Width: " << this->width << " cm" << endl;

	cout << "Length: " << this->length << " cm" << endl;

	cout << "Height: " << this->height << " cm" << endl;

	cout << "Do we count the ceiling in the area?: ";
	this->ceiling == 0 ? cout << "No" << endl : cout << "Yes" << endl;
}

double Room::RoomAreaCalculation() {
	double area = 0;

	area += this->width * this->length;
	if (this->ceiling == true) area *= 2;

	area += (this->height * this->width) * 2;

	area += (this->height * this->length) * 2;

	return area;
}



void Wallpaper::GetCharactRoom() {
	cout << "Width: " << this->width  << " cm" << endl;

	cout << "Length: " << this->length << " cm" << endl;

	cout << "Price: " << this->price << " dollar" << endl;
}