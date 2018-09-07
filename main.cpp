#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>

using namespace std;

class Login
{
    int choice;
    int confirmation;
    string username, password, password2;

void write_to_file(string username)
{
    ofstream writefile;
    string file = username+".txt";
    writefile.open(file.c_str(), ios::out);
    cin.clear();
    writefile << password<<';';
    writefile.close();
    system("cls");
    mainmenu();
    writefile.close();
}
void get_from_file(string username)
{
    ifstream getfile;
    string file = username+".txt";
    getfile.open(file.c_str());
    cin.clear();
    if (!getfile)
    {
        cout << "Wrong username"<<endl;
        mainmenu();
    }
    getfile.getline((char*)&password2,15,';');
    getfile.close();

}
void login()
{
    cout << "Enter the username: "; getchar(); getline(cin, username);
    cin.clear();
    get_from_file(username);
    cout << "Please enter the password: "; getchar(); cin >> password;
    cin.clear();
    if (password == password2)
    {
        cin.clear();
        cout << "You are being logged in!";
    }
    else
    {
        cout << "Sorry invalid" << endl;
        mainmenu();
    }

}


void registerpassword()
{
    cout << "Please enter the password:" << endl;
    cin >> password;
    cout << "Please renter your password:" << endl;
    cin >> password2;
    if (password == password2)
    {
        cin.clear();
        write_to_file(username);
        mainmenu();
    }
    else
    {
        cout << "Sorry invalid" << endl;
        registerpassword();
    }
}


void registerme()
{
    cout << "Please enter your username: " << endl;
    getchar();
    getline(cin, username);
    cout << "\nUsername: "<< username
         << "\nConfirm? \n\n"
         << "[1] Yes\n"
         << "[2] No" << endl;
    cin >> confirmation;
    if (confirmation == 1)
    {
        registerpassword();
    }

    else
    {
        cout << "Sorry invalid input, Please try again" << endl;
        cin.clear();
        registerme();
    }
}
public:
void mainmenu()
{   cout << "Hello, Would you like to log in or register\n"
         << "[1] Login\n"
         << "[2] Register\n"
         <<endl;
    cin >> choice;
    switch(choice)
    {
            case 1:
                    login();
                    break;

            case 2:
                    registerme();
                    break;
    }

}
}log1;

class stu
{
    uint32_t rollno;
    char Name[20];
    char Class[4];
    float marks;
    char grade;
    char calcgrade(float t1, char t2)
    {
        if (t1 >= 75) t2='A';
        else if (t1 >= 60) t2 = 'B';
        else if (t1 >= 50) t2 = 'C';
        else if (t1 >= 40) t2 = 'D';
        else t2 = 'E' ;
        return t2;
    }

  public:
    void getdata()
    {
        cout<<"Rollno :";   cin>>rollno;
        cout<<"Class :";    cin>>Class;
        cout<<"Name :";     getchar();  cin.getline(Name, 20);
        cout<<"Marks :";    cin>>marks;
        grade=calcgrade(marks,grade);
    }
    void putdata()
    {
        cout<< "Rollno : " << rollno << "\t Name : " << Name
            << "\n Marks : " << marks << "\t Grade : " << grade << endl;
    }
    int getrno() {  return rollno;    }
} s1, stud ;

int data_append()
{
    system("cls");
    cout << "Enter class (use numerals only)";      //implemented for school project
    getchar();
    char neim[8];
    cin.getline(neim,8);
    ifstream fi (neim, ios::in | ios::binary);
    if (!fi)
    {
        cout << "No such file in database" << endl;
        system("PAUSE");
        return -1;

    }
    ofstream fo ("temp.dat", ios::out | ios::binary);
    char last ='y';
    std::cout << " Enter details of student whose record is to be inserted \n ";
    s1.getdata();
    while (!fi.eof())
    {
        fi.read((char*)&stud, sizeof(stu));
        if ( s1.getrno()<= stud.getrno())
        {
            fo.write((char*)&s1, sizeof(stu));
            last = 'n';
            break;
        }
        else
            fo.write((char*)&stud, sizeof(stu));
    }
    if (last == 'y')
        fo.write((char*)&s1, sizeof(stu));
    else if (!fi.eof())
    {
        while (!fi.eof())
        {
        fi.read((char*)&stud, sizeof(stu));
        fo.write((char*)&stud, sizeof(stu));
        }
    }
    fi.close(); fo.close();
    remove(neim);
    rename("temp.dat",neim);
    fi.open(neim, ios::in);
    cout << "File now contains : \n";
    while (!fi.eof())
    {
        fi.read((char*)&stud, sizeof(stu));
        if (fi.eof()) break;
        stud.putdata();
    }
    fi.close();
    return 0;
}

int data_delete()
{
    cout << "Enter class (use numerals only)";      //implemented for school project
    getchar();
    char neim[8];
    cin.getline(neim,8);
    ifstream fi (neim, ios::in | ios::binary);
    if (!fi)
    {
        cout << "No such file in database" << endl;
        system("PAUSE");
        return -1;

    }
    ofstream file ("temp.dat", ios::out | ios::binary);
    int rno;    char found = 'f' , confirm = 'n' ;
    cout << " Enter rollno of student whose record is to be deleted \n";
    cin >> rno;
    while (!fi.eof())
    {
        fi.read((char*)&s1,sizeof(stu));
        if ( s1.getrno() == rno )
        {
            s1.putdata();
            found = 't';
            cout << " Are you sure, you want to delete this record? (y/n).. ";
            cin>> confirm ;
            if (confirm == 'n')
                file.write((char*)&s1,sizeof(stu));
        }
        else
            file.write((char*)&s1,sizeof(stu));
    }
    if ( found == 'f' )
        cout << " Record not found ;__; \n";
    fi.close();    file.close();
    remove("stu.dat");  rename("temp.dat","stu.dat");
    fi.open("stu.dat", ios::in);
    cout << "File now contains : \n";
    while (!fi.eof())
    {
        fi.read((char*)&stud, sizeof(stu));
        if (fi.eof()) break;
        stud.putdata();
    }
    fi.close();
    return 0;
}

int data_modify()
{
    fstream fio("stu.dat",ios::in|ios::out|ios::binary);
    int rno ;   long pos ;  char found = 'f';
    cout << " Enter rollno of student whose record is to be modified \n";
    getchar();
    cin >> rno;
    while ( !fio.eof())
    {
        pos = fio.tellg();
        fio.read((char*)&s1, sizeof(stu));
        if ( s1.getrno() == rno )
        {
            fio.seekg(pos);
            fio.write((char*)&s1, sizeof(stu));
            found = 't';
            break;
        }
    }
        if ( found == 'f')
            cout << "Record not found ;__; \n";
        fio.seekg(0);
        cout << "Now the file contains \n";
        while(!fio.eof())
        {
            fio.read((char*)&stud, sizeof(stu));
            stud.putdata();
        }
        fio.close();
        return 0;
}

int data_search()
{
    cout << "Enter class (use numerals only)";      //implemented for school project
    getchar();
    char neim[8];
    cin.getline(neim,8);
    ifstream fi (neim, ios::in | ios::binary);
    if (!fi)
    {
        cout << "No such file in database" << endl;
        system("PAUSE");
        return -1;

    }
    int rno;    char found = 'f' ;
    cout << " Enter rollno of student whose record is to be searched \n";
    cin >> rno;
    while (!fi.eof())
    {
        fi.read((char*)&s1,sizeof(stu));
        if ( s1.getrno() == rno )
        {
            s1.putdata();
            found = 't';
            fi.close();
        }
    }
    if ( found == 'f' )
        cout << " Record not found ;__; \n";
    return 0;
}
int main()
{
    //  log1.mainmenu();  coz errors
    menu:
    system("cls");

    cout << "\t\t\t Enter the number to proceed to corresponding operation" << endl;
    cout << "1. Append Data" << endl
         << "2. Delete Data" << endl
         << "3. Modify Data" << endl
         << "4. Search Record" << endl
         << "5. Exit" << endl;
    int *op = new int;
    cin >> *op;
    switch (*op)
    {
        case 1 : *op=data_append();
                    break;
        case 2 : *op=data_delete();
                    break;
        case 3 : *op=data_modify();
                    break;
        case 4 : *op=data_search();
                    break;
        case 5 : exit(0);

        default : cout << "Wrong input!";

    }
    system("pause");
    goto menu;
    return 0;
}
