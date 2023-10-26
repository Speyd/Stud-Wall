#include "Group.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
string subjectname_list[]{
"Украинский язык",
"Украинская литература",
"Иностранный язык",
"Зарубежная литература",
"История Украины",
"Всемирная история",
"Искусство",
"Алгебра",
"Геометрия",
"Биология",
"География",
"Физика",
"Химия",
"Технологии",
"Информатика",
"Основы здоровья",
"Физическая культура",
"Основы правоведения"
};


void Group::SetSizeListStudent(const int amount_studentP) { amount_student = amount_studentP; }

void Group::SetSizeListSubject(const int amount_subjectP) { amount_subject = amount_subjectP; }

void Group::AddStudent(const char* name_studentP) {
	int count = GetSizeListStudent();
	SetSizeListStudent(count + 1);
	if (list_student != nullptr) {

		string* temp_list_student = new string[count];

		for (int i{ 0 }; i != count; i++)temp_list_student[i] = list_student[i];

		delete[] list_student;
		list_student = new string[count + 1];

		for (int i{ 0 }; i != count; i++) list_student[i] = temp_list_student[i];

		list_student[count] = name_studentP;
		delete[] temp_list_student;
	}
	else {
		delete[]this->list_student;

		this->list_student = new string[count + 1];
		this->list_student[count] = name_studentP;
	}
}

void Group::DeleteStudent(const int index_delete) {
	int count = GetSizeListStudent() - 1;
	SetSizeListStudent(count);

	if (count > 0) {

		swap(list_student[index_delete], list_student[count]);
		string* temp_list_student = new string[count];

		for (int i{ 0 }; i != count; i++)temp_list_student[i] = list_student[i];

		delete[] list_student;
		list_student = new string[count];

		for (int i{ 0 }; i != count; i++) list_student[i] = temp_list_student[i];

		delete[] temp_list_student;
	}
	else {
		delete[] list_student;
		list_student = new string[0];
	}
}

void Group::SetListSubject() {
	int choice_subject = 1;

	do {
		cout << "Список уроков будет записан...\n[1] - Автоматически(уроки за 9 класс)\n[2] - Вручную\n[0] - Выйти" << endl;

		if (choice_subject >= 0 || choice_subject <= 2)cout << "Введите ваш выбор: ";
		else cout << "Нету такого выбора!\nВведите ваш выбор снова: ";

		cin >> choice_subject;

	} while (choice_subject < 0 || choice_subject > 2);
	if (choice_subject == 1) {

		SetSizeListSubject(18);

		if (list_subject != nullptr)delete[]list_subject;

		list_subject = new string[18];

		for (int i{ 0 }; i != 18; i++)list_subject[i] = subjectname_list[i];
	}
	else if (choice_subject == 2) {
		vector<string> add_subject;
		int count = GetSizeListSubject();

		cin.ignore();

		do {
			add_subject.resize(add_subject.size() + 1);
			cout << "Введите новый предмет(нажмите enter что-бы перестать вводить): "; getline(cin, add_subject[add_subject.size() - 1]);
		} while (!add_subject[add_subject.size() - 1].empty());

		add_subject.resize(add_subject.size() - 1);
		string* temp_subject = new string[count];

		for (int i{ 0 }; i != count; i++)temp_subject[i] = list_subject[i];

		delete[]list_subject;
		list_subject = new string[count + add_subject.size()];

		for (int i{ 0 }; i != count; i++)list_subject[i] = temp_subject[i];

		delete[] temp_subject;

		for (int i{ count }, l{ 0 }; l != add_subject.size(); i++, l++)list_subject[i] = add_subject[l];

		SetSizeListSubject(count + add_subject.size());
	}
}

void Group::DeleteSubject(const int index_delete) {
	int count = GetSizeListSubject() - 1;
	SetSizeListSubject(count);

	if (count > 0) {
		swap(list_subject[index_delete], list_subject[count]);
		string* temp_list_subject = new string[count];

		for (int i = 0; i != count; i++)temp_list_subject[i] = list_subject[i];

		delete[] list_subject;
		list_subject = new string[count];

		for (int i = 0; i != count; i++) list_subject[i] = temp_list_subject[i];

		delete[] temp_list_subject;
	}
	else {
		delete[] list_subject;
		list_subject = new string[0];
	}
}



void Subject::AddNameSubject(const int index_find, const string choice_addP) {

	name_subject[index_find].resize(name_subject[index_find].size() + 1);

	name_subject[index_find][name_subject[index_find].size() - 1] = choice_addP;
}

void Student::DeleteGrade(const int index) {

	swap(this->list_grade[index], this->list_grade[this->list_grade.size() - 1]);
	this->list_grade.resize(this->list_grade.size() - 1);
}

void Student::AddGrade(const int grade) {

	this->list_grade.resize(this->list_grade.size() + 1);
	this->list_grade[this->list_grade.size() - 1] = grade;
}



void Subject::DeleteNameSubject(const int index_delete, const int size_student) {

	swap(name_subject[index_delete], name_subject[size_student]);
	name_subject.resize(name_subject.size() - 1);
}

void Subject::DeleteNameSubjectColumn(const int line, const int column) {

	swap(name_subject[line][column], name_subject[line][name_subject[line].size() - 1]);
	name_subject[line].resize(name_subject[line].size() - 1);
}

void Subject::AddIndexNameSubject() {
	name_subject.resize(name_subject.size() + 1);
}