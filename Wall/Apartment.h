#include <iostream>
using namespace std;
class Apartment {
private:

	string* list_room;

	static int amount_room;

public:
	Apartment(const char* list_roomP) {
		if (list_roomP != nullptr) {
			string* temp_list_name = new string[amount_room - 1];
			for (int i{ 0 }; i != amount_room - 1; i++)temp_list_name[i] = list_room[i];
			delete[]list_room;
			list_room = new string[amount_room];
			for (int i{ 0 }; i != amount_room - 1; i++)list_room[i] = temp_list_name[i];
			delete[]temp_list_name;
			list_room[amount_room] = list_roomP;
		}
		else list_room = nullptr;
	}

	Apartment(): Apartment{ nullptr} {}

	~Apartment() {
		delete[]list_room;
		amount_room = 0;
	}
	
	void SetSizeRoom(const int amount_roomP);

	static int GetSizeRoom() { return amount_room; }

	string GetListRoom(const int index) { return list_room[index]; }

	void AddListRoom(const char* name_roomP);

	void DeleteListRoom(const int index_delete);
};

class Room {
private:

	char* name_room;

	double width;
	double height;
	double length;

	bool ceiling;

public:
	Room(const char* name_roomP, const double widthP, const double lengthP,
		 const double heightP, const int ceilingP)
		:width{ widthP }, length{ lengthP }, height{ heightP }, ceiling{ bool(ceilingP) } {

		if (name_roomP != nullptr) {
			this->name_room = new char[strlen(name_roomP) + 1];
			strcpy_s(this->name_room, strlen(name_roomP) + 1, name_roomP);
		}
		else this->name_room = nullptr;
	}

	Room(const char* name_roomP, const double widthP, const double lengthP, const double heightP)
		:Room(name_roomP, widthP, lengthP, heightP, 0) {}

	Room(const char* name_roomP, const double widthP, const double lengthP)
		:Room(name_roomP, widthP, lengthP, 0, 0) {}

	Room(const char* name_roomP, const double widthP):Room(name_roomP, widthP, 0, 0, 0) {}

	Room(const char* name_roomP) :Room(name_roomP, 0, 0, 0, 0) {}

	Room() :Room(nullptr, 0, 0, 0, 0) {}

	~Room() {
		delete[]this->name_room;

		this->width = 0;
		this->height = 0;
		this->length = 0;

		this->ceiling = 0;
	}

	void GetCharactRoom();

	double RoomAreaCalculation();

};


class Wallpaper {
private:

	string name;

	double width;
	double length;

	double price;
public:
	Wallpaper(const char* nameP, const double widthP, const double lengthP, const double priceP)
		:name{ "" },width{widthP}, length{lengthP}, price{priceP} {

		if (nameP != nullptr)this->name = nameP;
	}
	Wallpaper(const char* nameP, const double widthP, const double lengthP) :Wallpaper(nameP, widthP, lengthP, 0) {}
	Wallpaper(const char* nameP, const double widthP) :Wallpaper(nameP, widthP, 0, 0) {}
	Wallpaper(const char* nameP) :Wallpaper(nameP, 0, 0, 0) {}
	Wallpaper() :Wallpaper(nullptr, 0, 0, 0) {}

	~Wallpaper() {
		this->name = "";
		this->width = 0;
		this->length = 0;
		this->price = 0;
	}

	string GetNameWallp() { return this->name ; }


	double GetPrice() { return this->price; }

	void GetCharactRoom();

	double WallpAreaCalculation() { return this->width * this->length; }

};