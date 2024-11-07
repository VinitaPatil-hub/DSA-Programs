#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure to store student data
struct Student {
    int rollNumber;
    string name;
    char division;
    string address;
};

// Function to add a student's information
void addStudent() {
    ofstream file("students.txt", ios::app); // Open file in append mode
    Student student;

    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore(); // Clear the input buffer

    cout << "Enter Name: ";
    getline(cin, student.name);

    cout << "Enter Division (A/B/C etc.): ";
    cin >> student.division;
    cin.ignore();

    cout << "Enter Address: ";
    getline(cin, student.address);

    // Write data to file
    file << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;

    file.close();
    cout << "Student record added successfully.\n";
}

// Function to delete a student's information
void deleteStudent(int rollNumber) {
    ifstream file("students.txt"); // Open file in read mode
    ofstream tempFile("temp.txt"); // Temporary file for writing updated data

    bool found = false;
    Student student;

    // Read each record and copy it to temp file if it doesn't match rollNumber
    while (file >> student.rollNumber) {
        file.ignore();
        getline(file, student.name, ' ');
        file >> student.division;
        file.ignore();
        getline(file, student.address);

        if (student.rollNumber != rollNumber) {
            tempFile << student.rollNumber << " " << student.name << " " << student.division << " " << student.address << endl;
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    // Replace original file with the temp file
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "Student record deleted successfully.\n";
    } else {
        cout << "Student record with roll number " << rollNumber << " not found.\n";
    }
}

// Function to display a student's information
void displayStudent(int rollNumber) {
    ifstream file("students.txt"); // Open file in read mode
    Student student;
    bool found = false;

    // Read each record and display it if rollNumber matches
    while (file >> student.rollNumber) {
        file.ignore();
        getline(file, student.name, ' ');
        file >> student.division;
        file.ignore();
        getline(file, student.address);

        if (student.rollNumber == rollNumber) {
            cout << "\nStudent Found:\n";
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Student record with roll number " << rollNumber << " not found.\n";
    }
}

// Main function
int main() {
    int choice, rollNumber;

    while (true) {
        cout << "\n--- Student Database Management ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            case 3:
                cout << "Enter Roll Number to display: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

