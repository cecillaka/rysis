// rysisapp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include<iomanip>
#include<conio.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int const arraySize = 100;
string surname[arraySize];
string surnameFirst[arraySize];
string name[arraySize];
string temp;

//sorting names function
void bublesort(string arr[], int size) {
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
void numeringNames(string arrSurname[], string arrName[], int size) {
    for (int i = 0;i < size;i++) {
        surnameFirst[i] = to_string(i + 1) + " " + arrSurname[i] + " " + arrName[i];
        cout << surnameFirst[i] << endl;

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
    const int arraySize = 100;
    string  UnsortedNames[arraySize];
    string  sortedNames[arraySize];
    string fileName = "names.txt";
    string line = " ";
    string temp = " ";
    int size = 0;
    // 3.1	App 1 – Read a Text File and Sort Results

    ifstream myfile(fileName);

    if (!myfile) {
        cout << "Unable to open " << fileName << " file " << endl;
        return -1;
    }

    else if (myfile.is_open())
    {
        cout << endl;
        cout << "List of  Names Read From " << fileName << " file  " << endl;
        cout << "---------------------------------------------" << endl;

        while (!myfile.eof()) {
            getline(myfile, line);

            UnsortedNames[size] = line;

            cout << UnsortedNames[size] << endl;

            size++;

        }
        myfile.close();

        // 3 calling  buble sorting function to sort names in alphabetical order

        bublesort(UnsortedNames, size);

        cout << endl;
        cout << "List of Sorted Names" << endl;
        cout << "--------------------" << endl;

        for (int i = 0;i < size;i++) {

            cout << UnsortedNames[i] << endl;

        }

        // 4 calling function to store name and surname into separate arrays
        storeNameSurname(UnsortedNames, size);

        cout << endl;
        cout << "List of  Surname First Then Firstname " << endl;
        cout << "-------------------------------------" << endl;
        // 5 calling numbering Names function

        numeringNames(surname, name, size);

        //------end of question 3.1------

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
