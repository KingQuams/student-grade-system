#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 50;
const int MAX_SCORES = 5;

struct Student {
    string name;
    int id;
    double scores[MAX_SCORES];
    int scoreCount;
};

void addStudent(Student students[], int &count);
void displayAll(const Student students[], int count);
double calculateAverage(const Student &s);
void showHighestAndLowest(const Student students[], int count);
void searchByName(const Student students[], int count);
void printMenu();

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, count);
                break;
            case 2:
                displayAll(students, count);
                break;
            case 3:
                showHighestAndLowest(students, count);
                break;
            case 4:
                searchByName(students, count);
                break;
            case 5:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void printMenu() {
    cout << "\n===== Student Grade Management System =====\n";
    cout << "1. Add student\n";
    cout << "2. Display all students\n";
    cout << "3. Show highest and lowest average\n";
    cout << "4. Search student by name\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

void addStudent(Student students[], int &count) {
    if (count >= MAX_STUDENTS) {
        cout << "Roster is full.\n";
        return;
    }

    Student s;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "Enter student ID: ";
    cin >> s.id;

    cout << "How many scores to enter (max " << MAX_SCORES << ")? ";
    cin >> s.scoreCount;
    if (s.scoreCount > MAX_SCORES) s.scoreCount = MAX_SCORES;

    for (int i = 0; i < s.scoreCount; i++) {
        cout << "  Score " << (i + 1) << ": ";
        cin >> s.scores[i];
    }

    students[count] = s;
    count++;

    cout << "Student added.\n";
}

double calculateAverage(const Student &s) {
    if (s.scoreCount == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < s.scoreCount; i++) {
        sum += s.scores[i];
    }
    return sum / s.scoreCount;
}

void displayAll(const Student students[], int count) {
    if (count == 0) {
        cout << "No students yet.\n";
        return;
    }

    cout << "\n--- Roster ---\n";
    cout << left << setw(5) << "ID" << setw(20) << "Name" << "Average\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << students[i].id
             << setw(20) << students[i].name
             << fixed << setprecision(2) << calculateAverage(students[i]) << "\n";
    }
}

void showHighestAndLowest(const Student students[], int count) {
    if (count == 0) {
        cout << "No students yet.\n";
        return;
    }

    int highIdx = 0, lowIdx = 0;
    double highAvg = calculateAverage(students[0]);
    double lowAvg = highAvg;

    for (int i = 1; i < count; i++) {
        double avg = calculateAverage(students[i]);
        if (avg > highAvg) { highAvg = avg; highIdx = i; }
        if (avg < lowAvg)  { lowAvg = avg;  lowIdx = i; }
    }

    cout << "Highest average: " << students[highIdx].name
         << " (" << fixed << setprecision(2) << highAvg << ")\n";
    cout << "Lowest average: " << students[lowIdx].name
         << " (" << fixed << setprecision(2) << lowAvg << ")\n";
}

void searchByName(const Student students[], int count) {
    string target;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, target);

    for (int i = 0; i < count; i++) {
        if (students[i].name == target) {
            cout << "Found: ID " << students[i].id
                 << ", Average: " << fixed << setprecision(2)
                 << calculateAverage(students[i]) << "\n";
            return;
        }
    }
    cout << "Student not found.\n";
}