/*

Pamantasan ng Lungsod ng Maynila

Class Group Case Project Study

Group members:
APARICI, CHRISTIAN LORDENZ A.
BARNUEVO, JOHN BERNARD A.
ERNO, GARY DANIEL I.
GILO, DANNIEL KOOLIE C.
MORALES, JOSIAS SEYMOUR R.
PACLIAN, MICHA LENE R.

Course Code:
CPE 0211.1-3

Professor
TAN, RONALDO A.

Due date:
January 11, 2022

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <iomanip>
using namespace std;

// Class for Library items
struct Lib
{
public:
    char bookname[100], auname[50], sc[20], sc1[50];
    // Data in the format of MM/DD/YYYY
    int q, B, p;

    // Constructor
    // The instance of this class creates default chraracteristics
    Lib()
    {
        strcpy(bookname, "No Book Name");
        strcpy(auname, "No Author Name");
        strcpy(sc, "No Book ID");
        strcpy(sc1, "No Book ID");
        q = 0;
        B = 0;
        p = 0;
    }

    // Functions to be defined
    void get();
    void student();
    void pass();
    void librarian();
    void password();
    void getdata();
    void show(int);
    void booklist(int);
    void modify();
    void see(int);
    int branch(int);
    void issue();
    void der(char[], int, int);
    void fine(int, int, int, int, int, int);
};

// Implementation of getdata() function
// This function takes in the user input to fill the data needed for a certain book
// This can be used to add books or to issue books
void Lib::getdata()
{
    int i;
    // Flush the outer buffer of the screen
    fflush(stdin);

    // Enter the details
    cout << "\n\t\t" << setw(25) << "(Enter the details :-\n";
    cout << "\n\t\t" << setw(25) << "Enter Book's Name : ";
    cin.getline(bookname, 100);
    for (i = 0; bookname[i] != '\0'; i++)
    {
        if (bookname[i] >= 'a' && bookname[i] <= 'z')
            bookname[i] -= 32;
    }
    cout << "\n\t\t" << setw(25) << "Enter Author's Name : ";
    cin.getline(auname, 50);
    cout << "\n\t\t" << setw(25) << "Enter Publication name : ";
    cin.getline(sc1, 50);
    cout << "\n\t\t" << setw(25) << "Enter Book's ID : ";
    cin.getline(sc, 20);
    cout << "\n\t\t" << setw(25) << "Enter Book's Price : ";
    cin >> p;
    cout << "\n\t\t" << setw(25) << "Enter Book's Quantity : ";
    cin >> q;
}

// Implementation of show function
// This function prints the information of the available book inside the system
// Note that this function only gives the information for each individual book
void Lib::show(int i)
{
    cout << "\n\t\t" << setw(25) << "Book Name : " << bookname << endl;
    cout << "\n\t\t" << setw(25) << "Book's Author Name : " << auname << endl;
    cout << "\n\t\t" << setw(25) << "Book's ID : " << sc << endl;
    cout << "\n\t\t" << setw(25) << "Book's Publication : " << sc1 << endl;
    if (i == 2)
    {
        cout << "\n\t\t" << setw(25) << "Book's Price : " << p << endl;
        cout << "\n\t\t" << setw(25) << "Book's Quantity : " << q << endl;
    }
}

// Implementation of the booklist function
// This function takes the information from the show function
// to print the list of readily available books inside the system
void Lib::booklist(int i)
{
    int b, r = 0;
    system("cls");
    b = branch(i);
    system("cls");
    // Create a new file to store the booklist
    ifstream intf("booksdata.txt", ios::binary);
    if (!intf)
        cout << "\n\t\tFile Not Found.";
    else
    {
        // Print the book list
        cout << "\n\t" << setfill('*') << setw(25) << "*"
             << " Book List " << setw(25) << "*"
             << "\n\n";
        cout << setfill(' ');
        intf.read((char *)this, sizeof(*this));
        while (!intf.eof())
        {
            if (b == B)
            {
                if (q == 0 && i == 1)
                {
                }
                else
                {
                    r++;
                    cout << "\n\t\t" << setfill('*') << setw(25) << "*"
                         << " " << r << "." << setw(25) << "*"
                         << "\n";
                    cout << setfill(' ');
                    show(i);
                }
            }
            intf.read((char *)this, sizeof(*this));
        }
    }
    // Once all the books are printed, allow the user to press any key to exit
    cout << "\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    // If the previous user was a student, prompt the user window
    // Otherwise, prompt the librarian window
    if (i == 1)
        student();
    else
        librarian();
}

// Implementation of the modify function
// This function takes the previously defined book and change its information
// This also gives the option to add a book
void Lib::modify()
{
    char ch, st1[100];
    int i = 0, b, cont = 0;
    system("cls");
    cout << "\n\t\t>>Please Choose One Option :-\n";
    cout << "\n\t\t1. Modification In Current Books\n\n\t\t2. Add New Book\n\n\t\t3. Go back\n";
    cout << "\n\n\t\tEnter your choice : ";
    cin >> i;
    // Modify book information embedded into the database
    if (i == 1)
    {
        system("cls");
        b = branch(2);
        ifstream intf1("booksdata.txt", ios::binary);
        if (!intf1)
        {
            // If file is empty
            cout << "\n\t\tFile Not Found\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            librarian();
        }
        intf1.close();
        system("cls");
        cout << "\n\t\tPlease Choose One Option :-\n";
        cout << "\n\t\t1. Search By Book Name\n\n\t\t2. Search By Book's ID\n";
        cout << "\n\t\tEnter Your Choice : ";
        cin >> i;
        fflush(stdin);

        // Find the file through searching the book name itself
        if (i == 1)
        {
            // Append to the new file overwrite the previously entered information
            // The writing of the information in the text files are written in binary
            // This is to make a unified and uniform database and to avoid unwanted access outside
            // of the program
            system("cls");
            cout << "\n\t\t" << setw(25) << "Enter Book Name : ";
            cin.getline(st1, 100);
            system("cls");
            fstream intf("booksdata.txt", ios::in | ios::out | ios::ate | ios::binary);
            intf.seekg(0);
            intf.read((char *)this, sizeof(*this));
            while (!intf.eof())
            {
                for (i = 0; b == B && bookname[i] != '\0' && st1[i] != '\0' && (st1[i] == bookname[i] || st1[i] == bookname[i] + 32); i++)
                    ;
                if (bookname[i] == '\0' && st1[i] == '\0')
                {
                    cont++;
                    getdata();
                    intf.seekp(intf.tellp() - sizeof(*this));
                    intf.write((char *)this, sizeof(*this));
                    break;
                }
                intf.read((char *)this, sizeof(*this));
            }
            intf.close();
        }
        // Search the book through its ID
        else if (i == 2)
        {
            // Append to the new file overwrite the previously entered information
            cout << "\n\t\t" << setw(25) << "Enter Book's ID : ";
            cin.getline(st1, 100);
            system("cls");
            fstream intf("booksdata.txt", ios::in | ios::out | ios::ate | ios::binary);
            intf.seekg(0);
            intf.read((char *)this, sizeof(*this));
            while (!intf.eof())
            {
                for (i = 0; b == B && sc[i] != '\0' && st1[i] != '\0' && st1[i] == sc[i]; i++)
                    ;
                if (sc[i] == '\0' && st1[i] == '\0')
                {
                    cont++;
                    getdata();
                    intf.seekp(intf.tellp() - sizeof(*this));
                    intf.write((char *)this, sizeof(*this));
                    break;
                }
                intf.read((char *)this, sizeof(*this));
            }
            intf.close();
        }
        // Wrong input
        else
        {
            cout << "\n\t\tIncorrect Input..... :( \n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            modify();
        }
        // If not book is found
        if (cont == 0)
        {
            cout << "\n\t\tBook Not Found.\n";
            cout << "\n\t\tPress any key to continue.....";
            getch();
            system("cls");
            modify();
        }
        else
            cout << "\n\t\tUpdate Successful.\n";
    }
    // Add new book using the getdata function
    else if (i == 2)
    {
        system("cls");
        B = branch(2);
        system("cls");
        getdata();
        ofstream outf("booksdata.txt", ios::app | ios::binary);
        outf.write((char *)this, sizeof(*this));
        outf.close();
        cout << "\n\t\tBook added Successfully.\n";
    }
    // Go back to previous menu
    else if (i == 3)
    {
        system("cls");
        librarian();
    }

    else
    {
        cout << "\n\t\tWrong Input.\n";
        cout << "\n\t\tPress any key to continue.....";
        getch();
        system("cls");
        modify();
    }
    cout << "\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    librarian();
}

// Implementation of the branch function
// This prints the categories of which each book belongs for easier navigation
// The return value of this will be passed into the booklist function to access
// each book contained in the specified branch
int Lib::branch(int x)
{
    int i;
    cout << "\n\t\t>>Please Choose one Branch :-\n";
    cout << "\n\t\t1. Data Structures and Algorithms\n\n\t\t2. Fundamentals of Circuits\n\n\t\t3. Differential Calculus\n\n\t\t4. Engineering Data Analysis\n\n\t\t5. Computer Aided Design\n\n\t\t6. Physics\n\n\t\t7. Go to menu\n";
    cout << "\n\t\tEnter youur choice : ";
    cin >> i;
    switch (i)
    {
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    case 3:
        return 3;
        break;
    case 4:
        return 4;
        break;
    case 5:
        return 5;
        break;
    case 6:
        return 6;
        break;
    case 7:
        system("cls");
        if (x == 1)
            student();
        else
            librarian();
    default:
        cout << "\n\t\tPlease enter correct option : ";
        getch();
        system("cls");
        branch(x);
    }
}

// Implementation of the see function
// Pass the return value of from the branch function to see the contents of each branch
// After a branch is selected, the user is prompted to search for the desired book
void Lib::see(int x)
{
    int i, b, cont = 0;
    char ch[100];
    system("cls");
    b = branch(x);
    ifstream intf("booksdata.txt", ios::binary);
    if (!intf)
    {
        cout << "\n\t\tFile Not Found.\n";
        cout << "\n\t\t->Press any key to continue.....";
        getch();
        system("cls");
        if (x == 1)
            student();
        else
            librarian();
    }
    system("cls");
    cout << "\n\t\tPlease Choose one option :-\n";
    cout << "\n\t\t1. Search By Name\n\n\t\t2. Search By Book's ID\n";
    cout << "\n\t\tEnter Your Choice : ";
    cin >> i;
    fflush(stdin);
    intf.read((char *)this, sizeof(*this));
    if (i == 1)
    {
        cout << "\n\t\t" << setw(25) << "Enter Book's Name : ";
        cin.getline(ch, 100);
        system("cls");
        while (!intf.eof())
        {
            for (i = 0; b == B && q != 0 && bookname[i] != '\0' && ch[i] != '\0' && (ch[i] == bookname[i] || ch[i] == bookname[i] + 32); i++)
                ;
            if (bookname[i] == '\0' && ch[i] == '\0')
            {
                cout << "\n\t\tBook Found :-\n";
                show(x);
                cont++;
                break;
            }
            intf.read((char *)this, sizeof(*this));
        }
    }
    else if (i == 2)
    {
        cout << "\n\t\t" << setw(25) << "Enter Book's ID : ";
        cin.getline(ch, 100);
        system("cls");
        while (!intf.eof())
        {
            for (i = 0; b == B && q != 0 && sc[i] != '\0' && ch[i] != '\0' && ch[i] == sc[i]; i++)
                ;
            if (sc[i] == '\0' && ch[i] == '\0')
            {
                cout << "\n\t\tBook Found :-\n";
                show(x);
                cont++;
                break;
            }
            intf.read((char *)this, sizeof(*this));
        }
    }
    else
    {
        cont++;
        cout << "\n\t\tPlease enter correct option : ";
        getch();
        system("cls");
        see(x);
    }
    intf.close();
    if (cont == 0)
        cout << "\n\t\tThis Book is not available :( \n";
    cout << "\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    if (x == 1)
        student();
    else
        librarian();
}

// Implementation of issue function
// The issue function gives the functionality of the librarian to lend books to the students
// The librarian is given several options, from issue a book, to check the issued books
// to search for the name of the students that issued the books, reissue the books to
// to a different student, record the book that is returned, and to go back
void Lib::issue()
{
    char st[50], st1[20];
    int b, i, j, d, m, y, dd, mm, yy, cont = 0;
    system("cls");
    cout << "\n\t\t->Please Choose one option :-\n";
    cout << "\n\t\t1. Issue Book\n\n\t\t2. View Issued Book\n\n\t\t3. Search student/s who isuued books\n\n\t\t4. Reissue Book\n\n\t\t5. Return Book\n\n\t\t6. Go back to menu\n\n\t\tEnter Your Choice : ";
    cin >> i;
    fflush(stdin);

    // Open a new text file to contain the information of the student that will
    // issue a new book. This information will be recorded in separate text file
    if (i == 1)
    {
        system("cls");
        b = branch(2);
        system("cls");
        fflush(stdin);
        cout << "\n\t\t->Please Enter Details :-\n";
        cout << "\n\t\t" << setw(25) << "Enter Book Name : ";
        cin.getline(bookname, 100);
        cout << "\n\t\t" << setw(25) << "Enter Book's ID : ";
        cin.getline(sc, 20);
        // strcpy(st,sc);
        der(sc, b, 1);
        cout << "\n\t\t" << setw(25) << "Enter Student Name : ";
        cin.getline(auname, 100);
        cout << "\n\t\t" << setw(25) << "Enter Student's ID : ";
        cin.getline(sc1, 20);
        cout << "\n\t\t" << setw(25) << "Enter date (MM/DD/YYYY) : ";
        cin >> q >> B >> p;
        ofstream outf("student.txt", ios::binary | ios::app);
        outf.write((char *)this, sizeof(*this));
        outf.close();
        cout << "\n\n\t\tIssue Successfully.\n";
    }
    // Print issued book and the details on which it was issued
    else if (i == 2)
    {
        ifstream intf("student.txt", ios::binary);
        system("cls");
        cout << "\n\t\t->The Details are :-\n";
        intf.read((char *)this, sizeof(*this));
        i = 0;
        while (!intf.eof())
        {
            i++;
            cout << "\n\t\t*************** " << i << ". *************** \n";
            cout << "\n\t\t" << setw(25) << "Student Name : " << auname << "\n\t\t" << setw(25)
                 << "Student's ID : " << sc1 << "\n\t\t" << setw(25)
                 << "Book Name : " << bookname << "\n\t\t" << setw(25)
                 << "Book's ID : " << sc << "\n\t\t" << setw(25)
                 << "Date : " << q << "/" << B << "/" << p << "\n";
            intf.read((char *)this, sizeof(*this));
        }
        intf.close();
    }
    // Check the individual students that issued the books
    // This was a separate function so that when a student asks for
    // his/her record, it can be easily seen using their name
    else if (i == 3)
    {
        system("cls");
        fflush(stdin);
        // The information of the student name and id must be needed to search
        cout << "\n\t\t->Please Enter Details :-\n";
        cout << "\n\n\t\t" << setw(25) << "Enter Student Name : ";
        cin.getline(st, 50);
        cout << "\n\n\t\t" << setw(25) << "Enter Student's ID : ";
        cin.getline(st1, 20);
        system("cls");
        ifstream intf("student.txt", ios::binary);
        intf.read((char *)this, sizeof(*this));
        cont = 0;
        while (!intf.eof())
        {
            for (i = 0; sc1[i] != '\0' && st1[i] != '\0' && st1[i] == sc1[i]; i++)
                ;
            if (sc1[i] == '\0' && st1[i] == '\0')
            {
                cont++;
                if (cont == 1)
                {
                    cout << "\n\t\t->The Details are :-\n";
                    cout << "\n\t\t" << setw(25) << "Student Name : " << auname;
                    cout << "\n\t\t" << setw(25) << "Student's ID : " << sc1;
                }
                cout << "\n\n\t\t************ " << cont << ". Book details ************\n";
                cout << "\n\t\t" << setw(25) << "Book Name : " << bookname;
                cout << "\n\t\t" << setw(25) << "Book's ID : " << sc;
                cout << "\n\t\t" << setw(25) << "Date : " << q << "/" << B << "/" << p << "\n";
            }
            intf.read((char *)this, sizeof(*this));
        }
        intf.close();
        if (cont == 0)
            cout << "\n\t\tNo record found.";
    }
    // Modify the information of a previously issued book
    // If the book has been named to a different person or its return has
    // been moved to a different date, it can be updated here
    else if (i == 4)
    {
        system("cls");
        fflush(stdin);
        cout << "\n\t\t->Please Enter Details :-\n";
        cout << "\n\n\t\t" << setw(25) << "Enter Student's ID : ";
        cin.getline(st, 50);
        cout << "\n\t\t" << setw(25) << "Enter Book's ID : ";
        cin.getline(st1, 20);
        fstream intf("student.txt", ios::in | ios::out | ios::ate | ios::binary);
        intf.seekg(0);
        intf.read((char *)this, sizeof(*this));
        while (!intf.eof())
        {
            for (i = 0; sc[i] != '\0' && st1[i] != '\0' && st1[i] == sc[i]; i++)
                ;
            for (j = 0; sc1[j] != '\0' && st[j] != '\0' && st[j] == sc1[j]; j++)
                ;
            if (sc[i] == '\0' && sc1[j] == '\0' && st[j] == '\0' && st1[i] == '\0')
            {
                d = q;
                m = B;
                y = p;
                cout << "\n\t\t" << setw(25) << "Enter New Date (MM/DD/YYYY) : ";
                cin >> q >> B >> p;
                fine(d, m, y, q, B, p);                   // fn1
                intf.seekp(intf.tellp() - sizeof(*this)); // fn3
                intf.write((char *)this, sizeof(*this));  // fn5
                cout << "\n\n\t\tReissue successfully.";  // fn3
                break;
            }
            intf.read((char *)this, sizeof(*this));
        }
        intf.close();
    }
    // Return an issued book
    // This checks how much is the fine of the student based on the date
    // it borrowed the book, and the date it returned the book
    else if (i == 5)
    {
        system("cls");
        b = branch(2);
        system("cls");
        fflush(stdin);
        cout << "\n\t\t->Please Enter Details :-\n";
        cout << "\n\t\t" << setw(25) << "Enter Book's ID : ";
        cin.getline(st1, 20);
        der(st1, b, 2);
        cout << "\n\n\t\t" << setw(25) << "Enter Student's ID : ";
        cin.getline(st, 20);
        cout << "\n\t\t" << setw(25) << "Enter Present date : ";
        cin >> d >> m >> y;
        ofstream outf("temp.txt", ios::app | ios::binary);
        ifstream intf("student.txt", ios::binary);
        intf.read((char *)this, sizeof(*this));
        while (!intf.eof())
        {
            for (i = 0; sc[i] != '\0' && st1[i] != '\0' && st1[i] == sc[i]; i++)
                ;
            for (j = 0; sc1[j] != '\0' && st[j] != '\0' && st[j] == sc1[j]; j++)
                ;
            if (sc[i] == '\0' && sc1[j] == '\0' && st[j] == '\0' && st1[i] == '\0' && cont == 0)
            {
                cont++;
                intf.read((char *)this, sizeof(*this));
                fine(q, B, p, d, m, y);
                cout << "\n\t\tReturned successfully.";
            }
            else
            {
                outf.write((char *)this, sizeof(*this));
                intf.read((char *)this, sizeof(*this));
            }
        }
        intf.close();
        outf.close();
        getch();
        remove("student.txt");
        rename("temp.txt", "student.txt");
    }
    else if (i == 6)
    {
        system("cls");
        librarian();
    }
    else
        cout << "\n\t\tWrong Input.\n";
    cout << "\n\n\t\tPress any key to continue.....";
    getch();
    system("cls");
    librarian();
}

// Implementation of the fine function
// This function compares the starting date of the issued book
// to the date of its return to calculate how much the student has been fined
void Lib::fine(int d, int m, int y, int dd, int mm, int yy)
{
    long int n1, n2;
    int years, l, i;
    const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    n1 = y * 365 + d;
    for (i = 0; i < m - 1; i++)
        n1 += monthDays[i]; // fn1353
    years = y;
    if (m <= 2)
        years--;
    l = years / 4 - years / 100 + years / 400;
    n1 += l;
    n2 = yy * 365 + dd;
    for (i = 0; i < mm - 1; i++)
        n2 += monthDays[i];
    years = yy;
    if (m <= 2)
        years--;
    l = years / 4 - years / 100 + years / 400;
    n2 += l;
    n1 = n2 - n1;
    n2 = n1 - 15;
    if (n2 > 0)
        cout << "\n\t\t" << setw(25) << "The Total Fine is : " << n2;
}

// Implementation of der function
// Based on the branch and the issue function, it prints the books details
void Lib::der(char st[], int b, int x)
{
    int i, cont = 0;
    fstream intf("booksdata.txt", ios::in | ios::out | ios::ate | ios::binary);
    intf.seekg(0);
    intf.read((char *)this, sizeof(*this));
    while (!intf.eof())
    {
        for (i = 0; b == B && sc[i] != '\0' && st[i] != '\0' && st[i] == sc[i]; i++)
            ;
        if (sc[i] == '\0' && st[i] == '\0')
        {
            cont++;
            if (x == 1)
            {
                q--;
            }
            else
            {
                q++;
            }
            intf.seekp(intf.tellp() - sizeof(*this));
            intf.write((char *)this, sizeof(*this));
            break;
        }
        intf.read((char *)this, sizeof(*this));
    }
    if (cont == 0)
    {
        cout << "\n\t\tBook not found.\n";
        cout << "\n\n\t\tPress any key to continue.....";
        getch();
        system("cls");
        issue();
    }
    intf.close();
}

// Implementation of see function, where the main menu is printed
// This is the main screen the user sees in the start of the program
// This window gives the options to log-in as the student or the librarian
void Lib::get()
{
    int i;
    cout << "\n\t*********************** LIBRARY MANAGEMENT SYSTEM ***********************\n"
         << "\n\t\t\t    Group 3 Finals Project\n"
         << "\t   ____________________________________________________\n"
         << "\t  |____________________________________________________|\n"
         << "\t  | __     __   ____   ___ ||  ____    ____     _  __  |\n"
         << "\t  ||  |__ |--|_| || |_|   |||_|**|*|__|+|+||___| ||  | |\n"
         << "\t  ||==|^^||--| |=||=| |=*=||| |~~|~|  |=|=|| | |~||==| |\n"
         << "\t  ||  |##||  | | || | |JRO|||-|  | |==|+|+||-|-|~||__| |\n"
         << "\t  ||__|__||__|_|_||_|_|___|||_|__|_|__|_|_||_|_|_||__|_|\n"
         << "\t  ||_______________________||__________________________|\n"
         << "\t  | _____________________  ||      __   __  _  __    _ |\n"
         << "\t  ||=|=|=|=|=|=|=|=|=|=|=| __..\\/ |  |_|  ||#||==|  / /|\n"
         << "\t  || | | | | | | | | | | |/\\ \\  \\\\|++|=|  || ||==| / / |\n"
         << "\t  ||_|_|_|_|_|_|_|_|_|_|_/_/\\_.___\\__|_|__||_||__|/_/__|\n"
         << "\t |____________________ /\\~()/()~//\\ __________________|\n"
         << "\t  | __   __    _  _     \\_  (_ .  _/ _    ___     _____|\n"
         << "\t  ||~~|_|..|__| || |_ _   \\ //\\\\ /  |=|__|~|~|___| | | |\n"
         << "\t  ||--|+|^^|==|1||2| | |__/\\ __ /\\__| |==|x|x|+|+|=|=|=|\n"
         << "\t  ||__|_|__|__|_||_|_| /  \\ \\  / /  \\_|__|_|_|_|_|_|_|_|\n"
         << "\t  |_________________ _/    \\/\\/\\/    \\_ _______________|\n"
         << "\t  | _____   _   __  |/      \\../      \\|  __   __   ___|\n"
         << "\t  ||_____|_| |_|##|_||   |   \\/ __|   ||_|==|_|++|_|-|||\n"
         << "\t  ||______||=|#|--| |\\   \\   o    /   /| |  |~|  | | |||\n"
         << "\t  ||______||_|_|__|_|_\\   \\  o   /   /_|_|__|_|__|_|_|||\n"
         << "\t  |_________ __________\\___\\____/___/___________ ______|\n"
         << "\t  |__    _  /    ________     ______           /| _ _ _|\n"
         << "\t  |\\ \\  |=|/   //    /| //   /  /  / |        / ||%|%|%|\n"
         << "\t  | \\/\\ |*/  .//____//.//   /__/__/ (_)      /  ||=|=|=|\n"
         << "\t__|  \\/\\|/   /(____|/ //                    /  /||~|~|~|__\n"
         << "\t  |___\\_/   /________//   ________         /  / ||_|_|_|\n"
         << "\t  |___ /   (|________/   |\\_______\\       /  /| |______|\n"
         << "\t      /                  \\|________)     /  / | |\n";
    cout << "\n\t\t>>Please Choose Any Option To login \n";
    cout << "\n\t\t1. Student\n\n\t\t2. Librarian\n\n\t\t3. Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    if (i == 1)
    {
        system("cls");
        student();
    }
    else if (i == 2)
        pass();
    else if (i == 3)
        exit(0);
    else
    {
        cout << "\n\t\tPlease enter correct option : ";
        getch();
        system("CLS");
        get();
    }
}

// Implementation of student function that generates a new student screen
// This function prompts the user to view the booklist, search for a book, or go back to the main menu
// even close the application itself
void Lib::student()
{
    int i;
    cout << "\n\t*********************** WELCOME STUDENT ***********************\n"
         << "\t\t      _ _\n"
         << "\t\t .-. | | |\n"
         << "\t\t |M|_|A|N|\n"
         << "\t\t |A|a|.|.|<\\\n"
         << "\t\t |T|r| | | \\\\\n"
         << "\t\t |H|t|M|Z|  \\\\    \n"
         << "\t\t | |!| | |   \\>   \n"
         << "\t\t======================\n";
    cout << "\n\t\t>>Please Choose One Option:\n";
    cout << "\n\t\t1. View BookList\n\n\t\t2. Search for a Book\n\n\t\t3. Go to main menu\n\n\t\t4. Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    if (i == 1)
        booklist(1);
    else if (i == 2)
        see(1);
    else if (i == 3)
    {
        system("cls");
        get();
    }
    else if (i == 4)
        exit(0);
    else
    {
        cout << "\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        student();
    }
}

// Implementation of the password function
// Password function for initial log-in
void Lib::pass()
{
    int i = 0;
    char ch, st[21], ch1[21] = {"14mth30n3"};
    // Check the password
    cout << "\n\t\tEnter Password : ";
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            st[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            cout << "\b \b";
        }
        else
        {
            cout << "*";
            st[i] = ch;
            i++;
        }
    }
    // Check the input password inside the password file to check if the password is correct
    ifstream inf("password.txt");
    inf >> ch1;
    inf.close();
    for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++)
        ;
    if (st[i] == '\0' && ch1[i] == '\0')
    {
        // if the password is correct, prompt the librarian window
        system("cls");
        librarian();
    }
    else
    {
        cout << "\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
        getch();
        system("cls");
        get();
    }
}

// Librarian window pop-up
// After clearing the password, this is where most of the functionality of the program happens
// The windows prompts the librarian to view the booklist, search for a book, modify/add a book
// issue a book, go back to the main menu or change the password
void Lib::librarian()
{
    // remove("temp1.txt");
    int i;
    cout << "\n\t*********************** WELCOME LIBRARIAN ***********************\n"
         << "             .--.           .---.        .-.\n"
         << "         .---|--|   .-.     | A |  .---. |~|    .--.\n"
         << "      .--|===|Ch|---|_|--.__| S |--|:::| |~|-==-|==|---.\n"
         << "      |%%|NT2|oc|===| |~~|%%| C |--|   |_|~|CATS|  |___|-.\n"
         << "      |  |   |ah|===| |==|  | I |  |:::|=| |    |GB|---|=|\n"
         << "      |  |   |ol|   |_|__|  | I |__|   | | |    |  |___| |\n"
         << "      |~~|===|--|===|~|~~|%%|~~~|--|:::|=|~|----|==|---|=|\n"
         << "      ^--^---'--^---^-^--^--^---'--^---^-^-^-==-^--^---^-'\n";
    cout << "\n\t\t>>Please Choose One Option:\n";
    cout << "\n\t\t1. View BookList\n\n\t\t2. Search for a Book\n\n\t\t3. Modify/Add Book\n\n\t\t4. Issue Book\n\n\t\t5. Go to main menu\n\n\t\t6. Change Password\n\n\t\t7. Close Application\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> i;
    switch (i)
    {
    case 1:
        booklist(2);
        break;
    case 2:
        see(2);
        break;
    case 3:
        modify();
        break;
    case 4:
        issue();
        break;
    case 5:
        system("cls");
        get();
        break;
    case 6:
        password();
        break;
    case 7:
        exit(0);
    default:
        cout << "\n\t\tPlease enter correct option :(";
        getch();
        system("cls");
        librarian();
    }
}

// Implementation of the change password function
// This function changes the intitial password and set it to
// a new password
void Lib::password()
{
    int i = 0, j = 0;
    char ch, st[21], ch1[21] = {"14mth30n3"};
    system("cls");
    // Check for the old password
    cout << "\n\n\t\tEnter Old Password : ";
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            st[i] = '\0';
            break;
        }
        else if (ch == 8 && i > 0)
        {
            i--;
            cout << "\b \b";
        }
        else
        {
            cout << "*";
            st[i] = ch;
            i++;
        }
    }
    ifstream intf("password.txt");
    intf >> ch1;
    intf.close();
    for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++)
        ;
    if (st[i] == '\0' && ch1[i] == '\0')
    {
        system("cls");
        cout << "\n\t**The Password Should be less than 20 characters & don't use spaces**\n\n";
        cout << "\n\t\tEnter New Password : ";
        fflush(stdin);
        i = 0;
        while (1)
        {
            j++;
            ch = getch();
            if (ch == 13)
            {
                for (i = 0; st[i] != ' ' && st[i] != '\0'; i++)
                    ;
                if (j > 20 || st[i] == ' ')
                {
                    cout << "\n\n\t\tYou did't follow the instruction \n\n\t\tPress any key for try again.....";
                    getch();
                    system("cls");
                    password();
                    librarian();
                }
                st[i] = '\0';
                break;
            }
            else if (ch == 8 && i > 0)
            {
                i--;
                cout << "\b \b";
            }
            else
            {
                cout << "*";
                st[i] = ch;
                i++;
            }
        }
        ofstream outf("password.txt");
        outf << st;
        outf.close();
        cout << "\n\n\t\tYour Password has been changed Successfully.";
        cout << "\n\t\tPress any key to continue......";
        getch();
        system("cls");
        librarian();
    }
    else
    {
        cout << "\n\n\t\tPassword is incorrect.....\n";
        cout << "\n\t\tEnter 1 for retry or 2 for menu";
        cin >> i;
        if (i == 1)
        {
            system("cls");
            password();
        }
        else
        {
            system("cls");
            librarian();
        }
    }
}

int main()
{
    cout << left;
    Lib obj;
    obj.get(); // prompts the main menu
    getch();   // gets the character inputs
    return 0;
}

/************************************************** END OF PROGRAM ***********************************************************/