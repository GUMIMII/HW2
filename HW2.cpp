#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Student structure
struct student
{
    int ID;
    string firstName;
    string lastName;
    float GPA;
};

// Create a new student by user input
student *createStudent()
{
    student *s = new student;

    cout << "Enter ID: ";
    cin >> s->ID;

    cout << "Enter First Name: ";
    cin >> s->firstName;

    cout << "Enter Last Name: ";
    cin >> s->lastName;

    cout << "Enter GPA: ";
    cin >> s->GPA;

    return s;
}

// Print class
void printClass(student **classList, int size)
{
    if (size == 0)
    {
        cout << "No class loaded.\n";
        return;
    }

    float total = 0;

    for (int i = 0; i < size; i++)
    {
        cout << "ID: " << classList[i]->ID << " ";
        cout << classList[i]->firstName << " ";
        cout << classList[i]->lastName << " ";
        cout << "GPA: " << classList[i]->GPA << endl;

        total += classList[i]->GPA;
    }

    cout << "Number of Students: " << size << endl;
    cout << "Average GPA: " << total / size << endl;
}

// Edits the GPA of a specific user-select Student by student ID.
// Added some QOL by printing the name of the student being edited
void editStudent(student **classList, int size)
{
    int id;
    cout << "Enter student ID: ";
    cin >> id;

    for (int i = 0; i < size; i++)
    {
        if (classList[i]->ID == id)
        {
            cout << "Enter new GPA for: " << classList[i]->firstName << " " << classList[i]->lastName << ": ";
            cin >> classList[i]->GPA;
            cout << "Updated.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// Save to file (sorted largest to smallest GPA)
void saveClass(student **classList, int size)
{
    // Bubble sort by GPA (largest to smallest)
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (classList[j]->GPA < classList[j + 1]->GPA)
            {
                student *temp = classList[j];
                classList[j] = classList[j + 1];
                classList[j + 1] = temp;
            }
        }
    }

    ofstream file("students.txt");

    file << size << endl;

    for (int i = 0; i < size; i++)
    {
        file << classList[i]->ID << " "
             << classList[i]->firstName << " "
             << classList[i]->lastName << " "
             << classList[i]->GPA << endl;
    }

    file.close();

    cout << "Saved to file.\n";
}

// Load from file
void readFile(student **&classList, int &size)
{
    ifstream file("students.txt");

    if (!file)
    {
        cout << "File not found.\n";
        return;
    }

    // clean old memory
    if (classList != nullptr)
    {
        for (int i = 0; i < size; i++)
            delete classList[i];

        delete[] classList;
    }

    file >> size;

    classList = new student *[size];

    for (int i = 0; i < size; i++)
    {
        classList[i] = new student;
        file >> classList[i]->ID >> classList[i]->firstName >> classList[i]->lastName >> classList[i]->GPA;
    }

    file.close();

    cout << "Loaded from file.\n";
}

int main()
{
    /*
    Allocate an array of Student pointers to hold the number of students in the class.
    Have the user input the number of students in a class.
    For each student in the class, allocate a Student structure and have the user fill in the information.
    */
    student **classList = nullptr;
    int size = 0;
    char choice;

    cout << "A) Create New Class Record\n";
    cout << "B) Load Class Record\n";
    cout << "C) Print Class Record\n";
    cout << "D) Edit Student Record\n";
    cout << "M) Display Menu\n";
    cout << "Q) Exit\n";

    do
    {
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 'A' || choice == 'a')
        {
            // clean old memory
            if (classList != nullptr)
            {
                for (int i = 0; i < size; i++)
                    delete classList[i];

                delete[] classList;
            }

            cout << "Enter number of students: ";
            cin >> size;

            classList = new student *[size];

            //Loop until all students are entered
            for (int i = 0; i < size; i++)
            {
                cout << "\nStudent " << i + 1 << endl;
                classList[i] = createStudent();
            }
        }

        else if (choice == 'B' || choice == 'b')
        {
            readFile(classList, size);
        }

        else if (choice == 'C' || choice == 'c')
        {
            printClass(classList, size);
        }

        else if (choice == 'D' || choice == 'd')
        {
            editStudent(classList, size);
        }

        else if (choice == 'M' || choice == 'm')
        {
            cout << "A) Create New Class Record\n";
            cout << "B) Load Class Record\n";
            cout << "C) Print Class Record\n";
            cout << "D) Edit Student Record\n";
            cout << "M) Display Menu\n";
            cout << "Q) Exit\n";
        }

        else if (choice == 'Q' || choice == 'q')
        {
            saveClass(classList, size);

            // clean memory before exit
            if (classList != nullptr)
            {
                for (int i = 0; i < size; i++)
                    delete classList[i];

                delete[] classList;
            }

            cout << "Goodbye.\n";
        }

        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 'Q' && choice != 'q');

    return 0;
}
