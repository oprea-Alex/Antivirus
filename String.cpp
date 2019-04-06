#include "String.h"

C_String::C_String() {
	this->string = NULL;
}


C_String::C_String(const char* x) {
	try {
		const int len = strlen(x) + 1;
		this->string = new char[len];
		if (this->string == NULL) throw new C_Exceptions("Eroare la alocarea unui nou string.");
		strcpy(this->string, x);
	}
	catch (C_Exceptions* e) {
		e->showError();
		delete e;
		exit(1);
	}
}

C_String::C_String(const C_String& rhs) {
	try {
		const int len = strlen(rhs.get_string()) + 1;
		this->string = new char[len];
		if (this->string == NULL) throw new C_Exceptions("Eroare la alocarea unui nou string.");
		strcpy(this->string, rhs.get_string());
	}
	catch (C_Exceptions* e) {
		e->showError();
		delete e;
		exit(1);
	}
}

C_String::~C_String() {
	if (this->string != NULL)
		delete this->string;
	this->string = NULL;
}

void C_String::set_string(const char* x) {
	try {
		const int len = strlen(x) + 1;
		this->string = new char[len];
		if (this->string == NULL) throw new C_Exceptions("Eroare la alocarea unui nou string.");
		strcpy(this->string, x);
	}
	catch (C_Exceptions* e) {
		e->showError();
		delete e;
		exit(1);
	}
}

C_String& C_String::operator=(const char* x) {
	try {
		const int len = strlen(x) + 1;
		this->string = new char[len];
		if (this->string == NULL) throw new C_Exceptions("Eroare la alocarea unui nou string.");
		strcpy(this->string, x);
		return *this;
	}
	catch (C_Exceptions* e) {
		e->showError();
		delete e;
		exit(1);
	}
}

bool C_String::operator==(const char* x) {
	try {
		if (this->string == NULL) throw new C_Exceptions("Eroare la comparatie! String gol.");
		if (!strcmp(this->string, x)) return true;
		return false;
	}
	catch (C_Exceptions* e) {
		e->showError();
		delete e;
	}
}

ostream& operator<<(ostream& os, const C_String& rhs) {
	os << rhs.string;
	return os;
}

void C_String::operator=(const C_String& rhs) {
	if (this->string != NULL) delete this->string;
	const int len = strlen(rhs.string) + 1;
	this->string = new char[len];
	strcpy(this->string, rhs.string);
}

bool C_String::operator==(const C_String& rhs) {
	try {
		if (this->string == NULL) throw new C_Exceptions("Eroare la comparatie! String gol.");
		if (!strcmp(this->string, rhs.get_string())) return true;
		return false;
	}
	catch (C_Exceptions* e) {
		e->showError();
		delete e;
	}
}