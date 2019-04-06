#pragma once
#include "ScanManager.h"


class C_Antivirus {
	C_ScanManager* SM;
	C_MyList<C_String> txt_base;
	C_MyList<C_String> exe_base;
	int max_txt_workers;
	int max_exe_workers;
	bool strict_mode;
public:
	C_Antivirus();
	~C_Antivirus();
	C_MyList<C_String> get_txt_base() const { return this->txt_base; }
	C_MyList<C_String> get_exe_base() const { return this->exe_base; }
	void set_txt_base(C_MyList<C_String>& x) { this->txt_base = x; }
	void set_exe_base(C_MyList<C_String>& x) { this->exe_base = x; }
	void scan();
	void update(C_MyList<C_String>&, WorkerType);

};