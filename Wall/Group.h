#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
class Group {
private:

	char* name_group;

	string* list_student;
	int amount_student;

	string* list_subject;
	int amount_subject;

public:

	Group(const char* name_groupP) :name_group{ new char[strlen(name_groupP) + 1] }, list_student{ new string[0] },
		amount_student{ 0 }, list_subject{ new string[0] }, amount_subject{ 0 } {

		if (name_groupP != nullptr) {
			for (int i = 0; i <= strlen(name_groupP); i++) name_group[i] = name_groupP[i];
		}
	}

	Group() :Group{ nullptr } {}

	~Group() {

		delete[] name_group;

		delete[] list_student;
		amount_student = 0;

		delete[] list_subject;
		amount_subject = 0;
	}

	string GetListStudent(const int index) { return this->list_student[index]; }

	string GetListSubject(const int index) { return this->list_subject[index]; }

	int GetSizeListStudent() { return amount_student; }

	int GetSizeListSubject() { return amount_subject; }



	void SetSizeListStudent(const int amount_student);

	void SetSizeListSubject(const int amount_subjectP);

	void SetListSubject();



	void AddStudent(const char* name_studentP);

	void DeleteStudent(const int index_delete);

	void DeleteSubject(const int index_delete);

};

class Student {
private:

	string name_student;

	vector<int> list_grade;

public:
	Student(const string name_studentP) :name_student{ name_studentP } {
		this->list_grade.clear();
	}
	Student() :Student("") {}

	~Student() {

		this->name_student = "";
		this->list_grade.clear();
	}


	string GetNameStudent() { return this->name_student; }

	int GetListGrade(const int index) { return this->list_grade[index]; }



	void AddGrade(const int grade);

	void DeleteGrade(const int grade);
};

class Subject {
private:
	vector<vector<string>> name_subject;
public:

	~Subject() { name_subject.resize(0); }


	string GetNameSubject(const int line, const int column) { return name_subject[line][column]; }



	int SizeNameSubjectLine() { return name_subject.size(); }

	int SizeNameSubjectColumn(const int index) { return name_subject[index].size(); }



	void AddNameSubject(const int index_find, const string choice_addP);

	void AddIndexNameSubject();



	void DeleteNameSubject(const int index_delete, const int size_student);

	void DeleteNameSubjectColumn(const int line, const int column);
};

