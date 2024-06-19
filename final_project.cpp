#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

void home();
void number_add();
void show();
void find();
void record_delete();
void update();

class diary
{
    int sr_no;
    char name[25];
    char phone_no[15];
    char email[30];
    char groupby[20];

public:
    int getsrno() { return sr_no; }
    void data_store()
    {
        cout << "\n..................CREATE NEW PHONE RECORD..................\n";
        cout << "Enter serial number: ";
        cin >> sr_no;
        cin.ignore();
        cout << "Enter Record Name : ";
        cin.getline(name, 25);
        cout << "Enter Mobile Number : ";
        cin.getline(phone_no, 15);
        cout << "Enter email I.D. : ";
        cin.getline(email, 30);
        cout << "Enter Record Group : ";
        cin.getline(groupby, 20);
        cout << endl;
    }
    void data_show()
    {
        cout << "\n..................PHONE BOOK RECORD..................\n";
        cout << "sr. no : " << sr_no << endl;
        cout << "Name : " << name << endl;
        cout << "Mobile no. : " << phone_no << endl;
        cout << "Email Id : " << email << endl;
        cout << "Group : " << groupby << endl;
    }
} page;

void number_add()
{
    ofstream fout;
    fout.open("Phonebook.dat", ios::out | ios::binary | ios::app);
    page.data_store();
    fout.write((char *)&page, sizeof(page));
    fout.close();
    cout << "\nRecord saved to file.....\n";
}

void show()
{
    ifstream fin;
    fin.open("Phonebook.dat", ios::in | ios::binary | ios::app);
    while (fin.read((char *)&page, sizeof(page)))
    {
        page.data_show();
    }
    fin.close();
    cout << "\nReading of data file completed..........\n";
}

void find()
{
    ifstream fin;
    int n, flag = 0;
    fin.open("Phonebook.dat", ios::in | ios::binary | ios::app);
    cout << "Enter Serial number of record to display: ";
    cin >> n;
    while (fin.read((char *)&page, sizeof(page)))
    {
        if (n == page.getsrno())
        {
            page.data_show();
            flag++;
            cout << "\n\n...........RECORD FOUND AND DISPLAYED.............\n";
        }
    }
    fin.close();
    if (flag == 0)
        cout << "\nThe Record of Serial Number " << n << " is not in file.....\n";
    cout << "\nReading of data file completed........\n";
}

void record_delete()
{
    ifstream fin;
    ofstream fout;
    int n, flag = 0;
    fin.open("Phonebook.dat", ios::in | ios::binary);
    fout.open("temp.dat", ios::out | ios::binary);
    cout << "Enter Serial number of Record to Delete : ";
    cin >> n;

    while (fin.read((char *)&page, sizeof(page)))
    {
        if (n == page.getsrno())
        {
            cout << "\n The Following record is deleted....\n";
            page.data_show();
            flag++;
        }
        else
        {
            fout.write((char *)&page, sizeof(page));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "\n The Record of Serial number " << n << " is not in file....\n";
    cout << "\nReading of the data file completed......\n";
    remove("Phonebook.dat");
    rename("temp.dat", "Phonebook.dat");
}

void update()
{
    fstream fio;
    int n, flag = 0, pos;
    fio.open("Phonebook.dat", ios::out | ios::binary | ios::in);
    cout << "Enter serial number of record to modify: ";
    cin >> n;
    while (fio.read((char *)&page, sizeof(page)))
    {
        pos = fio.tellg();
        if (n == page.getsrno())
        {
            cout << "\nThe following record will be modified.\n";
            page.data_show();
            flag++;
            cout << "\nRe-enter the new details.\n";
            page.data_store();
            fio.seekg(pos - sizeof(page));
            fio.write((char *)&page, sizeof(page));
            cout << "\nData Modified Successfully";
        }
    }
    fio.close();
    if (flag == 0)
        cout << "\nThe record of serial number " << n << " is not in file...\n";
    cout << "\nReading of data file completed.\n";
}

void home()
{
    int ch;
    do
    {
        cout << "..............................................\n";
        cout << "           PHONEBOOK MANAGEMENT\n             \n";
        cout << "..............................................\n";
        cout << "::::::::::::    PROGRAM MENU    ::::::::::::::\n";
        cout << "0. Exit\n";
        cout << "1. Save New Phone Record\n";
        cout << "2. Display all saved records\n";
        cout << "3. Search a specific record\n";
        cout << "4. Delete a specific record\n";
        cout << "5. Modify existing records\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            number_add();
            break;
        case 2:
            show();
            break;
        case 3:
            find();
            break;
        case 4:
            record_delete();
            break;
        case 5:
            update();
            break;
        }
        getch();
    } while (ch != 0);
}

int main()
{
    home();
}