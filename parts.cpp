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


PARTSFUNC::PARTSFUNC()
{
    ALLPARTS = readPartsFromFile();
    sortNamesAZ(0);
    FOUNDPARTS = {};
}
PARTSFUNC::~PARTSFUNC()
{

}
void addSpaces(int current, int step)
{
    int maxSymbols[6] = { 8, 26, 26, 26, 26, 26 };
    int amount = maxSymbols[step] - current;
    //int maxParts = 18;
    //int maxCompany = 26;
    //int maxAmount = 19;
    //int maxPrice = 18;
    //int maxQuality = 16;

    for (int i = 0; i < amount; i++)
    {
        cout << ' ';
    }
    return;
}

void PARTSFUNC::DisplayContents(PARTS singlePart)
{
    //cout << singlePart.name << " by " << singlePart.manufacturer <<
    //    ", " << singlePart.qualityOption[singlePart.quality] << " quality, " << singlePart.amount << "x for "
    //    << singlePart.price << "$ *" << endl;

    string temp;
    int length;
    for (int i = 1; i < 6; i++)
    {
        switch (i)
        {
        case 1:
            temp = "| ";
            temp += singlePart.name;
            length = temp.length();
            cout << temp;
            addSpaces(length, i);
            break;
        case 2:
            temp = "| ";
            temp += singlePart.manufacturer;
            length = temp.length();
            cout << temp;
            addSpaces(length, i);
            break;
        case 3:
            temp = "| ";
            temp += to_string(singlePart.amount);
            temp += "x";
            length = temp.length();
            cout << temp;
            addSpaces(length, i);
            break;
        case 4:
            temp = "| ";
            temp += to_string(singlePart.price);
            temp += "$";
            length = temp.length();
            cout << temp;
            addSpaces(length, i);
            break;
        case 5:
            temp = "| ";
            temp += singlePart.qualityOption[singlePart.quality];
            temp += " quality";
            length = temp.length();
            cout << temp;
            addSpaces(length, i);
            cout << '|';
            break;

        }
    }
    cout << endl;
    return;
}
void PARTSFUNC::DisplayAllParts()
{
    if (ALLPARTS.empty())
    {
        cout << "| There are no parts. Tech support is working on it. |" << endl;
        cout << "**********************" << endl;
        return;
    }
    system("CLS");
    ALLPARTS = readPartsFromFile();
    int PARTSIZE = ALLPARTS.size();
    cout << "*******************************************************************************************************************************************" << endl;
    cout << "* SORT MODE: " << SortType[sortSelected] << " *" << endl;
    cout << "* PARTS CATALOGUE   *" << endl;
    cout << "|  NUM  |        PART NAME        |       COMPANY NAME      |     AMOUNT / SUPPLY     |      PRICE / SUPPLY     |       PART QUALITY      |" << endl;

    for (int i = 0; i < ALLPARTS.size(); i++)
    {
        string temp; int length;
        temp = "| ";
        temp += to_string(i);
        length = temp.length();
        cout << temp;
        addSpaces(length, 0);
        PARTSFUNC::DisplayContents(ALLPARTS[i]);


    }
    cout << "*******************************************************************************************************************************************" << endl;

    return;
}
void PARTSFUNC::DisplayMidProcess(PARTS temp, string processName)
{
    //system("CLS");
    //cout << "**********************" << endl;
    //cout << "* " << processName << " *" << endl;
    //cout << "**********************" << endl;
    //cout << "Name: " << temp.name << endl;
    //cout << "Manufacturer: " << temp.manufacturer << endl;
    //cout << "Amount per supply: " << temp.amount << endl;
    //cout << "Price per supply: " << temp.price << endl;
    //cout << "Part quality: " << temp.qualityOption[temp.quality] << endl;
    //return;

    system("CLS");
    cout << "*******************************************************************************************************************************************" << endl;
    cout << "* " << processName << " *" << endl;
    cout << "*******************************************************************************************************************************************" << endl;
    cout << "|        PART NAME        |       COMPANY NAME      |     AMOUNT / SUPPLY     |      PRICE / SUPPLY     |       PART QUALITY      |" << endl;
    PARTSFUNC::DisplayContents(temp);
    return;
}
vector<PARTS> PARTSFUNC::readPartsFromFile()
{
    vector<PARTS> readVect;
    ifstream R(PARTSPATH);
    PARTS buf;
    string temp;
    while (getline(R, temp))
    {
        R >> buf.name >> buf.manufacturer >> buf.amount >> buf.price >> buf.quality;
        readVect.push_back(buf);
    }
    R.close();
    return readVect;
}
void PARTSFUNC::writePartsToFile()
{
    int partsSize = ALLPARTS.size();
    ofstream W(PARTSPATH);
    for (int i = 0; i < partsSize; i++)
    {
        PARTS buf = ALLPARTS[i];
        W << endl << buf.name << ' ' << buf.manufacturer << ' '
            << buf.amount << ' ' << buf.price << ' '
            << buf.quality;
    }
    return;
}
void PARTSFUNC::addPartManually()
{
    PARTS newPart;
    int cntr = 0;
    ofstream W;
    string adding = "ADD NEW PART";
    while (cntr < 7)
    {
        PARTSFUNC::DisplayMidProcess(newPart, adding);
        switch (cntr)
        {
        case 0:
            cout << "Enter name: "; cin >> newPart.name;
            break;
        case 1:
            cout << "Enter manufacturer: "; cin >> newPart.manufacturer;
            break;
        case 2:
            cout << "Enter amount per supply: ";  newPart.amount = read_int_input(0, 999999);
            break;
        case 3:
            cout << "Enter price per supply: "; newPart.price = read_int_input(0, 999999);
            break;
        case 4:
            cout << "Enter part quality: " << endl;
            newPart.quality = read_int_input(1, 4);
            break;
        case 5:
            cout << "Add new part: are you sure?";
            char temp;
            temp = read_char_input('y', 'n', 1);
            if (temp == 'n')
            {
                cout << "Add new part: process cancelled." << endl;
                Sleep(2000);
                return;
                break;
            }
            ALLPARTS.push_back(newPart);
            W.open(PARTSPATH, std::ios::app);
            W << endl << newPart.name << ' ' << newPart.manufacturer << ' '
                << newPart.amount << ' ' << newPart.price << ' ' << newPart.quality;
            W.close();
            break;
        case 6:
            cout << newPart.name << ": added to the database." << endl;
            sortNamesAZ(0);
            Sleep(2000);
            return;
            break;
        }
        cntr++;
    }
    return;

}
vector<PARTS> PARTSFUNC::editPart()
{
    if (ALLPARTS.empty())
    {
        cout << "ERROR: There are no parts in database to edit" << endl;
        Sleep(2000);
        return ALLPARTS;
    }
    PARTS editPart;
    int cntr = 0;
    int sel = -1;
    int partsSize = ALLPARTS.size() - 1;
    bool repeat = true;
    string editing = "EDIT PART";

    PARTSFUNC::DisplayAllParts();
    cout << "Select part to edit: " << endl;
    sel = read_int_input(0, partsSize);
    editPart = ALLPARTS[sel];
    cout << "  DEBUG   " << editPart.name << endl;
    while (cntr < 7)
    {
        PARTSFUNC::DisplayMidProcess(editPart, editing);
        switch (cntr)
        {
        case 0:
            cout << "Edit name: "; cin >> editPart.name;
            break;
        case 1:
            cout << "Edit manufacturer: "; cin >> editPart.manufacturer;
            break;
        case 2:
            cout << "Edit amount per supply: "; editPart.amount = read_int_input(0, 999999);
            break;
        case 3:
            cout << "Edit price per supply: "; editPart.price = read_int_input(0, 999999);
            break;
        case 4:
            cout << "Edit part quality (range 1-4): "; editPart.quality = read_int_input(1, 4);
            break;
        case 5:
            cout << "Edit part: are you sure?";
            char temp;
            temp = read_char_input('y', 'n', 1);
            if (temp == 'n')
            {
                cout << "Edit part: process cancelled." << endl;
                Sleep(2000);
                return ALLPARTS;
                break;
            }
            ALLPARTS[sel] = editPart;
            sortNamesAZ(0);
            break;
        case 6:
            cout << editPart.name << ": edit successful." << endl;
            Sleep(2000);
            break;
        }
        cntr++;
    }
    return ALLPARTS;
}
vector<PARTS> PARTSFUNC::removePart()
{

    if (ALLPARTS.empty())
    {
        cout << "ERROR: There are no parts in database to remove" << endl;
        Sleep(2000);
        return ALLPARTS;
    }
    vector<PARTS> tempvec;
    int partsSize = ALLPARTS.size();
    int sel = -1;
    bool repeat = true;
    string removing = "REMOVE PART";
    string removed;

    PARTSFUNC::DisplayAllParts();

    cout << "Select part to remove: " << endl;
    sel = read_int_input(0, partsSize - 1);
    removed = ALLPARTS[sel].name;

    PARTSFUNC::DisplayMidProcess(ALLPARTS[sel], removing);
    cout << "Remove part: are you sure?";
    char temp;
    temp = read_char_input('y', 'n', 1);
    if (temp == 'n')
    {
        cout << "Remove part: process cancelled." << endl;
        Sleep(2000);
        return ALLPARTS;
    }

    for (int i = 0; i < partsSize; i++)
    {
        if (i != sel)
        {
            tempvec.push_back(ALLPARTS[i]);
        }
    }
    ALLPARTS = tempvec;
    writePartsToFile();
    cout << removed << ": removed successfuly." << endl;
    Sleep(2000);

    return ALLPARTS;
}
void PARTSFUNC::selectSort(int mode)
{
    int sel;
    system("cls");
    cout << "Select sort mode: " << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i + 1 << ". " << SortType[i] << endl;
    }
    sel = read_int_input(1, 10);
    switch (sel)
    {
    case 1:
        sortNamesAZ(mode);
        break;
    case 2:
        sortNamesZA(mode);
        break;
    case 3:
        sortManuAZ(mode);
        break;
    case 4:
        sortManuZA(mode);
        break;
    case 5:
        sortAmountAZ(mode);
        break;
    case 6:
        sortAmountZA(mode);
        break;
    case 7:
        sortPriceAZ(mode);
        break;
    case 8:
        sortPriceZA(mode);
        break;
    case 9:
        sortQualityAZ(mode);
        break;
    case 10:
        sortQualityZA(mode);
        break;
    }
    return;
}
void PARTSFUNC::fillRandom()
{
    int amount;
    string partsNames[19] = { "Copper", "Scrap", "Electronics",
    "Wire", "Ore", "Coal",
    "Plastic", "Lead", "Metals",
    "Composite", "Oil", "Wood",
    "Planks" , "Wool", "Cloth",
    "Chemicals", "Minerals", "Glass",
    "Microcomponents" };
    string companyNames[21] = { "Silot", "Sectory", "Ultrade",
        "Unione", "Secctrade", "Promotech",
        "BusinessPlus", "WireCommerce", "Idustry",
        "Tradept", "Marketics", "Commercore",
        "Sectories", "InnovativeProductionCO", "Machinic",
        "Tooling", "MFactory", "Supplier.ly",
        "Accultery", "PFactory", "Automaking" };

    cout << "Enter amount of parts to generate: ";
    amount = read_int_input(10, 500);

    ofstream W(PARTSPATH, std::ios::app);
    ofstream Wclear;
    Wclear.open(PARTSPATH, std::ofstream::out | std::ofstream::trunc);
    Wclear.close();
    for (int i = 0; i < amount; i++)
    {
        PARTS genPart;
        //RMIN + ( rand() % ( RMAX - RMIN + 1 ) )
        int partName = 0 + (rand() % (18 - 0 + 1));
        genPart.name = partsNames[partName];
        int companyName = 0 + (rand() % (20 - 0 + 1));
        genPart.manufacturer = companyNames[companyName];
        int partAmount = 10 + (rand() % (2000 - 10 + 1));
        genPart.amount = partAmount;
        int partPrice = 50 + (rand() % (10000 - 50 + 1));
        genPart.price = partPrice;
        int partQuality = 1 + (rand() % (4 - 1 + 1));
        genPart.quality = partQuality;

        W << endl << genPart.name << ' ' << genPart.manufacturer << ' '
            << genPart.amount << ' ' << genPart.price << ' ' << genPart.quality;
    }
    ALLPARTS = readPartsFromFile();
    sortSelected = 10;
    W.close();
    return;
}
void PARTSFUNC::search(string search)
{
    FOUNDPARTS.clear();
    cout << "Search name: searching '" << search << "'" << endl;
    for (int i = 0; i < ALLPARTS.size(); i++)
    {
        if (ALLPARTS[i].name == search)
        {
            FOUNDPARTS.push_back(ALLPARTS[i]);
        }
    }
    Sleep(2000);
    return;
}
void PARTSFUNC::displayFound()
{
    if (FOUNDPARTS.empty())
    {
        cout << "| There are no parts. Make a search query. |" << endl;
        cout << "************************" << endl;
        return;
    }
    system("CLS");
    int PARTSIZE = FOUNDPARTS.size();
    cout << "*******************************************************************************************************************************************" << endl;
    cout << "* SORT MODE: " << SortType[sortSelected] << " *" << endl;
    cout << "* PARTS CATALOGUE   *" << endl;
    cout << "|  NUM  |        PART NAME        |       COMPANY NAME      |     AMOUNT / SUPPLY     |      PRICE / SUPPLY     |       PART QUALITY      |" << endl;

    for (int i = 0; i < FOUNDPARTS.size(); i++)
    {
        string temp; int length;
        temp = "| ";
        temp += to_string(i);
        length = temp.length();
        cout << temp;
        addSpaces(length, 0);
        PARTSFUNC::DisplayContents(FOUNDPARTS[i]);
    }
    cout << "*******************************************************************************************************************************************" << endl;
    return;

}
bool PARTSFUNC::is_empty()
{
    if (FOUNDPARTS.empty())
    {
        return true;
    }
    return false;
}
void PARTSFUNC::contactCompanies()
{
    if (FOUNDPARTS.empty())
    {
        cout << "No results. " << endl;
        Sleep(2000);
        return;
    }
    int sel = -1;
    cout << "Select offer number: " << endl;
    sel = read_int_input(0, FOUNDPARTS.size() - 1);
    cout << "To contact " << FOUNDPARTS[sel].manufacturer << ", visit " <<
        FOUNDPARTS[sel].manufacturer << ".com " << endl;
    system("PAUSE");
    return;
}

//sort functions
bool NamesAZ(PARTS i, PARTS j) { return (i.name < j.name); }
void PARTSFUNC::sortNamesAZ(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), NamesAZ);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), NamesAZ);
    }
    sortSelected = 0;
    return;
}

bool NamesZA(PARTS i, PARTS j) { return (i.name > j.name); }
void PARTSFUNC::sortNamesZA(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), NamesZA);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), NamesZA);
    }
    sortSelected = 1;
    return;
}

bool ManuAZ(PARTS i, PARTS j) { return (i.manufacturer < j.manufacturer); }
void PARTSFUNC::sortManuAZ(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), ManuAZ);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), ManuAZ);
    }
    sortSelected = 2;
    return;
}

bool ManuZA(PARTS i, PARTS j) { return (i.manufacturer > j.manufacturer); }
void PARTSFUNC::sortManuZA(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), ManuZA);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), ManuZA);
    }
    sortSelected = 4;
    return;
}

bool AmountAZ(PARTS i, PARTS j) { return (i.amount < j.amount); }
void PARTSFUNC::sortAmountAZ(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), AmountAZ);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), AmountAZ);
    }
    sortSelected = 4;
    return;
}

bool AmountZA(PARTS i, PARTS j) { return (i.amount > j.amount); }
void PARTSFUNC::sortAmountZA(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), AmountZA);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), AmountZA);
    }
    sortSelected = 5;
    return;
}

bool PriceAZ(PARTS i, PARTS j) { return (i.price < j.price); }
void PARTSFUNC::sortPriceAZ(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), PriceAZ);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), PriceAZ);
    }
    sortSelected = 6;
    return;
}

bool PriceZA(PARTS i, PARTS j) { return (i.price > j.price); }
void PARTSFUNC::sortPriceZA(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), PriceZA);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), PriceZA);
    }
    sortSelected = 7;
    return;
}

bool QualityAZ(PARTS i, PARTS j) { return (i.quality < j.quality); }
void PARTSFUNC::sortQualityAZ(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), QualityAZ);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), QualityAZ);
    }
    sortSelected = 8;
    return;
}

bool QualityZA(PARTS i, PARTS j) { return (i.quality > j.quality); }
void PARTSFUNC::sortQualityZA(int mode)
{
    if (mode == 0)
    {
        sort(ALLPARTS.begin(), ALLPARTS.end(), QualityZA);
        writePartsToFile();
    }
    else
    {
        sort(FOUNDPARTS.begin(), FOUNDPARTS.end(), QualityZA);
    }
    sortSelected = 0;
    return;
}
