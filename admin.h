#pragma once
#ifndef _ADMIN_H
#define _ADMIN_H

using namespace std;

bool file_is_empty(ifstream& checked_ifstream);
int read_int_input(int left_bound, int right_bound); //read int to be >= lbound && <= rbound
char read_char_input(char left_bound, char right_bound, short check_mode); //read char to be > lbound && <= rbound
int GET_ADMIN_CODE(); //gets admin code from file
int CHANGE_ADMIN_CODE(); // change or reset admin code
#endif