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
{
    cout << "\t\t\t Login Panel" << endl;
    getchar();
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
{
    cout << "\t\t\t Signup Panel" << endl;
    cout << "Enter username: ";
    cin.getline(log1.username,10);
    cout << "Enter password: ";
    cin.getline(log1.password,10);
    if( !strlen(log1.username) || !strlen(log1.password) )
    {
        cout << "Error, unsupported characters" << endl;
        signup();
    }
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

int data_append(char* neim)
{
    ifstream fi (neim, ios::in | ios::binary);
    if (!fi)
    {
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
    return 0;
}

int data_delete(char* neim)
{
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
    remove(neim);  rename("temp.dat",neim);
    return 0;
}

int data_modify(char* neim)
{
    fstream fio(neim,ios::in|ios::out|ios::binary);
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
            return -1;
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

int data_search(char* neim)
{

    ifstream fi (neim, ios::in | ios::binary);
    if (!fi)
    {
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
        return -2;
    return 0;
}
int data_new(char* Class)
{
    ifstream tmp1 (Class,ios::in);
    if (tmp1)
    {
        cout << "Class already exists!!!" << endl;
        tmp1.close();
        return -1;
    }
    ofstream newclass (Class,ios::out);
    newclass.close();
    return 0;
}
int data_remove(char* ClassDel)
{
    ifstream tmp1 (ClassDel,ios::in);
    if ( !tmp1 )
        return -1;
    tmp1.close();
    remove(ClassDel);
    return 0;
}
int main()
{
  loginpanel:
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
         << "6. Delete Class" << endl
         << "7. Logout" << endl
         << "8. Exit" << endl;
    int *op = new int;
    cin >> *op;
    switch (*op)
    {
        case 1 : {  char Class[10];
                    cout << "Enter new class name :";
                    getchar();
                    cin.getline(Class,10);
                    cout << "\nCreating Class files.." << endl;
                    *op=data_new(Class);
                    if (*op==(-1))
                    {
                        cout << "Class already exists!!!" << endl;
                        break;
                    }
                    cout << "Class creation successful" << endl;
                    system("pause");
                    delete op;
                    break;
                 }
        case 2 : {
                 system("cls");
                 char neim[8];
                 cout << "Enter class (use numerals only)";      //implemented for school project
                 getchar();
                 cin.getline(neim,8);
                 *op=data_append(neim);
                 if (*op==(-1))
                 {
                    cout << "No such file in database" << endl;
                    break;
                 }
                 ifstream fi(neim, ios::in);
                 cout << "File now contains : \n";
                 while (!fi.eof())
                {
                    fi.read((char*)&stud, sizeof(stu));
                    if (fi.eof()) break;
                    stud.putdata();
                }
                fi.close();
                delete op;
                break;
                }
        case 3 : {
                  cout << "Enter class";      //implemented for school project
                  getchar();
                  char neim1[8];
                  cin.getline(neim1,8);
                  *op=data_delete(neim1);
                  if (*op==(-1))
                  {
                        cout << "No such file in database" << endl;
                        system("PAUSE");
                  }
                  ifstream fi;
                  fi.open(neim1, ios::in);
                  cout << "File now contains : \n";
                  while (!fi.eof())
                  {
                        fi.read((char*)&stud, sizeof(stu));
                        if (fi.eof()) break;
                        stud.putdata();
                  }
                  fi.close();
                    delete op;
                    break;
                 }
        case 4 : {
                    cout << "Enter class (use numerals only)";      //implemented for school project
                    char neim[8];
                    cin.getline(neim,8);
                    *op=data_modify(neim);
                    if ( *op==(-1))
                    {
                        cout << "Record not found ;__; \n";
                    }
                    delete op;
                    break;
                 }
        case 5 : {
                    cout << "Enter class (use numerals only)";      //implemented for school project
                    char neim[8];
                    cin.getline(neim,8);
                    *op=data_search(neim);
                    if(*op==(-1))
                    {
                        cout << "No such file in database" << endl;
                        system("PAUSE");
                    }
                    else if(*op==(-2))
                    {
                        cout << "Record not found" << endl;
                        system("PAUSE");
                    }
                    delete op;
                    break;
                 }
        case 6 : {
                    char ClassDel[10];
                    cout << "Enter class name to be deleted:" << endl;
                    cin.getline(ClassDel,10);
                    cout << "Deleting Class files.." << endl;
                    *op=data_remove(ClassDel);
                    if(*op==(-1))
                    {
                     cout << "No such class as '" << ClassDel << "'" << endl;
                    }
                    delete op;
                    break;
                 }
        case 7 : {
                    delete op;
                    goto loginpanel;
                 }
        case 8 : {
                    delete op;
                    exit(0);
                 }
        default : cout << "Wrong input!";
    }
    system("pause");
    goto menu;
    return 0;
}
