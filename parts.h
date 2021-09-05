#pragma once
#ifndef _PARTS_H
#define _PARTS_H

using namespace std;

void addSpaces(int symbols_in_input, int step);

struct PARTS //struct allows for structurised parts array creation
{
    string name = "";
    string manufacturer = "";
    int amount = 0;
    int price = 0;
    int quality = 0;
    string qualityOption[5] = { "DEFAULT", "low", "medium", "high", "exceptional" };
};

class PARTSFUNC //class contains main parts list and functions connected to it
{
public:
    PARTSFUNC();
    ~PARTSFUNC();
    void DisplayContents(PARTS single_part_structure);
    void DisplayAllParts();
    void DisplayMidProcess(PARTS single_part_structure, string mode_display);
    void addPartManually();
    vector<PARTS> readPartsFromFile();
    void writePartsToFile();
    vector<PARTS> editPart();
    vector<PARTS> removePart();
    void selectSort(int mode);
    void sortNamesAZ(int mode);
    void sortNamesZA(int mode);
    void sortManuAZ(int mode);
    void sortManuZA(int mode);
    void sortAmountAZ(int mode);
    void sortAmountZA(int mode);
    void sortPriceAZ(int mode);
    void sortPriceZA(int mode);
    void sortQualityAZ(int mode);
    void sortQualityZA(int mode);
    void fillRandom();
    void search(string search_query);
    bool is_empty();
    void displayFound();
    void contactCompanies();

private:
    vector<PARTS> ALLPARTS; //main parts list
    vector<PARTS> FOUNDPARTS; //sub parts list for search results
};

#endif