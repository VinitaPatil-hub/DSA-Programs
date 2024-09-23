#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

// A. Bubble sort - Sorting students by roll number in ascending order
void bubbleSortByRollNo(Student students[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (students[j].rollNo > students[j+1].rollNo) {
                swap(students[j], students[j+1]);
            }
        }
    }
}

// B. Insertion sort - Sorting students alphabetically by name
void insertionSortByName(Student students[], int n) {
    for (int i = 1; i < n; i++) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].name > key.name) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}

// C. Quick sort - Sorting students by SGPA to find top 10
int partition(Student students[], int low, int high) {
    float pivot = students[high].sgpa;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (students[j].sgpa > pivot) {
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSortBySGPA(Student students[], int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSortBySGPA(students, low, pi - 1);
        quickSortBySGPA(students, pi + 1, high);
    }
}

// D. Search students by SGPA and print all with the same SGPA
void searchBySGPA(Student students[], int n, float targetSGPA) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (students[i].sgpa == targetSGPA) {
            cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found with SGPA: " << targetSGPA << endl;
    }
}

// E. Binary search by name without recursion
int binarySearchByName(Student students[], int n, const string& targetName) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (students[mid].name == targetName) {
            return mid;
        } else if (students[mid].name < targetName) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Function to print the list of students
void printStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
    }
}

int main() {
    const int SIZE = 15; // Defining the size of the array
    Student students[SIZE] = {
        {101, "Alice", 8.5}, {102, "Bob", 9.0}, {103, "Charlie", 7.5}, {104, "David", 8.9},
        {105, "Eve", 9.5}, {106, "Frank", 8.2}, {107, "Grace", 9.3}, {108, "Heidi", 7.8},
        {109, "Ivan", 8.0}, {110, "Judy", 9.1}, {111, "Mallory", 6.5}, {112, "Niaj", 7.0},
        {113, "Oscar", 8.7}, {114, "Peggy", 8.4}, {115, "Quentin", 7.9}
    };

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Roll Call List (Sort by Roll No)\n";
        cout << "2. Arrange list alphabetically (Sort by Name)\n";
        cout << "3. Top 10 Toppers (Sort by SGPA)\n";
        cout << "4. Search students by SGPA\n";
        cout << "5. Search student by Name\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bubbleSortByRollNo(students, SIZE);
                cout << "Students sorted by Roll No:\n";
                printStudents(students, SIZE);
                break;
            case 2:
                insertionSortByName(students, SIZE);
                cout << "Students sorted by Name:\n";
                printStudents(students, SIZE);
                break;
            case 3:
                quickSortBySGPA(students, 0, SIZE - 1);
                cout << "Top 10 Toppers:\n";
                for (int i = 0; i < 10 && i < SIZE; i++) {
                    cout << "Rank " << i+1 << ": ";
                    cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
                }
                break;
            case 4: {
                float sgpa;
                cout << "Enter SGPA to search: ";
                cin >> sgpa;
                searchBySGPA(students, SIZE, sgpa);
                break;
            }
            case 5: {
                string name;
                cout << "Enter name to search: ";
                cin >> name;
                insertionSortByName(students, SIZE);  // Binary search requires sorted data
                int index = binarySearchByName(students, SIZE, name);
                if (index != -1) {
                    cout << "Student found - Roll No: " << students[index].rollNo << ", Name: " << students[index].name << ", SGPA: " << students[index].sgpa << endl;
                } else {
                    cout << "Student not found!\n";
                }
                break;
            }
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

