#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    string name;
    float marks;
};

struct Credential {
    string username;
    string password;
    string role;
};

vector<Credential> credentials;

string currentUser, currentRole;


// ========================== ENSURE FILE EXISTS ==========================
void ensureFileExists(const string &filename) {
    ofstream fout(filename, ios::app);
    fout.close();
}


// ========================== LOAD CREDENTIALS ==========================
bool loadCredentials() {
    ensureFileExists(CREDENTIAL_FILE);

    ifstream fin(CREDENTIAL_FILE);
    if (!fin) {
        cout << "Error: Could not load credentials.txt\n";
        return false;
    }

    string line;
    while (getline(fin, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);

        if (p1 == -1 || p2 == -1) continue;

        Credential c;
        c.username = line.substr(0, p1);
        c.password = line.substr(p1 + 1, p2 - p1 - 1);
        c.role = line.substr(p2 + 1);

        credentials.push_back(c);
    }

    fin.close();
    return true;
}


// ========================== LOGIN SYSTEM ==========================
bool loginSystem() {
    string username, password;

    cout << "============ Login Screen ==============\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (auto &c : credentials) {
        if (c.username == username && c.password == password) {
            currentUser = c.username;
            currentRole = c.role;
            return true;
        }
    }
    return false;
}


// ========================== FORWARD DECLARATIONS ==========================
void mainMenu();
void adminMenu();
void userMenu();
void staffMenu();
void guestMenu();

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();


// ========================== MAIN ==========================
int main() {

    ensureFileExists(STUDENT_FILE);

    if (!loadCredentials()) return 0;

    if (loginSystem()) {
        mainMenu();
    } else {
        cout << "\nLogin failed. Exiting...\n";
    }
    return 0;
}


// ========================== MAIN MENU ==========================
void mainMenu() {
    if (currentRole == "ADMIN") adminMenu();
    else if (currentRole == "USER") userMenu();
    else if (currentRole == "STAFF") staffMenu();
    else guestMenu();
}


// ========================== ADMIN MENU ==========================
void adminMenu() {
    int choice;
    do {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: cout << "Invalid choice!\n";
        }
    } while (true);
}


// ========================== USER MENU ==========================
void userMenu() {
    int choice;
    cout << "\n===== USER MENU =====\n";
    cout << "1. Display All Students\n";
    cout << "2. Search Student\n";
    cout << "3. Logout\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: displayStudents(); break;
        case 2: searchStudent(); break;
        default: return;
    }
}


// ========================== STAFF MENU ==========================
void staffMenu() {
    int choice;
    cout << "\n===== STAFF MENU =====\n";
    cout << "1. Display All Students\n";
    cout << "2. Search Student\n";
    cout << "3. Update Student\n";
    cout << "4. Logout\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: displayStudents(); break;
        case 2: searchStudent(); break;
        case 3: updateStudent(); break;
        default: return;
    }
}


// ========================== GUEST MENU ==========================
void guestMenu() {
    int choice;
    cout << "\n===== GUEST MENU =====\n";
    cout << "1. Display All Students\n";
    cout << "2. Logout\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: displayStudents(); break;
        default: return;
    }
}


// ========================== ADD STUDENT ==========================
void addStudent() {

    ensureFileExists(STUDENT_FILE);

    ofstream fout(STUDENT_FILE, ios::app);
    if (!fout) {
        cout << "Error opening file!\n";
        return;
    }

    Student st;

    cout << "Enter Roll No: ";
    cin >> st.roll;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, st.name);

    cout << "Enter Marks: ";
    cin >> st.marks;

    fout << st.roll << "|" << st.name << "|" << st.marks << "\n";
    fout.close();

    cout << "Student added successfully!\n";
}


// ========================== DISPLAY STUDENTS ==========================
void displayStudents() {
    ensureFileExists(STUDENT_FILE);

    ifstream fin(STUDENT_FILE);
    if (!fin) {
        cout << "No student records found!\n";
        return;
    }

    cout << "\n"
         << left << setw(10) << "ROLL"
         << left << setw(25) << "NAME"
         << left << setw(10) << "MARKS" << "\n";

    cout << "--------------------------------------------------------\n";

    string line;
    while (getline(fin, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);

        Student st;
        st.roll = stoi(line.substr(0, p1));
        st.name = line.substr(p1 + 1, p2 - p1 - 1);
        st.marks = stof(line.substr(p2 + 1));

        cout << left << setw(10) << st.roll
             << left << setw(25) << st.name
             << left << setw(10) << st.marks << "\n";
    }

    fin.close();
}


// ========================== SEARCH STUDENT ==========================
void searchStudent() {
    int r;
    cout << "Enter roll number to search: ";
    cin >> r;

    ifstream fin(STUDENT_FILE);
    if (!fin) {
        cout << "File not found!\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(fin, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);

        Student st;
        st.roll = stoi(line.substr(0, p1));
        st.name = line.substr(p1 + 1, p2 - p1 - 1);
        st.marks = stof(line.substr(p2 + 1));

        if (st.roll == r) {
            cout << "\nRecord Found!\n";
            cout << "Roll : " << st.roll << "\n";
            cout << "Name : " << st.name << "\n";
            cout << "Marks: " << st.marks << "\n";
            found = true;
            break;
        }
    }

    if (!found) cout << "No record found!\n";

    fin.close();
}


// ========================== UPDATE STUDENT ==========================
void updateStudent() {
    int r;
    cout << "Enter roll number to update: ";
    cin >> r;

    ifstream fin(STUDENT_FILE);
    ofstream temp("temp.txt");

    if (!fin) {
        cout << "File not found!\n";
        return;
    }

    string line;
    bool found = false;

    cin.ignore();

    while (getline(fin, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);

        Student st;
        st.roll = stoi(line.substr(0, p1));
        st.name = line.substr(p1 + 1, p2 - p1 - 1);
        st.marks = stof(line.substr(p2 + 1));

        if (st.roll == r) {
            found = true;

            cout << "Enter new Name: ";
            getline(cin, st.name);

            cout << "Enter new Marks: ";
            cin >> st.marks;
            cin.ignore();
        }

        temp << st.roll << "|" << st.name << "|" << st.marks << "\n";
    }

    fin.close();
    temp.close();

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found) cout << "Record Updated!\n";
    else cout << "Record Not Found!\n";
}


// ========================== DELETE STUDENT ==========================
void deleteStudent() {
    int r;
    cout << "Enter roll number to delete: ";
    cin >> r;

    ifstream fin(STUDENT_FILE);
    ofstream temp("temp.txt");

    if (!fin) {
        cout << "File not found!\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(fin, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);

        Student st;
        st.roll = stoi(line.substr(0, p1));
        st.name = line.substr(p1 + 1, p2 - p1 - 1);
        st.marks = stof(line.substr(p2 + 1));

        if (st.roll != r) {
            temp << st.roll << "|" << st.name << "|" << st.marks << "\n";
        } else {
            found = true;
        }
    }

    fin.close();
    temp.close();

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found) cout << "Record Deleted!\n";
    else cout << "Record Not Found!\n";
}
