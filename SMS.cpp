#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string name;
    int rollNumber;
    char CNIC[14];  // 13 characters + 1 null terminator
    string studentClass;
    string address;
    char phoneNumber[12];  // 11 characters + 1 null terminator
    string previousResult;
};

void addStudent() {
    Student student;
    ofstream file("students.dat", ios::app | ios::binary);

    cout << "Enter Name: ";
    cin.ignore();  // Ignore newline character
    getline(cin, student.name);

    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore();  // Ignore newline character

    cout << "Enter CNIC (13 characters): ";
    cin.getline(student.CNIC, 14);

    do {
        cout << "Enter Class (11th or 12th): ";
        getline(cin, student.studentClass);
    } while (student.studentClass != "11th" && student.studentClass != "12th");

    cout << "Enter Address: ";
    getline(cin, student.address);

    cout << "Enter Phone Number (11 characters): ";
    cin.getline(student.phoneNumber, 12);

    cout << "Enter Previous Result: (Pass or Fial) ";
    cin >> student.previousResult;

    file.write((char*)&student, sizeof(student));
    file.close();

    cout << "Student record added successfully!" << endl;
}

void displayStudents() {
    Student student;
    ifstream file("students.dat", ios::in | ios::binary);

    if (!file) {
        cout << "No student records found!" << endl;
        return;
    }

    cout << "Student Records:" << endl;
    while (file.read((char*)&student, sizeof(student))) {
        cout << "Name: " << student.name << endl;
        cout << "Roll Number: " << student.rollNumber << endl;
        cout << "CNIC: " << student.CNIC << endl;
        cout << "Class: " << student.studentClass << endl;
        cout << "Address: " << student.address << endl;
        cout << "Phone Number: " << student.phoneNumber << endl;
        cout << "Previous Result: " << student.previousResult << endl;
        cout << "------------------------" << endl;
    }

    file.close();
}

void updateStudent() {
    int rollNumber;
    Student student;
    fstream file("students.dat", ios::in | ios::out | ios::binary);

    cout << "Enter Roll Number of student to update: ";
    cin >> rollNumber;

    while (file.read((char*)&student, sizeof(student))) {
        if (student.rollNumber == rollNumber) {
            cout << "Enter Update Name: ";
            cin.ignore();  // Ignore newline character
            getline(cin, student.name);

//            cout << "Enter New CNIC (13 characters): ";
//            cin.getline(student.CNIC, 14);

//            do {
//                cout << "Enter New Class (11th or 12th): ";
//                getline(cin, student.studentClass);
//            } while (student.studentClass != "11th" && student.studentClass != "12th");

            cout << "Enter New Address: ";
            getline(cin, student.address);

            cout << "Enter New Phone Number (11 characters): ";
            cin.getline(student.phoneNumber, 12);

            cout << "Enter New Previous Result: ";
            cin >> student.previousResult;

            file.seekp(-sizeof(student), ios::cur);
            file.write((char*)&student, sizeof(student));
            cout << "Student record updated successfully!" << endl;
            file.close();
            return;
        }
    }

    cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
    file.close();
}

void deleteStudent() {
    int rollNumber;
    Student student;
    ifstream inFile("students.dat", ios::in | ios::binary);
    ofstream outFile("temp.dat", ios::out | ios::binary);

    cout << "Enter Roll Number of student to delete: ";
    cin >> rollNumber;

    bool found = false;
    while (inFile.read((char*)&student, sizeof(student))) {
        if (student.rollNumber != rollNumber) {
            outFile.write((char*)&student, sizeof(student));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "Student Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Update Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
