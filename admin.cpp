#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include "admin.h"
#include "parts.h"
#undef min
#undef max
using namespace std;

//global variables
extern int ADMCODE;
extern string ADMCODEPATH;
extern string PARTSPATH;
extern string SortType[10];
extern int sortSelected;

bool file_is_empty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

int read_int_input(int lbound, int rbound) //read int to be >= lbound && <= rbound
{
    int input = -1;
    bool valid = false;
    do
    {
        cout << lbound << " - " << rbound << ">" << flush;
        cin >> input;
        if (cin.good() && input >= lbound && input <= rbound)
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!valid);
    return (input);
}

char read_char_input(char lbound, char rbound, short mode) //read char to be >= lbound && <= rbound
{
    char input = '?';
    lbound = tolower(lbound);
    rbound = tolower(rbound);
    if (mode == 0) //a-z 1-9 type
    {
        bool valid = false;
        do
        {
            cout << ">" << flush;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  DEBUG READ AT  FUNC" << endl;
            cin.get(input); 
            input = tolower(input);
            if (input >= lbound && input <= rbound)
            {
                valid = true;
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid);
    }
    else
        if (mode == 1) //Y/N type
        {
            bool valid = false;
            do
            {
                cout << "(" << lbound << "/" << rbound << ")>" << flush;
                cin >> input; input = tolower(input);
                if (cin.good() && input == lbound || input == rbound)
                {
                    valid = true;
                }
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!valid);
        }
    return (input);
}

int GET_ADMIN_CODE() //gets admin code from file
{
	ifstream R(ADMCODEPATH, ios::binary);
    ifstream check(ADMCODEPATH);
	ofstream W;
	int DEFAULT_ADMCODE = 1453;

	if (R.fail() || file_is_empty(check))
	{
		W.open(ADMCODEPATH, ios::binary);
        W.write((char*)&DEFAULT_ADMCODE, sizeof(DEFAULT_ADMCODE));
		W.close();
	}

	R.read((char*)&ADMCODE, sizeof(ADMCODE));
    R.close();
	return ADMCODE;
}

int CHANGE_ADMIN_CODE()
{
    SetConsoleTitle(TEXT("Parts-Catalog V1.0/AdminMenu/ChangePassword"));
    ofstream W;
    int DEFAULT_ADMCODE = 1453;
    int sel = -1;

    system("CLS");
    cout << "**********************" << endl;
    cout << "* ADMIN CODE CHANGE" << endl;
    cout << "**********************" << endl;
    cout << "1. Reset to default (1453)" << endl
        << "2. Enter new code" << endl;
    sel = read_int_input(1, 2);
    switch (sel)
    {
    case 1:
        system("CLS");
        cout << "**********************" << endl;
        cout << "* ADMIN CODE CHANGE" << endl;
        cout << "**********************" << endl;
        W.open(ADMCODEPATH, ios::binary);
        W.write((char*)&DEFAULT_ADMCODE, sizeof(DEFAULT_ADMCODE));
        W.close();
        cout << "Default admin code restored. Re-authorize" << endl;
        Sleep(2000);
        return DEFAULT_ADMCODE;
        break;
    case 2:
        system("CLS");
        cout << "**********************" << endl;
        cout << "* ADMIN CODE CHANGE" << endl;
        cout << "**********************" << endl;
        cout << "Enter new admin code: " << endl;
        sel = read_int_input(0, 999999); 
        W.open(ADMCODEPATH, ios::binary);
        W.write((char*)&sel, sizeof(sel));
        W.close();
        cout << "New admin code set. Re-authorize. " << endl;
        Sleep(2000);
        return sel;
        break;
    }
}