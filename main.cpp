#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>

using namespace std;

class Login
{
    public:
    char username[10], password[10];

}log1,log2;

int login()
{   cout << "\t\t\t Login Panel" << endl;
    cout << "Enter username: ";
    cin.getline(log1.username,10);
    cout << "Enter password: ";
    cin.getline(log1.password,10);
    ifstream fin ("db", ios::binary | ios::in);
    if (!fin)
    {
        cout<< "Database cannot be accessed" << endl;
        return 0;
    }
    int i=0;
    while(!fin.eof())
    {
        fin.read((char*)&log2 , sizeof(Login));
        if (strcmp(log1.username,log2.username)==0 && strcmp(log1.password,log2.password)==0)
        {
            cout << "Logged in" << endl;
            i=1;
            break;
        }

    }
    fin.close();
    if(!i)
        cout << "Wrong Credentials";
    return i;
}
void signup()
{   cout << "\t\t\t Signup Panel" << endl;
    cout << "Enter username: ";
    cin.getline(log1.username,10);
    cout << "Enter password: ";
    cin.getline(log1.password,10);
    ifstream fin ("db", ios::binary | ios::in);
    while(!fin.eof())
    {
        fin.read((char*)&log2 , sizeof(Login));
        if (!fin)
            break;
        if (strcmp(log1.username,log2.username)==0 )
        {
            cout << "User already exists!" << endl;
            system("PAUSE");
            system("CLS");
            signup();
        }

    }
    fin.close();
    ofstream fout ("db", ios::binary | ios::app);
    fout.write((char*)&log1 , sizeof(Login));
    fout.close();
}
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
int data_new()
{   char Class[10];
    cout << "Enter new class name :";
    getchar();
    cin.getline(Class,10);
    cout << "\nCreating Class files.." << endl;
    ifstream tmp1 (Class,ios::in);
    getchar();
    if (tmp1)
    {
        cout << "Class already exists!!!" << endl;
        tmp1.close();
        return -1;

    }
    ofstream newclass (Class,ios::out);
    newclass.close();
    cout << "Class creation successful" << endl;
    system("pause");
    return 0;
}
int main()
{  loginpanel:
    getchar();
    if(!login())
    {
        system("pause");
        signup();
    }
    system("pause");
    menu:
    system("cls");

    cout << "\t\t\t Enter the number to proceed to corresponding operation" << endl;
    cout << "1. Create Class" << endl
         << "2. Append Data" << endl
         << "3. Delete Data" << endl
         << "4. Modify Data" << endl
         << "5. Search Record" << endl
         << "6. Logout" << endl
         << "7. Exit" << endl;
    int *op = new int;
    cin >> *op;
    switch (*op)
    {
        case 1 : *op=data_new();
                    break;
        case 2 : *op=data_append();
                    break;
        case 3 : *op=data_delete();
                    break;
        case 4 : *op=data_modify();
                    break;
        case 5 : *op=data_search();
                    break;
        case 6 : goto loginpanel;
                    break;
        case 7 : exit(0);

        default : cout << "Wrong input!";
        getchar();
        delete op;
    }
    system("pause");
    goto menu;
    return 0;
}
