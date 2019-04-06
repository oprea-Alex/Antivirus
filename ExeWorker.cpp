#include "ExeWorker.h"

//functia de scan a workerului Exe
//primeste baza de cunostinte exe, fisierul de scanat sub forma de C_String si daca se face in modul strict scanarea
//citeste continutul semnaturii(virus_signature) intr-un char*, continutul fisierului de scanat in alt char
//parcurgand continului fisierului(file_content) intr-un for si comparandu-l cu semnatura virusului cu memcmp()
void C_ExeWorker::scan(C_MyList<C_String>& list, const C_String& file_name, bool strict_mode) {
	try {
		C_MyList<C_String> temp;
		C_String aux;
		temp = list;
		if (temp.isVoid()) throw new C_Exceptions("Baza de cunostinte goala!");
		ifstream fin, fin2;
		int no_of_infections = 0;
		fin.open(file_name.get_string(), ios::binary);
		if (!fin.is_open()) throw new C_Exceptions("Fisierul binar nu a fost deschis!");
		fin.seekg(0, ios::end);
		int size_file = fin.tellg();
		char *virus_signature = NULL;
		char *file_content = NULL;
		file_content = new char[size_file + 1];
		if (file_content == NULL) {
			C_Exceptions e("Eroare la alocarea memoriei pentru continutul fisierului binar de scanat!");
			throw e;
		}
		fin.seekg(0, ios::beg);
		file_content[size_file] = NULL;
		fin.read(file_content, size_file);
		fin.close();
		while (!temp.isVoid()) {
			aux = temp.pop();
			fin2.open(aux.get_string(), ios::binary);
			if (!fin2.is_open()) throw new C_Exceptions("Fisierul binar nu a fost deschis!");
			fin2.seekg(0, ios::end);
			int size_vir = fin2.tellg();
			virus_signature = new char[size_vir + 1];
			if (virus_signature == NULL) {
				C_Exceptions e("Eroare la alocarea memoriei pentru continutul fisierului binar de scanat!");
				throw e;
			}
			fin2.seekg(0, ios::beg);
			virus_signature[size_vir] = NULL;
			fin2.read(virus_signature, size_vir);
			fin2.close();
			if (strict_mode) {
				cout << "Introduceti procentul P pentru scanarea de fisier(e) .exe in modul strict:\n";
				int P;
				cin >> P;
				size_vir = (size_vir * P) / 100;
			}
			for (int i = 0; i <= size_file - size_vir; i++)
				if (!memcmp(file_content + i, virus_signature, size_vir))
					no_of_infections++;
		}
		this->report(file_name, no_of_infections);
		delete[] file_content;
		delete[] virus_signature;
	}
	catch (C_Exceptions* e) {
		e->printError(file_name.get_string(), 2);
		delete e;
	}
	catch (C_Exceptions& e) {
		e.showError();
		exit(1);
	}
}

//functia workerului exe care raporteaza in fisierul EXE_scanned.txt numarul de infectii
//apelata la finalul fiecarei scanari
void C_ExeWorker::report(const C_String& file_name, int& no_of_infections) {
	ofstream fout;
	fout.open("EXE_scanned.txt", ios::app);
	fout << file_name.get_string() << " | ";
	fout << "ExeWorker: " << this->Get_Worker_ID() << " | ";
	if (no_of_infections) fout << "No of infections: " << no_of_infections << endl;
	else fout << "Clean file" << endl;
	fout.close();
}