#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>


class Login
{
    public:
    char username[10], password[10];

}log1,log2;

int login()
{
    std::cout << "\t\t\t Login Panel" << std::endl;
    getchar();
    std::cout << "Enter username: ";
    std::cin.getline(log1.username,10);
    std::cout << "Enter password: ";
    std::cin.getline(log1.password,10);
    std::ifstream fin ("db", std::ios::binary | std::ios::in);
    if (!fin)
    {
        std::cout<< "Database cannot be accessed" << std::endl;
        return 0;
    }
    int i=0;
    while(!fin.eof())
    {
        fin.read((char*)&log2 , sizeof(Login));
        if (strcmp(log1.username,log2.username)==0 && strcmp(log1.password,log2.password)==0)
        {
            std::cout << "Logged in" << std::endl;
            i=1;
            break;
        }

    }
    fin.close();
    if(!i)

        std::cout << "Wrong Credentials";

    return i;
}
int signup()
{
        std::cout << "\t\t\t Signup Panel" << std::endl;
        std::cout << "Enter username: ";
        getchar();
        std::cin.getline(log1.username,10);
        std::cout << "Enter password: ";
        getchar();
        std::cin.getline(log1.password,10);
        if( !strlen(log1.username) || !strlen(log1.password) )
        {
            std::cout << "Error, unsupported characters" << std::endl;
            system("PAUSE");
            system("CLS");
            return 0;
        }
        std::ifstream fin ("db", std::ios::binary | std::ios::in);
        while(!fin.eof())
        {
            fin.read((char*)&log2 , sizeof(Login));
            if ( strcmp(log1.username,log2.username)==0 )
            {
                std::cout << "User already exists!" << std::endl;
                system("PAUSE");
                system("CLS");
                return 0;
            }
        }
        fin.close();
        std::ofstream fout ("db", std::ios::binary | std::ios::app);
        fout.write((char*)&log1 , sizeof(Login));
        std::cout << "\nSignup sucess" << std::endl;
        fout.close();
        return 1;
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
        std::cout<<"Rollno :";   std::cin>>rollno;
        std::cout<<"Class :";    std::cin>>Class;
        std::cout<<"Name :";     getchar();  std::cin.getline(Name, 20);
        std::cout<<"Marks :";    std::cin>>marks;
        grade=calcgrade(marks,grade);
    }
    void putdata()
    {
        std::cout<< "Rollno : " << rollno << "\t Name : " << Name
            << "\n Marks : " << marks << "\t Grade : " << grade << std::endl;
    }
    int getrno() {  return rollno;    }
} s1, stud ;

int data_append(char* neim)
{
    std::ifstream fi (neim, std::ios::in | std::ios::binary);
    if (!fi)
    {
        return -1;
    }
    std::ofstream fo ("temp.dat", std::ios::out | std::ios::binary);
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
    std::ifstream fi (neim, std::ios::in | std::ios::binary);
    if (!fi)
    {
        std::cout << "No such file in database" << std::endl;
        system("PAUSE");
        return -1;

    }
    std::ofstream file ("temp.dat", std::ios::out | std::ios::binary);
    int rno;    char found = 'f' , confirm = 'n' ;
    std::cout << " Enter rollno of student whose record is to be deleted \n";
    std::cin >> rno;
    while (!fi.eof())
    {
        fi.read((char*)&s1,sizeof(stu));
        if ( s1.getrno() == rno )
        {
            s1.putdata();
            found = 't';
            std::cout << " Are you sure, you want to delete this record? (y/n).. ";
            std::cin>> confirm ;
            if (confirm == 'n')
                file.write((char*)&s1,sizeof(stu));
        }
        else
            file.write((char*)&s1,sizeof(stu));
    }
    if ( found == 'f' )
        std::cout << " Record not found ;__; \n";
    fi.close();    file.close();
    remove(neim);  rename("temp.dat",neim);
    return 0;
}

int data_modify(char* neim)
{
    std::fstream fio(neim, std::ios::in | std::ios::out | std::ios::binary);
    int rno ;   long pos ;  char found = 'f';
    std::cout << " Enter rollno of student whose record is to be modified \n";
    getchar();
    std::cin >> rno;
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
        std::cout << "Now the file contains \n";
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

    std::ifstream fi (neim, std::ios::in | std::ios::binary);
    if (!fi)
    {
        return -1;

    }
    int rno;    char found = 'f' ;
    std::cout << " Enter rollno of student whose record is to be searched \n";
    std::cin >> rno;
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
    std::ifstream tmp1 (Class,std::ios::in);
    if (tmp1)
    {
        std::cout << "Class already exists!!!" << std::endl;
        tmp1.close();
        return -1;
    }
    std::ofstream newclass (Class,std::ios::out);
    newclass.close();
    return 0;
}
int data_remove(char* ClassDel)
{
    std::ifstream tmp1 (ClassDel,std::ios::in);
    if ( !tmp1 )
        return -1;
    tmp1.close();
    remove(ClassDel);
    return 0;
}
int main()
{
    int log;
    while (1)
{
    while(1)
     {  system("cls");
        std::cout << "Login Panel" << std::endl
                        << "1. Login" << std::endl
                        << "2. Sign up" << std::endl;
        std::cin >> log;
        switch(log)
        {
            case 1 :   { log=login();
                        break; }
            case 2 :    { log=signup();
                        break; }
            default : std::cout << "Wrong input" << std::endl;
        }
        if(log==1)
            break;
     }

    system("pause");
    menu:
    system("cls");
    std::cout << "\t\t\t Enter the number to proceed to corresponding operation" << std::endl;
    std::cout
         << "1. Create Class"   << std::endl
         << "2. Append Data"    << std::endl
         << "3. Delete Data"    << std::endl
         << "4. Modify Data"    << std::endl
         << "5. Search Record"  << std::endl
         << "6. Delete Class"   << std::endl
         << "7. Logout"         << std::endl
         << "8. Exit"           << std::endl;
    int *op = new int;
    std::cin >> *op;

    switch (*op)
    {
        case 1 : {  char Class[10];
                    std::cout << "Enter new class name :";
                    getchar();
                    std::cin.getline(Class,10);
                    std::cout << "\nCreating Class files.." << std::endl;
                    *op=data_new(Class);
                    if (*op==(-1))
                    {
                        std::cout << "Class already exists!!!" << std::endl;
                        break;
                    }
                    std::cout << "Class creation successful" << std::endl;
                    system("pause");
                    delete op;
                    break;
                 }
        case 2 : {
                 system("cls");
                 char neim[8];
                 std::cout << "Enter class (use numerals only)";      //implemented for school project
                 getchar();
                 std::cin.getline(neim,8);
                 *op=data_append(neim);
                 if (*op==(-1))
                 {
                    std::cout << "No such file in database" << std::endl;
                    break;
                 }
                 std::ifstream fi(neim, std::ios::in);
                 std::cout << "File now contains : \n";
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
                  std::cout << "Enter class";      //implemented for school project
                  getchar();
                  char neim1[8];
                  std::cin.getline(neim1,8);
                  *op=data_delete(neim1);
                  if (*op==(-1))
                  {
                        std::cout << "No such file in database" << std::endl;
                        system("PAUSE");
                  }
                  std::ifstream fi;
                  fi.open(neim1, std::ios::in);
                  std::cout << "File now contains : \n";
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
                    std::cout << "Enter class (use numerals only)";      //implemented for school project
                    char neim[8];
                    std::cin.getline(neim,8);
                    *op=data_modify(neim);
                    if ( *op==(-1))
                    {
                        std::cout << "Record not found ;__; \n";
                    }
                    delete op;
                    break;
                 }
        case 5 : {
                    std::cout << "Enter class (use numerals only)";      //implemented for school project
                    char neim[8];
                    std::cin.getline(neim,8);
                    *op=data_search(neim);
                    if(*op==(-1))
                    {
                       std::cout << "No such file in database" << std::endl;
                        system("PAUSE");
                    }
                    else if(*op==(-2))
                    {
                        std::cout << "Record not found" << std::endl;
                        system("PAUSE");
                    }
                    delete op;
                    break;
                 }
        case 6 : {
                    char ClassDel[10];
                    std::cout << "Enter class name to be deleted:" << std::endl;
                    std::cin.getline(ClassDel,10);
                    std::cout << "Deleting Class files.." << std::endl;
                    *op=data_remove(ClassDel);
                    if(*op==(-1))
                    {
                     std::cout << "No such class as '" << ClassDel << "'" << std::endl;
                    }
                    delete op;
                    break;
                 }
        case 7 : {
                    delete op;
                    getchar();
                    continue;

                 }
        case 8 : {
                    delete op;
                    break;
                 }
        default : std::cout << "Wrong input!";
    }
}
    system("pause");

    return 0;
}
