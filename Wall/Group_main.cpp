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
	cout << "\t  Журнал группы(" << name_group << ')' << endl;
}
void Enter(int choice) {
	string enter;
	if (choice != 1 && choice != 3 && choice != 4 && choice != 6 && choice != 8 && choice != 11 && choice != 13)cin.ignore();
	do {
		cout << "Нажмите enter что-бы выбрать другое действие/продолжить: "; getline(cin, enter);
	} while (!enter.empty());
}
#pragma endregion
void PrintSubject(Group& group) {
	for (int i = 0; i != group.GetSizeListSubject(); i++) {
		cout << i + 1 << "-ый предмет: " << group.GetListSubject(i) << endl;
	}
}
int SubjectSelection(Group& group) {
	int choice_subject = 1, count = group.GetSizeListSubject(), amount_grade = 0;
	double average = 0;

	do {
		ClearScreanTask2();
		PrintSubject(group);

		if (choice_subject >= 1 && choice_subject <= count)cout << "Впишите номер предмета который вам нужен: ";
		else cout << "Ваш номер выходит за рамки списка предетов!\nВпишите номер предмета который вам нужен снова: ";

		cin >> choice_subject;

	} while (choice_subject < 1 || choice_subject > count);

	return choice_subject - 1;
}
#pragma region AddDelete_Student
void AddStudent(Group& group, vector<Student>& student, Subject& subject) {
	char name[60];
	cin.ignore();
	cout << "Введите ФИО нового ученика: "; cin.getline(name, 60);
	student.push_back(Student(name));
	group.AddStudent(name);
	subject.AddIndexNameSubject();
}
void DeleteStudent(Group& group, vector<Student>& student, Subject& subject, const int index_delete) {
	ClearScreanTask2();
	cout << "Информаия успешно удалена!" << endl;

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

	if (average == 0)cout << "У группы нету оценок по предмету(" << group.GetListSubject(choice_averageall) << ')' << endl;
	else cout << "У группы средний бал по предмету(" << group.GetListSubject(choice_averageall) << "): " << round(average / amount_grade) << endl;
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

	if (average == 0)cout << "У группы нету оценок по всем предметам!" << endl;
	else cout << "У группы средний бал по всем предметам: " << round(average / amount_grade) << endl;
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

	if (average == 0)cout << "У ученика с именем(" << group.GetListStudent(index) << ") нету оценок по предмету(" << group.GetListSubject(choice_average) << ')' << endl;
	else cout << "У ученика с именем(" << group.GetListStudent(index) << ") средний бал по предмету(" << group.GetListSubject(choice_average) << "): " << round(average / amount_grade) << endl;
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

	if (average == 0)cout << "У ученика с именем(" << group.GetListStudent(index) << ") нету оценок по всем предметам" << endl;
	else cout << "У ученика с именем(" << group.GetListStudent(index) << ") средний бал по всем предметам: " << round(average / amount_grade) << endl;
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

	if (amount_grade == 0)cout << "У ученика нету оценок по предмету(" << group.GetListSubject(choice_minmax) << ')' << endl;
	else {
		cout << "У ученика минимальный балл по предмету(" << group.GetListSubject(choice_minmax) << "): " << min << endl;
		cout << "У ученика максимальный балл по предмету(" << group.GetListSubject(choice_minmax) << "): " << max << endl;
	}
}

#pragma endregion
void AddGrade(Group& group, vector<Student>& student, Subject& subject, const int index_find) {
	int choice_add = SubjectSelection(group), count = group.GetSizeListSubject(), grade = 1;

	do {

		ClearScreanTask2();

		if (grade >= 1 && grade <= 12)cout << "Впишите оценку за предмет(" << group.GetListSubject(choice_add) << "): ";
		else cout << "Ваша оценка выходит за рамки допустипого(1-12)!\nВпишите оценку за предмет(" << group.GetListSubject(choice_add) << ") снова: ";

		cin >> grade;

	} while (grade < 1 || grade > 12);
	ClearScreanTask2();

	subject.AddNameSubject(index_find, group.GetListSubject(choice_add));
	student[index_find].AddGrade(grade);

	cout << "Оценка успешно поставлена!" << endl;
}
void FindStudent(Group& group, vector<Student>& student, Subject& subject, const int choice) {
	int choice_find = 1, index_find = 1;

	vector<int> index_findname;
	char name[60];

	do {

		ClearScreanTask2();

		if (choice == 8)cout << "Нужно выбрать кому ставить оценку!" << endl;

		cout << "Искать будем по...\n[1] - ФИО\n[2] - По номеру в журнале\n[0] - Выйти в меню" << endl;

		if (choice_find >= 0 && choice_find <= 2)cout << "Введите ваш выбор: ";
		else cout << "Нету такого выбора! Введите ваш выбор снова: ";

		cin >> choice_find;

	} while (choice_find < 0 || choice_find > 2);

	if (choice_find == 0)return;

	else if (choice_find == 1) {

		ClearScreanTask2();
		cin.ignore();
		cout << "Введите ФИО которое ходите найти в журнале: "; cin.getline(name, 60);

		for (int i = 0; i != group.GetSizeListStudent(); i++) {
			if (group.GetListStudent(i) == name) {
				index_findname.resize(index_findname.size() + 1);
				index_findname[index_findname.size() - 1] = i;
			}
		}

		ClearScreanTask2();

		if (index_findname.size() == 0) { cout << "Ученика с ФИО(" << name << ") не найдено в журнале!" << endl; return; }

		else if (index_findname.size() == 1) {

			cout << "Ученика с ФИО(" << name << ") находиться на " << index_findname[0] + 1 << "-ым списке" << endl;

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

				cout << "В журнале есть неколько учеников с ФИО(" << name << ')' << endl;

				for (int i = 0; i != index_findname.size(); i++) {
					cout << index_findname[i] + 1 << "-ий в списке(" << name << ')' << endl;
				}

				if (choice == 4) {

					if (index_find != -1)cout << "Выберете ученика которого хотите удалить из журнала: ";

					else cout << "В этом списке нету ученика под номером " << temp_index << endl
						<< "Выберете ученика которого хотите удалить из журнала: ";

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

			if (index_find >= 1 && index_find <= group.GetSizeListStudent())cout << "Введите номер ученика в журнале: ";
			else cout << "Номер не может быть меньше 1 или больше общего количества студентов!\nВведите номер ученика в журнале снова: ";

			cin >> index_find;

		} while (index_find < 1 || index_find > group.GetSizeListStudent());

		ClearScreanTask2();
		cout << "Под номером " << index_find << " находиться ученик с ФИО(" << group.GetListStudent(index_find - 1) << ')' << endl;
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

		if (choice_delete >= 1 && choice_delete <= count)cout << "Впишите номер предмета что-бы его удалить(0 - выйти): ";
		else cout << "Ваш номер выходит за рамки списка предетов!\nВпишите номер предмета что-бы его удалить снова(0 - выйти): ";

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
	cout << "Введите имя группы: "; cin.getline(name_group, 30);

	Group group{ name_group };

	vector<Student> student;

	Subject subject;

	int choice = 0;
	do {

		do {

			ClearScreanTask2();

			cout << "Выберете действия в журанале\n[1] - Добавить ученика в журнал\n[2] - Вывести список учеников\n"
				<< "[3] - Поиск ученика в журнале\n[4] - Удалить ученика из журнала\n[5] - Вывести список предметов\n"
				<< "[6] - Добавить предмет\n[7] - Удалить предмет\n[8] - Выставить оценку по предмету\n"
				<< "[9] - Вывести среднею оценку ученика по предмету\n[10] - Вывести среднею оценку всей группы по предмету\n"
				<< "[11] - Вывести общий средний бал по всем предметам у ученика\n"
				<< "[12] - Вывести общий средний бал по всем предметам у всей группы\n"
				<< "[13] - Минимальный и маскимальный бал ученика за определенный предмет\n[0] - Выйти в меню" << endl;

			if (choice >= 0 && choice <= 13)cout << "Введите ваш выбор: ";

			else cout << "Нету такого выбора! Введите ваш выбор снова: ";

			cin >> choice;

		} while (choice < 0 || choice > 13);
		ClearScreanTask2();

		if (choice == 1) {
			AddStudent(group, student, subject);
		}

		else if (choice == 2) {

			if (group.GetSizeListStudent() != 0) {

				cout << "Список учеников" << endl;

				for (int i = 0; i != group.GetSizeListStudent(); i++) {

					cout << i + 1 << "-ий студент: " << group.GetListStudent(i) << endl;

				}
			}
			else cout << "Список учеников пуст!" << endl;
		}

		else if (choice == 3 || choice == 4) {
			if (group.GetSizeListStudent() != 0) FindStudent(group, student, subject, choice);
			else { cout << "Список учеников пуст!\nВы не можете взаимодействовать со списком учеников!" << endl; cin.ignore(); }
		}

		else if (choice == 5) {
			if (group.GetSizeListSubject() != 0) PrintSubject(group);
			else cout << "Список предметов пуст!" << endl;
		}

		else if (choice == 6) group.SetListSubject();

		else if (choice == 7) {
			if (group.GetSizeListSubject() != 0) DeleteSubjectInList(group, student, subject);
			else cout << "Список предметов пуст!\nВы не можете взаимодействовать со списком предметов!" << endl;
		}

		else if (choice == 8) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else { cout << "Список учеников/предметов пуст!\nВы не можете добавить оценку по предмету!" << endl; cin.ignore(); }
		}

		else if (choice == 9) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else cout << "Список учеников/предметов пуст!\nВы не можете узнать среднею оценку по предмету!" << endl;
		}

		else if (choice == 10) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)AverageGroupGrade(group, student, subject);
			else cout << "Список учеников/предметов пуст!\nВы не можете узнать среднею оценку по предмету всей группы!" << endl;
		}

		else if (choice == 11) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else { cout << "Список учеников/предметов пуст!\nВы не можете найти средний бал по все предметам у ученика!" << endl; cin.ignore(); }
		}

		else if (choice == 12) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)AverageGroupGradeAllSubject(group, student, subject);
			else cout << "Список учеников/предметов пуст!\nВы не можете узнать среднею оценку по всем предметам у всей группы!" << endl;
		}

		else if (choice == 13) {
			if (group.GetSizeListStudent() != 0 && group.GetSizeListSubject() != 0)FindStudent(group, student, subject, choice);
			else { cout << "Список учеников/предметов пуст!\nВы не можете узнать максиальную и минимальную оценку ученика по предметам!" << endl; cin.ignore(); }
		}

		if(choice != 0)Enter(choice);

	} while (choice != 0);

	return 0;
}