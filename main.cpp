#include  <iostream>
#include  <string>
#include  <fstream>
#include  <vector>
#include  <algorithm>
#include <windows.h>
#include "admin.h"
#include "parts.h"
#undef min
#undef max
using namespace std;

//prototypes
void UserMenu();
void AdminMenu();
void SearchMenu();

//global variables
int ADMCODE;
string ADMCODEPATH = "admcode.bin";
string PARTSPATH = "parts.txt"; 
PARTSFUNC PartsClass;
string SortType[11] = { "Alphabet A->Z", "Alphabet Z->A", "Manufacturer A->Z", "Manufacturer Z->A",
	"Amount per supply ascending", "Amount per supply descending", "Price per supply ascending", 
	"Price per supply descending", "Quality ascending", "Quality descending", "No order selected"};
int sortSelected = 0;

//search menu
void SearchMenu()
{
	int action = -1;
	string searchQuery;
	sortSelected = 0;
	while (action != 0)
	{
		system("CLS");
		PartsClass.displayFound();
		cout << "SEARCH QUERY" << endl;
		cout << endl << "************************" << endl;
		cout << "Choose your action: " << endl;
		cout << "1. Set part name" << endl;
		if (!PartsClass.is_empty())
		{
			cout << "2. Set sort mode" << endl;
			cout << "3. More details for offer" << endl;
		}
		cout << "0. Back to user menu" << endl;
		
		if (PartsClass.is_empty())
		{
			action = read_int_input(0, 1);
		}
		else
			if(!PartsClass.is_empty())
		{
			action = read_int_input(0, 3);
		}
		switch (action)
		{
		case 1:
			cout << "Search for:" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, searchQuery);
			while (searchQuery == "")
			{
				getline(cin, searchQuery);
			}
			PartsClass.search(searchQuery);
			action = -1;
			break;
		case 2:
			PartsClass.selectSort(1);
			action = -1;
			break;
		case 3:
			PartsClass.contactCompanies();
			action = 0;
			break;
		case 0:
			cout << "Returning to user..." << endl;
			Sleep(2000);
			action = -1;
			return;
			break;
		default:
			cout << "ERROR: Input out of bounds" << endl;
			action = -1;
			break;
		}
	}
	return;
}

//admin panel
void AdminMenu()
{
	int action = -1;
	while (action != 0)
	{
		PartsClass.DisplayAllParts();
		cout << "ADMIN INTERFACE" << endl;
		cout << "************************" << endl;
		cout << "Choose your action: " << endl;
		cout << "1. Add new part" << endl;
		cout << "2. Edit part" << endl;
		cout << "3. Generate instances" << endl;
		cout << "4. Remove part" << endl;
		cout << "5. Change password" << endl;
		cout << "************************" << endl;
		cout << "6. Sort parts" << endl;
		cout << "0. Logout" << endl;
		//cout << "  DEBUG READ AT  ADMINMENU" << endl;
		action = read_int_input(0, 6);
		switch (action)
		{
		case 0:
			cout << "Returning to user..." << endl;
			Sleep(2000);
			action = -1;
			return;
			break;
		case 1:
			PartsClass.addPartManually();
			action = -1;
			break;
		case 2:
			PartsClass.editPart();
			action = -1;
			break;
		case 3:
			PartsClass.fillRandom();
			action = -1;
			break;
		case 4:
			PartsClass.removePart();
			action = -1;
			break;
		case 5:
			ADMCODE = CHANGE_ADMIN_CODE();
			action = -1;
			return;
			break;
		case 6:
			
			PartsClass.selectSort(0);
			action = -1;
			break;
		default:
			cout << "ERROR: Input out of bounds" << endl;
			action = -1;
			break;
		}
	}
	return;
}

//menu sequence
void UserMenu()
{
	int action = -1;
	int tries = 5;
	int guess = 0000;
	while (action != 0)
	{
		system("CLS");
		PartsClass.DisplayAllParts();
		cout << "WELCOME, USER" << endl;
		cout << endl << "************************" << endl;
		cout << "Choose your action: " << endl;
		cout << "1. Login as admin" << endl;
		cout << "2. Search deals" << endl;
		cout << "3. Set sort mode" << endl;
		cout << "0. Exit program" << endl;
		//cout << "  DEBUG READ AT  USERMENU" << endl;
		action = read_int_input(0, 3);
		switch (action)
		{
		case 1:
			while (tries != 0)
			{
				system("CLS");
				cout << "Enter admcode (" << tries << " attemps left): " << endl;
				guess = read_int_input(0, 999999);
				if (guess != ADMCODE)
				{
					tries--;
				}
				else
					if (ADMCODE == guess)
					{
						AdminMenu();
						tries = 5;
						action = -1;
						break;
					}
			}
			if (tries == 0)
			{
				PartsClass.DisplayAllParts();
				cout << "Attempts left: 0" << endl << "Too many fails!" << endl;
			}
			Sleep(2000);
			action = -1;
			break;
		case 2:
			SearchMenu();
			tries = 5;
			action = -1;
			break;
		case 3:
			PartsClass.selectSort(0);
			tries = 5;
			action = -1;
			break;
		case 0:
			PartsClass.writePartsToFile();
			cout << "Thanks for using Parts-Catalogue!" << endl;
			exit(EXIT_SUCCESS);
			return;
			break;
		}

	}
	return;
}

//main
int main()
{
	SetConsoleTitle(TEXT("Parts-Catalog V1.0"));
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1600, 900, TRUE);
	system("mode 650");
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	ADMCODE = 1453;
	//loading sequence
	cout << "************************" << endl;
	cout << "*                      *" << endl;
	cout << "*                      *" << endl;
	cout << "* PARTS-CATALOGUE V1.0 *" << endl;
	cout << "*                      *" << endl;
	cout << "*                      *" << endl;
	cout << "************************" << endl;
	Sleep(2000);
	system("CLS");
	UserMenu();
}