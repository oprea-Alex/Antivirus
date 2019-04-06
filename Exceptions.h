#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <istream>
#include <ostream>

using namespace std;

class C_Exceptions {
	char* ErrMsg;

public:
	C_Exceptions();
	C_Exceptions(const char*);
	~C_Exceptions();
	void showError();
	void printError(const char*,int);
};