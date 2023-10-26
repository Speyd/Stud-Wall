#include "Group.h"
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
extern string subjectname_list[];
char name_group[30];
#pragma region Special_Abilities
void ClearScreanTask2() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	cout << "\t  ������ ������(" << name_group << ')' << endl;
}
void Enter(int choice) {
	string enter;
	if (choice != 1 && choice != 3 && choice != 4 && choice != 6 && choice != 8 && choice != 11 && choice != 13)cin.ignore();
	do {
		cout << "������� enter ���-�� ������� ������ ��������/����������: "; getline(cin, enter);
	} while (!enter.empty());
}
#pragma endregion
void PrintSubject(Group& group) {
	for (int i = 0; i != group.GetSizeListSubject(); i++) {
		cout << i + 1 << "-�� �������: " << group.GetListSubject(i) << endl;
	}
}
int SubjectSelection(Group& group) {
	int choice_subject = 1, count = group.GetSizeListSubject(), amount_grade = 0;
	double average = 0;

	do {
		ClearScreanTask2();
		PrintSubject(group);

		if (choice_subject >= 1 && choice_subject <= count)cout << "������� ����� �������� ������� ��� �����: ";
		else cout << "��� ����� ������� �� ����� ������ ��������!\n������� ����� �������� ������� ��� ����� �����: ";

		cin >> choice_subject;

	} while (choice_subject < 1 || choice_subject > count);

	return choice_subject - 1;
}
#pragma region AddDelete_Student
void AddStudent(Group& group, vector<Student>& student, Subject& subject) {
	char name[60];
	cin.ignore();
	cout << "������� ��� ������ �������: "; cin.getline(name, 60);
	student.push_back(Student(name));
	group.AddStudent(name);
	subject.AddIndexNameSubject();
}
void DeleteStudent(Group& group, vector<Student>& student, Subject& subject, const int index_delete) {
	ClearScreanTask2();
	cout << "��������� ������� �������!" << endl;

	student[index_delete] = student.back();
	student.pop_back();

	group.DeleteStudent(index_delete);

	subject.DeleteNameSubject(index_delete, student.size());
}
#pragma endregion
#pragma region Average-MinMax

void AverageGroupGrade(Group& group, vector<Student>& student, Subject& subject) {
	int choice_averageall = SubjectSelection(group), count = group.GetSizeListSubject(), amount_grade = 0;

	double average = 0;

	for (int i = 0; i != subject.SizeNameSubjectLine(); i++) {

		for (int l = 0; l != subject.SizeNameSubjectColumn(i); l++) {

			if (subject.GetNameSubject(i, l) == group.GetListSubject(choice_averageall)) {

				average += student[i].GetListGrade(l);
				amount_grade++;
			}
		}
	}
	ClearScreanTask2();

	if (average == 0)cout << "� ������ ���� ������ �� ��������(" << group.GetListSubject(choice_averageall) << ')' << endl;
	else cout << "� ������ ������� ��� �� ��������(" << group.GetListSubject(choice_averageall) << "): " << round(average / amount_grade) << endl;
}

void AverageGroupGradeAllSubject(Group& group, vector<Student>& student, Subject& subject) {
	int count = group.GetSizeListSubject(), amount_grade = 0;

	double average = 0;

	for (int i = 0; i != subject.SizeNameSubjectLine(); i++) {

		for (int l = 0; l != subject.SizeNameSubjectColumn(i); l++) {

			for (int j = 0; j != count; j++) {

				if (subject.GetNameSubject(i, l) == group.GetListSubject(j)) {

					average += student[i].GetListGrade(l);
					amount_grade++;
					break;
				}
			}
		}
	}

	ClearScreanTask2();

	if (average == 0)cout << "� ������ ���� ������ �� ���� ���������!" << endl;
	else cout << "� ������ ������� ��� �� ���� ���������: " << round(average / amount_grade) << endl;
}

void AverageStudentGrade(Group& group, vector<Student>& student, Subject& subject, const int index) {
	int choice_average = SubjectSelection(group), count = group.GetSizeListSubject(), amount_grade = 0;

	double average = 0;

	for (int i = 0; i != subject.SizeNameSubjectColumn(index); i++) {

		if (subject.GetNameSubject(index, i) == group.GetListSubject(choice_average)) {

			average += student[index].GetListGrade(i);
			amount_grade++;
		}
	}

	ClearScreanTask2();

	if (average == 0)cout << "� ������� � ������(" << group.GetListStudent(index) << ") ���� ������ �� ��������(" << group.GetListSubject(choice_average) << ')' << endl;
	else cout << "� ������� � ������(" << group.GetListStudent(index) << ") ������� ��� �� ��������(" << group.GetListSubject(choice_average) << "): " << round(average / amount_grade) << endl;
}

void AverageStudentGradeAllSubject(Group& group, vector<Student>& student, Subject& subject, const int index) {
	int count = group.GetSizeListSubject(), amount_grade = 0;

	double average = 0;

	for (int i = 0; i != subject.SizeNameSubjectColumn(index); i++) {

		for (int l = 0; l != count; l++) {

			if (subject.GetNameSubject(index, i) == group.GetListSubject(l)) {

				average += student[index].GetListGrade(i);
				amount_grade++;
				break;
			}
		}
	}
	ClearScreanTask2();

	if (average == 0)cout << "� ������� � ������(" << group.GetListStudent(index) << ") ���� ������ �� ���� ���������" << endl;
	else cout << "� ������� � ������(" << group.GetListStudent(index) << ") ������� ��� �� ���� ���������: " << round(average / amount_grade) << endl;
}

void MinMaxGradeStudent(Group& group, vector<Student>& student, Subject& subject, const int index) {
	int choice_minmax = SubjectSelection(group), count = group.GetSizeListSubject(), amount_grade = 0, min = 12, max = 1;

	for (int i = 0; i != subject.SizeNameSubjectColumn(index); i++) {

		if (subject.GetNameSubject(index, i) == group.GetListSubject(choice_minmax)) {

			if (min > student[index].GetListGrade(i))min = student[index].GetListGrade(i);
			if (max < student[index].GetListGrade(i))max = student[index].GetListGrade(i);
			amount_grade++;
		}
	}

	ClearScreanTask2();

	if (amount_grade == 0)cout << "� ������� ���� ������ �� ��������(" << group.GetListSubject(choice_minmax) << ')' << endl;
	else {
		cout << "� ������� ����������� ���� �� ��������(" << group.GetListSubject(choice_minmax) << "): " << min << endl;
		cout << "� ������� ������������ ���� �� ��������(" << group.GetListSubject(choice_minmax) << "): " << max << endl;
	}
}

#pragma endregion
void AddGrade(Group& group, vector<Student>& student, Subject& subject, const int index_find) {
	int choice_add = SubjectSelection(group), count = group.GetSizeListSubject(), grade = 1;

	do {

		ClearScreanTask2();

		if (grade >= 1 && grade <= 12)cout << "������� ������ �� �������(" << group.GetListSubject(choice_add) << "): ";
		else cout << "���� ������ ������� �� ����� �����������(1-12)!\n������� ������ �� �������(" << group.GetListSubject(choice_add) << ") �����: ";

		cin >> grade;

	} while (grade < 1 || grade > 12);
	ClearScreanTask2();

	subject.AddNameSubject(index_find, group.GetListSubject(choice_add));
	student[index_find].AddGrade(grade);

	cout << "������ ������� ����������!" << endl;
}
void FindStudent(Group& group, vector<Student>& student, Subject& subject, const int choice) {
	int choice_find = 1, index_find = 1;

	vector<int> index_findname;
	char name[60];

	do {

		ClearScreanTask2();

		if (choice == 8)cout << "����� ������� ���� ������� ������!" << endl;

		cout << "������ ����� ��...\n[1] - ���\n[2] - �� ������ � �������\n[0] - ����� � ����" << endl;

		if (choice_find >= 0 && choice_find <= 2)cout << "������� ��� �����: ";
		else cout << "���� ������ ������! ������� ��� ����� �����: ";

		cin >> choice_find;

	} while (choice_find < 0 || choice_find > 2);

	if (choice_find == 0)return;

	else if (choice_find == 1) {

		ClearScreanTask2();
		cin.ignore();
		cout << "������� ��� ������� ������ ����� � �������: "; cin.getline(name, 60);

		for (int i = 0; i != group.GetSizeListStudent(); i++) {
			if (group.GetListStudent(i) == name) {
				index_findname.resize(index_findname.size() + 1);
				index_findname[index_findname.size() - 1] = i;
			}
		}

		ClearScreanTask2();

		if (index_findname.size() == 0) { cout << "������� � ���(" << name << ") �� ������� � �������!" << endl; return; }

		else if (index_findname.size() == 1) {

			cout << "������� � ���(" << name << ") ���������� �� " << index_findname[0] + 1 << "-�� ������" << endl;

			if (choice == 4) { DeleteStudent(group, student, subject, index_findname[0]); return; }

			else if (choice == 8) { AddGrade(group, student, subject, index_findname[0]); return; }

			else if (choice == 9) { AverageStudentGrade(group, student, subject, index_findname[0]); return; }

			else if (choice == 11) { AverageStudentGradeAllSubject(group, student, subject, index_findname[0]); return; }

			else if (choice == 13) { MinMaxGradeStudent(group, student, subject, index_findname[0]); return; }
		}

		else if (index_findname.size() > 1) {
			int temp_index;
			do {
				ClearScreanTask2();

				cout << "� ������� ���� �������� �������� � ���(" << name << ')' << endl;

				for (int i = 0; i != index_findname.size(); i++) {
					cout << index_findname[i] + 1 << "-�� � ������(" << name << ')' << endl;
				}

				if (choice == 4) {

					if (index_find != -1)cout << "�������� ������� �������� ������ ������� �� �������: ";

					else cout << "� ���� ������ ���� ������� ��� ������� " << temp_index << endl
						<< "�������� ������� �������� ������ ������� �� �������: ";

					cin >> index_find;

					temp_index = index_find;

					for (int i = 0; i != index_findname.size(); i++) {

						if (index_find - 1 == index_findname[i])break;
						else if (i + 1 == index_findname.size())index_find = -1;
					}

					if (index_find != -1)break;
				}
			} while (choice != 3);
		}
		Enter(choice);

		index_find--;

		if (choice == 4) { DeleteStudent(group, student, subject, index_find); return; }

		else if (choice == 8) { AddGrade(group, student, subject, index_find); return; }

		else if (choice == 9) { AverageStudentGrade(group, student, subject, index_find); return; }

		else if (choice == 11) { AverageStudentGradeAllSubject(group, student, subject, index_find); return; }

		else if (choice == 13) { MinMaxGradeStudent(group, student, subject, index_find); return; }
	}
	else if (choice_find == 2) {

		do {
			ClearScreanTask2();

			if (index_find >= 1 && index_find <= group.GetSizeListStudent())cout << "������� ����� ������� � �������: ";
			else cout << "����� �� ����� ���� ������ 1 ��� ������ ������ ���������� ���������!\n������� ����� ������� � ������� �����: ";

			cin >> index_find;

		} while (index_find < 1 || index_find > group.GetSizeListStudent());

		ClearScreanTask2();
		cout << "��� ������� " << index_find << " ���������� ������ � ���(" << group.GetListStudent(index_find - 1) << ')' << endl;
		cin.ignore();

		Enter(choice);

		index_find--;

		if (choice == 4) { DeleteStudent(group, student, subject, index_find); return; }
		else if (choice == 8) { AddGrade(group, student, subject, index_find); return; }
		else if (choice == 9) { AverageStudentGrade(group, student, subject, index_find); return; }
		else if (choice == 11) { AverageStudentGradeAllSubject(group, student, subject, index_find); return; }
		else if (choice == 13) { MinMaxGradeStudent(group, student, subject, index_find); return; }
	}
}
void DeleteSubjectInList(Group& group, vector<Student>& student, Subject& subject) {
	int choice_delete = 1, count = group.GetSizeListSubject();

	do {

		ClearScreanTask2();
		PrintSubject(group);

		if (choice_delete >= 1 && choice_delete <= count)cout << "������� ����� �������� ���-�� ��� �������(0 - �����): ";
		else cout << "��� ����� ������� �� ����� ������ ��������!\n������� ����� �������� ���-�� ��� ������� �����(0 - �����): ";

		cin >> choice_delete;

	} while (choice_delete < 1 || choice_delete > count);

	if (choice_delete == 0)return;

	for (int i = 0; i != subject.SizeNameSubjectLine(); i++) {

		for (int l = 0; l != subject.SizeNameSubjectColumn(i); l++) {

			if (subject.GetNameSubject(i, l) == group.GetListSubject(choice_delete - 1)) {

				subject.DeleteNameSubjectColumn(i, l);
				student[i].DeleteGrade(l);
				break;
				l--;
			}
		}
	}
	group.DeleteSubject(choice_delete - 1);
}
int Group_main() {
	setlocale(LC_ALL, "Rus");
	cin.ignore();
	cout << "������� ��� ������: "; cin.getline(name_group, 30);

	Group group{ name_group };

	vector<Student> student;

	Subject subject;

	int choice = 0;
	do {

		do {

			ClearScreanTask2();

			cout << "�������� �������� � ��������\n[1] - �������� ������� � ������\n[2] - ������� ������ ��������\n"
				<< "[3] - ����� ������� � �������\n[4] - ������� ������� �� �������\n[5] - ������� ������ ���������\n"
				<< "[6] - �������� �������\n[7] - ������� �������\n[8] - ��������� ������ �� ��������\n"
				<< "[9] - ������� ������� ������ ������� �� ��������\n[10] - ������� ������� ������ ���� ������ �� ��������\n"
				<< "[11] - ������� ����� ������� ��� �� ���� ��������� � �������\n"
				<< "[12] - ������� ����� ������� ��� �� ���� ��������� � ���� ������\n"
				<< "[13] - ����������� � ������������ ��� ������� �� ������������ �������\n[0] - ����� � ����" << endl;

			if (choice >= 0 && choice <= 13)cout << "������� ��� �����: ";

			else cout << "���� ������ ������! ������� ��� ����� �����: ";

			cin >> choice;

		} while (choice < 0 || choice > 13);
		ClearScreanTask2();

		if (choice == 1) {
			AddStudent(group, student, subject);
		}

		else if (choice == 2) {

			if (group.GetSizeListStudent() != 0) {

				cout << "������ ��������" << endl;

				for (int i = 0; i != group.GetSizeListStudent(); i++) {

					cout << i + 1 << "-�� �������: " << group.GetListStudent(i) << endl;

				}
			}
			else cout << "������ �������� ����!" << endl;
		}

		else if (choice == 3 || choice == 4) {
			if (group.GetSizeListStudent() != 0) FindStudent(group, student, subject, choice);
			else { cout << "������ �������� ����!\n�� �� ������ ����������������� �� ������� ��������!" << endl; cin.ignore(); }
		}

		else if (choice == 5) {
			if (group.GetSizeListSubject() != 0) PrintSubject(group);
			else cout << "������ ��������� ����!" << endl;
		}

		else if (choice == 6) group.SetListSubject();

		else if (choice == 7) {
			if (group.GetSizeListSubject() != 0) DeleteSubjectInList(group, student, subject);
			else cout << "������ ��������� ����!\n�� �� ������ ����������������� �� ������� ���������!" << endl;
		}

		else if (choice == 8) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else { cout << "������ ��������/��������� ����!\n�� �� ������ �������� ������ �� ��������!" << endl; cin.ignore(); }
		}

		else if (choice == 9) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else cout << "������ ��������/��������� ����!\n�� �� ������ ������ ������� ������ �� ��������!" << endl;
		}

		else if (choice == 10) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)AverageGroupGrade(group, student, subject);
			else cout << "������ ��������/��������� ����!\n�� �� ������ ������ ������� ������ �� �������� ���� ������!" << endl;
		}

		else if (choice == 11) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else { cout << "������ ��������/��������� ����!\n�� �� ������ ����� ������� ��� �� ��� ��������� � �������!" << endl; cin.ignore(); }
		}

		else if (choice == 12) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)AverageGroupGradeAllSubject(group, student, subject);
			else cout << "������ ��������/��������� ����!\n�� �� ������ ������ ������� ������ �� ���� ��������� � ���� ������!" << endl;
		}

		else if (choice == 13) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else { cout << "������ ��������/��������� ����!\n�� �� ������ ������ ����������� � ����������� ������ ������� �� ���������!" << endl; cin.ignore(); }
		}

		if(choice != 0)Enter(choice);

	} while (choice != 0);

	return 0;
}