// instructions to run the project.
/*
App 2 instructions
1.	Download and install MySQL Installer at: https://dev.mysql.com/downloads/windows/installer/8.0.html

2. Using MySQL Installer install:
 a. MySQL Community Server 8.0.11
 b. MySQL Connector/C++ version 8.0.11
3. Update the relevant include and lib directories in Visual Studio Community 2019
a. C:\Program Files\MySQL\Connector C++ 1.1\include
b. C:\Program Files\MySQL\MySQL Server 8.0\include
 c. C:\Program Files\MySQL\Connector C++ 1.1\lib\opt
 d. C:\Program Files\MySQL\MySQL Server 8.0\lib
 e. mysqlcppconn.lib
 f. libmysql.lib
4. Code, build, run
a. Copy libmysql.dll from C:\Program Files\MySQL\MySQL Server 8.0\lib to the executable directory
b. Copy libeay32.dll and ssleay32.dll from C:\Program Files\MySQL\MySQL Server 8.0\bin to the executable directory
Check this video on YouTube for more info: https://youtu.be/yNniOHn9Xe0

*/


//3.2	App 2 - Develop a Database App and Read / Write Data
#include <stdlib.h>
#include<iomanip>
#include<conio.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <mysql.h>


using namespace std;
int qstate;
int Sqstate;
//database declaration variables
//---------- copied from youtube
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
//----------end of copied from youtube
string character = "'";
int inserted = 0;
int notInserted = 0;
int const arraySize = 100;
string surname[arraySize];
string surnameFirst[arraySize];
string name[arraySize];
string temp;

//sorting names function
void bublesort(string arr[],int size) {
    for (int i = 0;i < size;i++)
    {
        for (int j = 1;j < size - i;j++)
        {
            if (arr[j - 1] > arr[j])
            {
                temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    
}

//numbering names function and swap name with surname
void numberingNames(string arrSurname[],string arrName[], int s) {

    for (int i = 0;i < s;i++) {
        cout << to_string(i + 1) + " " + arrSurname[i] + " " + arrName[i] << endl;

    }

}

// storing name and surname separate 
void storeNameSurname(string arrUnsortednames[], int size) {
    for (int i = 0;i < size;i++) {
        name[i] = arrUnsortednames[i].substr(0, arrUnsortednames[i].find(" "));
        arrUnsortednames[i] = arrUnsortednames[i].erase(0, arrUnsortednames[i].find(" ") + 1);
        surname[i] = arrUnsortednames[i].substr(0, arrUnsortednames[i].find("\n"));

    }
}


int main()
{
    ifstream infile;
    string  UnsortedNames[arraySize];
    string fileName = "names.txt";
    string line = " ";
    int size = 0;

    ifstream myfile(fileName);
 
   if(!myfile){
        cout << "Unable to open "<< fileName <<" file " << endl;
        return -1;
    }
    
     else if (myfile.is_open())
    {
        while (!myfile.eof()) {
            getline(myfile, line);

            UnsortedNames[size] = line;
            size++;
        }
        myfile.close();

        storeNameSurname(UnsortedNames,size);

        conn = mysql_init(0);
       
        //database configuration settings
        //copied from youtube
        conn = mysql_real_connect(conn, "localhost", "root", "", "test", 3306, NULL, 0);
        //----------end of copied from youtube
        if (conn) {
            puts("Successful connection to database!");
            for (int i = 0; i < size;i++) {
                //copied from youtube
                string query = "select * FROM name where Surname = '" + surname[i] + character;
                const char* q = query.c_str();
                qstate = mysql_query(conn, q);
                res = mysql_store_result(conn);

                if (qstate==0) {
                    row = mysql_fetch_row(res);
                    //----------end of copied from youtube
                    if(row== 0000000000000000){
                        
                        cout << "Inserting "<< surname[i] << endl;
                        inserted++;
                      
                        string bracket = ")";
                        string coma= ",";
                        string singleQ = "'";
                      
                        //insert names inside the database
                        string query1 = "INSERT INTO name (FirstName,Surname) VALUES ('"+name[i]+
                            singleQ+coma+singleQ+surname[i]+singleQ+bracket ;

                        const char* q1 = query1.c_str();
                        //copied from youtube
                        qstate = mysql_query(conn, q1);

                        if (qstate == 0) {
                            
                            cout << "record inserted" << endl;
                      
                        }
                        else
                        {
                            cout << "failed" << endl;
                           
                        }
                        //----------end of copied from youtube

                    }

                    else if(row != 0000000000000000) {
                        
                        cout << " Cannot Insert!! User " << surname[i] << " already Exist!" << endl;
                        notInserted++;
                        
                        
                    }

                    
                }

                
            }
            cout << endl;
            cout << inserted << " rows affected" << endl;
            cout << notInserted << " name(s) couldnot be inserted" << endl;
            //number 6 , fetch the names from the database  
            //,sort names alphabetically,swap name with surname and and add numbering

            string sQuery = "select * FROM name ";
            const char* sq = sQuery.c_str();
            Sqstate = mysql_query(conn, sq);
            string dBFirstname = " ";
            string dBFirstnameArr[arraySize];
            string dBSurname = " ";
            string dBNameArr[arraySize];
            string dBNamesArr[arraySize];
            if (Sqstate == 0) {
                int is = 0;;
                res = mysql_store_result(conn);
                //copied from youtube
                while (row = mysql_fetch_row(res))
                {
                    dBFirstname = row[1];
                    dBSurname = row[2];
                    dBNamesArr[is]= dBFirstname + " " + dBSurname;
                    is++;
                }
                //----------end of copied from youtube
                cout << endl;
                cout << "List of  Names Read From Database sorted aphabetically & numbered  " << endl;
                cout << "--------------------------------------------------------------------" << endl;
                //calling bubble sort function and display list of sorted names alphabetically
                bublesort(dBNamesArr, is);

               // calling this fuction to store name and surname separetely
                storeNameSurname(dBNamesArr, is);

                //calling this function to add numbers to surname and firstname
              
                numberingNames(surname, name, is);

            }

            else
            {
                cout << "Query failed: " << mysql_error(conn) << endl;
            }


        }

        else {
            cout << endl;
            cout << "connection failed check your database configurations" << endl;
        }

    }
     else {
         cout << "Unable to open " << fileName << " file " << endl;
     }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
