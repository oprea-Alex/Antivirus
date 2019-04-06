#include "Exceptions.h"

C_Exceptions::C_Exceptions() {
	this->ErrMsg = NULL;
}

C_Exceptions::C_Exceptions(const char* msg) {
	const int len = strlen(msg) + 1;
	this->ErrMsg = new char[len];
	strcpy(this->ErrMsg, msg);
}

C_Exceptions::~C_Exceptions() {
	if (this->ErrMsg != NULL)
		delete this->ErrMsg;
	this->ErrMsg = NULL;
}

void C_Exceptions::showError() {
	cout << "Eroare! " << " | ";
	cout << this->ErrMsg << endl;
}

void C_Exceptions::printError(const char* file_name,int x) {
	ofstream fout;
	if(x == 1) fout.open("TXT_scanned.txt", ios::app);
	else fout.open("EXE_scanned.txt", ios::app);
	fout << file_name << "Eroare! " << this->ErrMsg << endl;
	fout.close();
}