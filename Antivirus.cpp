#include "Antivirus.h"

C_Antivirus::C_Antivirus() {
	fstream f1, f2;
	f1.open("TXT_scanned.txt", ios::in | ios::out | ios::trunc);
	f2.open("EXE_scanned.txt", ios::in | ios::out | ios::trunc);
	f1.clear(0);
	f2.clear(0);
	f1.close();
	f2.close();
	this->txt_base.fill_txt_list_std();//
	this->exe_base.fill_exe_list_std();//functii ce creaza doua baze de cunostinte standard(una txt si una exe)
	this->SM = NULL;
	cout << "Introduceti nr maxim de workeri:\n";
	cout << "Pt. txt: "; cin >> this->max_txt_workers;
	cout << "Pt. exe: "; cin >> this->max_exe_workers;
	cout << "Doriti sa scanati in modul strict[1/0]?\n";
	int flag;
	cin >> flag;
	if (flag == 0) this->strict_mode = false;
	else this->strict_mode = true;
}

void C_Antivirus::scan() {
	this->SM = C_ScanManager::GetInstance(txt_base, exe_base, max_txt_workers, max_exe_workers);
	this->SM->scan(this->txt_base, this->exe_base, this->strict_mode);
}

void C_Antivirus::update(C_MyList<C_String>& list, WorkerType t) {//functia de update primeste lista(baza de cunostine noua)
	//si tipul acesteia(exe/txt)
	if (t == txt_Worker) {
		if (this->txt_base != list) {
			this->txt_base += list;
			cout << "Update-ul bazei de cunostinte text, realizat cu succes!\n";
		}
		else cout << "Nu s-a realizat update-ul bazei de cunostinte txt!\n";
	}
	else {
		if (this->exe_base != list) {
			this->exe_base += list;
			cout << "Update-ul bazei de cunostinte exe, realizat cu succes!\n";
		}
		else cout << "Nu s-a realizat update-ul bazei de cunostinte exe!\n";
	}
}

C_Antivirus::~C_Antivirus() {
	this->SM->deallocate_list();
	this->SM->DestroyInstance();
}