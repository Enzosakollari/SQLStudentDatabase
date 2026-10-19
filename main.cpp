#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student
{
    int id;
    int age;
    string name;
    string degree;
    char group;
    int year;
};

void printStudent(Student student)
{
    cout << student.name << " " << student.age << " "
         << student.id << " " << student.degree << " "
         << student.year << " " << student.group << "\n";
}

int main()
{
    vector<Student> students;
    Student student{};

    cout << "Welcome to StudentSQL\n";
    cout << "Create a student by entering the following details:\n";

    cout << "ID: ";
    cin >> student.id;

    cout << "Age: ";
    cin >> student.age;

    cout << "Name: ";
    getline(cin >> ws, student.name);

    cout << "Degree: ";
    getline(cin >> ws, student.degree);

    cout << "Group: ";
    cin >> student.group;

    cout << "Year: ";
    cin >> student.year;

    students.push_back(student);

    printStudent(students[0]);

    return 0;
}