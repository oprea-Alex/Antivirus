#pragma once
#include "Exceptions.h"

//clasa C_String reprezinta, de fapt, un wrapper pentru un char* in care stochez nume de fisiere, cuvinte malitioase etc.
class C_String {
	char* string;

public:
	C_String();
	C_String(const char*);
	C_String(const C_String&);
	~C_String();
	char* get_string()const { return this->string; }
	void set_string(const char* x);
	C_String& operator=(const char*);
	bool operator==(const char*);
	friend ostream& operator<<(ostream&, const C_String&);
	void operator=(const C_String&);
	bool operator==(const C_String&);
};