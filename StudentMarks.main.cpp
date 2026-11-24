#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student
{
    int id;
    string name;
    int marks[5];
};

void menu();
void addStudents(Student s[], int &n);
void display(Student s[], int n);
int studentTotal(Student st);
double studentAverage(Student st);
double classAverage(Student s[], int n);
int highest(Student s[], int n);
int lowest(Student s[], int n);
int countPass(Student s[], int n);
char grade(double avg);
void sortStudents(Student s[], int n);
int search(Student s[], int n, int id);
void saveFile(Student s[], int n);

int main()
{
    Student s[50];
    int n = 0;
    int choice;

    cout << "Welcome to Student Marks Program" << endl;

    do
    {
        menu();
        cin >> choice;

        if (n == 0 && choice != 1 && choice != 0)
        {
            cout << "No students yet!! please add students first" << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            addStudents(s, n);
            break;
        case 2:
            display(s, n);
            break;
        case 3:
            for (int i = 0; i < n; i++)
            {
                cout << s[i].name << ": Total = " << studentTotal(s[i]) << "  Average = " << studentAverage(s[i]) << endl;
            }
            break;
        case 4:
            cout << "Class average = " << classAverage(s, n) << endl;
            break;
        case 5:
        {
            int h = highest(s, n);
            int l = lowest(s, n);
            cout << "Highest student: " << s[h].name << " with average " << studentAverage(s[h]) << endl;
            cout << "Lowest student: " << s[l].name << " with average " << studentAverage(s[l]) << endl;
            break;
        }
        case 6:
        {
            int pass = countPass(s, n);
            cout << "Passed students = " << pass << endl;
            cout << "Failed students = " << n - pass << endl;
            break;
        }
        case 7:
        {
            int id;
            cout << "Enter student ID: ";
            cin >> id;
            int i = search(s, n, id);
            if (i == -1)
                cout << "Student not found" << endl;
            else
            {
                cout << "Name: " << s[i].name << endl;
                cout << "Marks: ";
                for (int j = 0; j < 5; j++)
                    cout << s[i].marks[j] << " ";
                cout << endl;
                cout << "Total: " << studentTotal(s[i]) << "  Average: " << studentAverage(s[i]) << "  Grade: " << grade(studentAverage(s[i])) << endl;
            }
            break;
        }
        case 8:
            sortStudents(s, n);
            cout << "Students after sorting:" << endl;
            display(s, n);
            break;
        case 9:
            saveFile(s, n);
            break;
        case 0:
            cout << "Thank you, bye" << endl;
            break;
        default:
            cout << "Wrong choice!! try again" << endl;
        }

    } while (choice != 0);

    return 0;
}

void menu()
{
    cout << "\n----- Student Marks Management -----\n";
    cout << "1. Add students\n";
    cout << "2. Display students\n";
    cout << "3. Total and average of each student\n";
    cout << "4. Class average\n";
    cout << "5. Highest and lowest student\n";
    cout << "6. Number of passed and failed students\n";
    cout << "7. Search for a student\n";
    cout << "8. Sort students by average\n";
    cout << "9. Save to file\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void addStudents(Student s[], int &n)
{
    int num;
    cout << "Enter number of students: ";
    cin >> num;

    if (num <= 0)
    {
        cout << "Number must be more than 0" << endl;
        return;
    }
    if (n + num > 50)
    {
        cout << "You can only add " << 50 - n << " students" << endl;
        return;
    }

    for (int i = 0; i < num; i++)
    {
        cout << "\nStudent " << n + 1 << endl;

        cout << "ID: ";
        cin >> s[n].id;
        while (search(s, n, s[n].id) != -1)
        {
            cout << "This ID is already used, enter another ID: ";
            cin >> s[n].id;
        }

        cout << "Name: ";
        cin.ignore();
        getline(cin, s[n].name);

        for (int j = 0; j < 5; j++)
        {
            cout << "Mark " << j + 1 << ": ";
            cin >> s[n].marks[j];
            while (s[n].marks[j] < 0 || s[n].marks[j] > 100)
            {
                cout << "Mark must be between 0 and 100, enter again: ";
                cin >> s[n].marks[j];
            }
        }

        n++;
    }
    cout << "Done, students added successfully" << endl;
}

void display(Student s[], int n)
{
    cout << "\nID\tName\t\tM1\tM2\tM3\tM4\tM5\tTotal\tAvg\tGrade\n";
    for (int i = 0; i < n; i++)
    {
        cout << s[i].id << "\t" << s[i].name << "\t\t";
        for (int j = 0; j < 5; j++)
            cout << s[i].marks[j] << "\t";
        cout << studentTotal(s[i]) << "\t" << studentAverage(s[i]) << "\t" << grade(studentAverage(s[i])) << endl;
    }
}

int studentTotal(Student st)
{
    int sum = 0;
    for (int j = 0; j < 5; j++)
        sum = sum + st.marks[j];
    return sum;
}

double studentAverage(Student st)
{
    return studentTotal(st) / 5.0;
}

double classAverage(Student s[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum = sum + studentAverage(s[i]);
    return sum / n;
}

int highest(Student s[], int n)
{
    int max;
    max = 0;
    for (int i = 1; i < n; i++)
    {
        if (studentAverage(s[i]) > studentAverage(s[max]))
            max = i;
    }
    return max;
}

int lowest(Student s[], int n)
{
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        if (studentAverage(s[i]) < studentAverage(s[min]))
            min = i;
    }
    return min;
}

int countPass(Student s[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (studentAverage(s[i]) >= 60)
            count = count + 1;
    }
    return count;
}

char grade(double avg)
{
    if (avg >= 90)
        return 'A';
    else if (avg >= 80)
        return 'B';
    else if (avg >= 70)
        return 'C';
    else if (avg >= 60)
        return 'D';
    else
        return 'F';
}

void sortStudents(Student s[], int n)
{
    Student temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (studentAverage(s[j]) < studentAverage(s[j + 1]))
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int search(Student s[], int n, int id)
{
    int index = -1;
    bool found = false;
    int i = 0;
    while (i < n && found == false)
    {
        if (s[i].id == id)
        {
            found = true;
            index = i;
        }
        i++;
    }
    return index;
}

void saveFile(Student s[], int n)
{
    ofstream file("results.txt");

    if (!file)
    {
        cout << "Error opening file" << endl;
        return;
    }

    file << "Student Marks Report\n\n";
    file << "ID\tName\t\tM1\tM2\tM3\tM4\tM5\tTotal\tAvg\tGrade\n";
    for (int i = 0; i < n; i++)
    {
        file << s[i].id << "\t" << s[i].name << "\t\t";
        for (int j = 0; j < 5; j++)
            file << s[i].marks[j] << "\t";
        file << studentTotal(s[i]) << "\t" << studentAverage(s[i]) << "\t" << grade(studentAverage(s[i])) << endl;
    }

    int h = highest(s, n);
    int l = lowest(s, n);
    int pass = countPass(s, n);

    file << "\nNumber of students: " << n << endl;
    file << "Class average: " << classAverage(s, n) << endl;
    file << "Highest student: " << s[h].name << " (" << studentAverage(s[h]) << ")" << endl;
    file << "Lowest student: " << s[l].name << " (" << studentAverage(s[l]) << ")" << endl;
    file << "Passed: " << pass << endl;
    file << "Failed: " << n - pass << endl;

    file.close();
    cout << "Saved!! open results.txt to see the results" << endl;
}
