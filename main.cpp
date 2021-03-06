#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <process.h>
#include <cstring>

class Login
{
public:
    char username[10], password[10];

} log1,log2;

int login()
{
    std::cout << "\t\t\t ..::Login Panel::.." << std::endl;
    std::cin.sync();
    std::cout << "Enter username: ";
    std::cin.getline(log1.username,10);
    std::cout << "Enter password: ";
    std::cin.getline(log1.password,10);
    std::ifstream fin ("db", std::ios::binary | std::ios::in);
    if (!fin)
        return -1;
    while(!fin.eof())
    {
        fin.read((char*)&log2, sizeof(Login));
        if (strcmp(log1.username,log2.username)==0 && strcmp(log1.password,log2.password)==0)
        {
            fin.close();
            return 0;
        }

    }
    fin.close();
    return -2;      //  Wrong Credentials :(
}
int signup()
{
    std::cout << "\t\t\t Signup Panel" << std::endl;
    std::cout << "Enter username: ";
    std::cin.sync();
    std::cin.getline(log1.username,10);
    std::cout << "Enter password: ";
    std::cin.sync();
    std::cin.getline(log1.password,10);
    if( !strlen(log1.username) || !strlen(log1.password) )
        return -1;
    std::ifstream fin ("db", std::ios::binary | std::ios::in);
    if (fin)
        while(!fin.eof())
        {
            fin.read((char*)&log2, sizeof(Login));
            if ( strcmp(log1.username,log2.username)==0 )
                return -2;
        }
    fin.close();
    std::ofstream fout ("db", std::ios::binary | std::ios::app);
    fout.write((char*)&log1, sizeof(Login));
    fout.close();
    return 0;
}

/*___________________________________________________________________________________
                            Student Functions from here
  ___________________________________________________________________________________
*/
class stu
{
    int rollno;
    char Name[20];
    char Class[4];
    float marks;
    char grade;
    char calcgrade(float t1, char t2)
    {
        if (t1 >= 75)
            t2='A';
        else if (t1 >= 60)
            t2 = 'B';
        else if (t1 >= 50)
            t2 = 'C';
        else if (t1 >= 40)
            t2 = 'D';
        else
            t2 = 'E' ;
        return t2;
    }

public:
    void getdata()
    {
        int flag=0;
        do
        {
            std::cout<<"Rollno :";
            std::cin.sync();
            std::cin>>rollno;
            std::cout<<"Class :";
            std::cin.sync();
            std::cin>>Class;
            std::cout<<"Name :";
            std::cin.sync();
            std::cin.getline(Name, 20);
            std::cout<<"Marks :";
            std::cin.sync();
            std::cin>>marks;
            grade=calcgrade(marks,grade);
            if( !strlen(Name) || !strlen(Class) )                            // lets check for empty strings
            {
                std::cout << "Invalid name or class, try again" << std::endl;
                flag=1;
                system("PAUSE");
                system("CLS");
            }
        }
        while(flag);

    }
    void putdata()
    {
        std::cout << "Rollno : " << rollno << "\tName : " << Name
                  << "\nMarks : " << marks << "\tGrade : " << grade
                  << std::endl;
    }
    int getrno()
    {
        return rollno;
    }
    void setRNO(int a)
    {
        rollno = a;
    }
} s1, stud ;

int data_append(char* neim)
{
    std::fstream fi (neim, std::ios::binary | std::ios::in);
    if (!fi)
    {
        return -1;
    }
    std::cout << "Enter details of student whose record is to be inserted" << std::endl;
    s1.getdata();
    fi.seekg(0, std::ios::beg);
    while(!fi.eof())
    {
        fi.read((char*)&stud,sizeof(stu));
        if(stud.getrno()==s1.getrno())
        {
            std::cout << "Student with same roll number already exists" << std::endl;
            system("PAUSE");
            system("CLS");
            fi.close();
            return -2;
        }
    }
    fi.close();
    fi.open(neim, std::ios::out | std::ios::binary | std::ios::app);
    fi.write((char*)&s1,sizeof(stu));
    fi.close();
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
    int rno;
    char found = 'f', confirm = 'n' ;
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
            if (((confirm == 'n') || (confirm == 'N') ) && (s1.getrno()!=-1))
                file.write((char*)&s1,sizeof(stu));
        }
        else if(s1.getrno()!=-1)
            file.write((char*)&s1,sizeof(stu));
        s1.setRNO(-1);
    }
    if ( found == 'f' )
        std::cout << " Record not found ;__; \n";
    fi.close();
    file.close();
    remove(neim);
    rename("temp.dat",neim);
    return 0;
}
int data_modify(char* neim)
{
    std::ifstream check (neim, std::ios::in);
    if (!check)
    {
        return -2;
    }
    std::fstream fio(neim, std::ios::in | std::ios::out | std::ios::binary);
    int rno ;
    long pos ;
    char found = 'f', option;
    std::cout << " Enter rollno of student whose record is to be modified \n";
    std::cin.sync();
    std::cin >> rno;
    while ( !fio.eof())
    {
        pos = fio.tellg();
        fio.read((char*)&s1, sizeof(stu));
        if ( s1.getrno() == rno )
        {
            std::cout << "Modify? (y/n)" << std::endl;
            s1.putdata();
            std::cout << "\n:";
            std::cin >> option;
            if((option == 'n') || (option == 'N'))
                break;
            else
            {
                std::cout << "Enter new details :" << std::endl;
                s1.getdata();
            }
            fio.seekg(pos);
            fio.write((char*)&s1, sizeof(stu));
            found = 't';
            break;
        }
    }
    if ( found == 'f')
        return -1;
    fio.seekg(0);
    return 0;
}
int data_search(char* neim)
{

    std::ifstream fi (neim, std::ios::in | std::ios::binary);
    if (!fi)
    {
        return -1;
    }
    int rno;
    char found = 'f' ;
    std::cout << " Enter roll no of student whose record is to be searched \n";
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
void show_students(char* neim)
{
    std::ifstream fi;
    fi.open(neim, std::ios::in);
    if(!fi)
    {
        std::cout << "No database found" << std::endl;
        return;
    }
    std::cout << "File now contains : \n";
    while (!fi.eof())
    {
        fi.read((char*)&s1, sizeof(stu));
        if (fi.eof())
            break;
        s1.putdata();
    }
    fi.close();
    system("pause");
}
/*___________________________________________________________________________________
                            Staff Functions from here
  ___________________________________________________________________________________
*/
class teacher
{
    uint32_t empno;
    char Name[20];
    char role[4];
    float salary;
    float calcsal(char* post)
    {
        if (strcmpi(post,"PGT")==0)
            return 80000;
        if (strcmpi(post,"TGT")==0)
            return 60000;
        if (strcmpi(post,"PRT")==0)
            return 40000;
        if (strcmpi(post,"OT")==0)
            return 20000;
        return 15000;
    }
public:
    void getstaff()
    {
        int flag=0;
        do
        {
            std::cout<<"Empno. :";
            std::cin.sync();
            std::cin>>empno;
            std::cout<<"Role :";
            std::cin.sync();
            std::cin>>role;
            std::cout<<"Name :";
            std::cin.sync();
            std::cin.getline(Name, 20);
            salary=calcsal(role);
            if( !strlen(Name) || !strlen(role) )                              // lets check for empty strings
            {
                std::cout << "Invalid name or role, try again" << std::endl;
                flag=1;
                system("PAUSE");
                system("CLS");
            }
        }
        while(flag);
    }
    void putstaff()
    {
        std::cout << "Empno : " << empno
                  << "\nName : " << Name << "\tSalary : " << salary
                  << std::endl;
    }
    int getID()
    {
        return empno;
    }
    void setID(int a)
    {
        empno = a;
    }
} e1, emp ;

int staff_append()
{
    std::fstream fi ("staff", std::ios::binary | std::ios::in);
    if (!fi)
    {
        std::cout << "No file, creating file..." << std::endl;
    }
    std::cout << "Enter details of student whose record is to be inserted" << std::endl;
    e1.getstaff();
    fi.seekg(0, std::ios::beg);
    while(!fi.eof())
    {
        fi.read((char*)&emp,sizeof(teacher));
        if(emp.getID()==e1.getID())
        {
            std::cout << "Student with same roll number already exists" << std::endl;
            system("PAUSE");
            system("CLS");
            fi.close();
            return -2;
        }
    }
    fi.close();
    fi.open("staff", std::ios::out | std::ios::binary | std::ios::app);
    fi.write((char*)&e1,sizeof(teacher));
    fi.close();
    return 0;
}

int staff_delete()
{
    std::ifstream fi ("staff", std::ios::in | std::ios::binary);
    if (!fi)
    {
        std::cout << "No such file in staff-base" << std::endl;
        system("PAUSE");
        return -1;
    }
    std::ofstream file ("temp.dat", std::ios::out | std::ios::binary);
    int rno;
    char found = 'f', confirm = 'n' ;
    std::cout << " Enter Emp No. of staff whose record is to be deleted \n";
    std::cin >> rno;
    while (!fi.eof())
    {
        fi.read((char*)&e1,sizeof(teacher));
        if ( e1.getID() == rno )
        {
            e1.putstaff();
            found = 't';
            std::cout << " Are you sure, you want to delete this record? (y/n).. ";
            std::cin>> confirm ;
            if (((confirm == 'n') || (confirm == 'N') ) && (e1.getID()!=-1))
                file.write((char*)&e1,sizeof(teacher));
        }
        else if(e1.getID()!=-1)
            file.write((char*)&e1,sizeof(teacher));
        e1.setID(-1);
    }
    if ( found == 'f' )
        std::cout << " Record not found ;__; \n";
    fi.close();
    file.close();
    remove("staff");
    rename("temp.dat","staff");
    return 0;
}

int staff_modify()
{
    std::ifstream check ("staff", std::ios::in);
    if (!check)
    {
        return -2;
    }
    std::fstream fio("staff", std::ios::in | std::ios::out | std::ios::binary);
    int rno ;
    long pos ;
    char found = 'f', option;
    std::cout << " Enter empno of staff whose record is to be modified \n";
    std::cin >> rno;
    while ( !fio.eof())
    {
        pos = fio.tellg();
        fio.read((char*)&e1, sizeof(teacher));
        if ( e1.getID() == rno )
        {
            std::cout << "Modify? (y/n)" << std::endl;
            e1.putstaff();
            std::cout << "\n:";
            std::cin >> option;
            if((option == 'n') || (option == 'N'))
                break;
            else
            {
                std::cout << "Enter new details :" << std::endl;
                e1.getstaff();
            }
            fio.seekg(pos);
            fio.write((char*)&e1, sizeof(teacher));
            found = 't';
            break;
        }
    }
    if ( found == 'f')
        return -1;
    return 0;
}

int staff_search()
{

    std::ifstream fi ("staff", std::ios::in | std::ios::binary);
    if (!fi)
    {
        return -1;
    }
    int rno;
    char found = 'f' ;
    std::cout << " Enter empno of staff whose record is to be searched \n";
    std::cin >> rno;
    while (!fi.eof())
    {
        fi.read((char*)&e1,sizeof(teacher));
        if ( e1.getID() == rno )
        {
            e1.putstaff();
            found = 't';
            fi.close();
            system("PAUSE");
        }
    }
    if ( found == 'f' )
        return -2;
    return 0;
}

void show_staff()
{
    std::ifstream fi;
    fi.open("staff", std::ios::in);
    if(!fi)
    {
        std::cout << "No staff-base found" << std::endl;
        system("pause");
        return;
    }
    std::cout << "File now contains : \n";
    while (!fi.eof())
    {
        fi.read((char*)&emp, sizeof(teacher));
        if (fi.eof())
            break;
        emp.putstaff();
    }
    fi.close();
    system("pause");
}
int main()
{
    std::cout << " ___________________________________________________________________________________" << std::endl;
    std::cout << "|_____________________________School Management___________________________________|" << std::endl;
    std::cout << "|_________________________________________________________________________________|" << std::endl;
    system("pause");
    int option;
    do
    {
        system("cls");
        std::cout << "|                                 Login Menu                                      |" << std::endl;
        std::cout << "Choose your option:" << std::endl
                  << "\t 1. Login "  << std::endl
                  << "\t 2. Signup " << std::endl
                  << "\t 3. Exit "   << std::endl
                  << "Option: "  << std::endl;
        std::cin >> option;
        switch (option)
        {
        case 1 :
            option=login();
            if(option==-1)
            {
                std::cout<< "Database cannot be accessed!" << std::endl;
                system("pause");
                system("cls");
            }
            else if(option==-2)
            {
                std::cout<< "Wrong credentials!" << std::endl;
                system("pause");
            }
            else if(option==0)
            {
                std::cout<< "Logged in!" << std::endl;
                system("pause");
                system("cls");
            }
            else
            {
                std::cout<< "Unknown error! Aborting..." << std::endl;      // Just in case something goes wrong :3
                exit(-1);
            }
            break;
        case 2 :
            option=signup();
            if(option==-1)
            {
                std::cout << "Error, unsupported characters" << std::endl;
                system("pause");
                system("cls");
            }
            else if(option==-2)
            {
                std::cout << "User already exists!" << std::endl;
                system("pause");
                system("cls");
            }
            else if(option==0)
            {
                std::cout<< "Signed Up!" << std::endl;
                system("pause");
                system("cls");
                break;
            }
            else
            {
                std::cout<< "Unknown error! Aborting..." << std::endl;      // Just in case something goes wrong :3
                exit(-1);
            }
            break;
        case 3 :
            exit(0);
        default :
            std::cout<< "Wrong choice!" << std::endl;
            option=1;
            break;
        }

    }
    while (option!=0);
    do
    {
        system("cls");
        std::cout << "|                                 Selection Menu                                      |" << std::endl;
        std::cout << "Choose your option:" << std::endl
                  << "\t 1. Student "  << std::endl
                  << "\t 2. Staff " << std::endl
                  << "\t 3. Exit "   << std::endl
                  << "Option: "  << std::endl;
        std::cin >> option;
        switch (option)
        {
        case 1 :
            int op;
            char neim[8];
            do
            {
                system("cls");
                std::cout << "\t\t\t Enter the number to proceed to corresponding operation" << std::endl;
                std::cout
                        << "1. Create Class"   << std::endl
                        << "2. Show records"   << std::endl
                        << "3. Append Data"    << std::endl
                        << "4. Delete Data"    << std::endl
                        << "5. Modify Data"    << std::endl
                        << "6. Search Record"  << std::endl
                        << "7. Delete Class"   << std::endl
                        << "8. Exit"           << std::endl;
                std::cin >> op;
                switch (op)
                {
                case 1 :
                    char Class[10];
                    std::cout << "Enter new class name :";
                    std::cin.sync();
                    std::cin.getline(Class,10);
                    std::cout << "\nCreating Class file.." << std::endl;
                    op=data_new(Class);
                    if (op==(-1))
                    {
                        std::cout << "Class already exists!!!" << std::endl;
                        break;
                    }
                    std::cout << "Class creation successful" << std::endl;
                    system("pause");
                    option=1;
                    break;
                case 2 :
                    system("cls");
                    std::cout << "Enter class";
                    std::cin.sync();
                    std::cin.getline(neim,8);
                    show_students(neim);
                    option=1;
                    break;
                case 3 :
                    system("cls");
                    std::cout << "Enter class";
                    std::cin.sync();
                    std::cin.getline(neim,8);
                    op=data_append(neim);
                    if (op==(-1))
                    {
                        std::cout << "No such file in database" << std::endl;
                        system("PAUSE");
                        option=1;
                        break;
                    }
                    show_students(neim);
                    option=1;
                    break;
                case 4 :
                    std::cout << "Enter class";
                    std::cin.sync();
                    char neim1[8];
                    std::cin.getline(neim1,8);
                    op=data_delete(neim1);
                    if (op==(-1))
                    {
                        std::cout << "No such file in database" << std::endl;
                        system("PAUSE");
                    }
                    show_students(neim);
                    option=1;
                    break;
                case 5 :
                    std::cout << "Enter class (use numerals only)";
                    std::cin.sync();
                    std::cin.getline(neim,8);
                    op=data_modify(neim);

                    if ( op==(-1))
                        std::cout << "Record not found ;__;" << std::endl;
                    if ( op==(-2))
                    {
                        std::cout << "No class data base \n";
                    }
                    option=1;
                    system("pause");
                    break;
                case 6 :
                    std::cout << "Enter class (use numerals only)";
                    std::cin.sync();
                    std::cin.getline(neim,8);
                    op=data_search(neim);
                    if(op==(-1))
                    {
                        std::cout << "No such file in database" << std::endl;
                        system("PAUSE");
                    }
                    else if(op==(-2))
                    {
                        std::cout << "Record not found" << std::endl;
                        system("PAUSE");
                    }
                    option=1;
                    system("PAUSE");
                    break;
                case 7 :
                    char ClassDel[10];
                    std::cout << "Enter class name to be deleted:" << std::endl;
                    std::cin.sync();
                    std::cin.getline(ClassDel,10);
                    std::cout << "Deleting Class files.." << std::endl;
                    op=data_remove(ClassDel);
                    if(op==(-1))
                    {
                        std::cout << "No such class as '" << ClassDel << "'" << std::endl;
                        system("PAUSE");
                    }
                    option=1;
                    break;
                case 8 :
                    exit(0);
                default :
                    std::cout << "Wrong input!";
                    system("PAUSE");
                    option=1;

                }

            }
            while(option!=0);
            break;
        case 2 :
            while (1)
            {
                system("pause");
                system("cls");
                std::cout << "\t\t\t Enter the number to proceed to corresponding operation" << std::endl;
                std::cout
                        << "1. Show Data"      << std::endl
                        << "2. Append Data"    << std::endl
                        << "3. Delete Data"    << std::endl
                        << "4. Modify Data"    << std::endl
                        << "5. Search Data"    << std::endl
                        << "6. Exit"           << std::endl;
                int op;
                std::cin >> op;

                switch (op)
                {
                case 1 :
                {
                    system("cls");
                    show_staff();
                    system("PAUSE");
                    continue;
                }
                case 2 :
                {
                    system("cls");
                    op=staff_append();
                    if (op==(-1))
                    {
                        std::cout << "No file in staff-base" << std::endl;
                        break;
                    }
                    show_staff();

                    continue;
                }
                case 3 :
                {
                    op=staff_delete();
                    if (op==(-1))
                    {
                        std::cout << "No file in staff-base" << std::endl;
                        system("PAUSE");
                    }

                    continue;
                }
                case 4 :
                {
                    op=staff_modify();
                    if ( op==(-1))
                    {
                        std::cout << "Record not found ;__; \n";
                    }
                    if ( op==(-2))
                    {
                        std::cout << "No staff data base \n";
                    }
                    show_staff();

                    continue;
                }
                case 5 :
                    op=staff_search();
                    if(op==(-1))
                    {
                        std::cout << "No file in staff-base" << std::endl;
                        system("PAUSE");
                    }
                    else if(op==(-2))
                    {
                        std::cout << "Record not found" << std::endl;
                        system("PAUSE");
                    }
                    break;

                case 6 :
                    exit(0);

                default :
                    std::cout << "Wrong input!";
                    option=1;
                    break;
                }
            }
            break;
        case 3 :
            exit(0);
        default :
            std::cout<< "Wrong choice!" << std::endl;
            option=1;
            break;
        }
    }
    while (option!=0);
}
