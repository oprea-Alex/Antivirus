#pragma once
#include "MyList.h"

using namespace std;

typedef enum WorkerType {
	txt_Worker, exe_Worker
}WorkerType;

class C_StdWorker {//clasa abstracta din care deriveaza workerii exe si txt
	WorkerType Type;
	int ID;
	static int Worker_counter;
	bool ready;
public:
	C_StdWorker() {	}
	C_StdWorker(WorkerType& type) {
		this->Type = type;
		this->Worker_counter++;
		this->ready = ready;
		this->ID = C_StdWorker::Worker_counter;
	}
	static int& Get_Worker_counter() { 
		return C_StdWorker::Worker_counter;
	}
	int& Get_Worker_ID(){
		return this->ID;
	}
	~C_StdWorker() {}
	WorkerType get_Type() const { return this->Type; }
	void set_ready(const bool x) { this->ready = x; }
	bool isReady() {
		if (this->ready == true) return true;
		return false;
	}
	virtual void scan(C_MyList<C_String>&,const C_String&, bool) = 0;
	virtual void report(const C_String&, int&) = 0;
};