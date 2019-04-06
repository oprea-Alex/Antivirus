#include "TxtWorker.h"

//functia de scanare a workerului txt
//primeste baza de cunostinte, numele fisierului sub tipul C_String si daca/nu se face scanarea stricta
//in cazul scanarii stricte, citeste cate un cuvant din fisierul de scanat si scoate cate un cuvant din baza de cunosinte
	//pana cand lista este goala si cauta cu strstr() daca cuv. malitios se afla in cuvantul citit din fisiere
//in cazul in care nu se doreste scanare stricta, pune cuvantul scos din fisier intr-un C_String
	//si foloseste functia search(C_String, C_MyList) implementata la nivelul clasei C_MyList pentru a cauta cuvantul suspectat in baza de cunostinte
void C_TxtWorker::scan(C_MyList<C_String>& list, const C_String& file_name, bool strict_mode) {
	try {
		ifstream fin;
		C_MyList<C_String> temp;
		temp = list;
		if (temp.get_head() == NULL) throw new C_Exceptions("Baza de cunostinte goala!");
		int no_of_infections = 0;
		fin.open(file_name.get_string());
		if (!fin.is_open()) throw new C_Exceptions("Fisierul text nu a fost deschis!");
		char aux[800];
		int P = 100;
		if (strict_mode) {
			cout << "Introduceti procentul P pentru scanarea de fisier(e) .txt in modul strict:\n";
			cin >> P;
		}
		while (!fin.eof()) {
			fin >> aux;
			temp = list;
			if (strict_mode) {
				while (!temp.isVoid()) {
					char temp_string[600];
					strcpy(temp_string, temp.pop().get_string());
					int x = (strlen(temp_string) * P) / 100;
					temp_string[x] = '\0';
					char* p = strstr(aux, temp_string);
					if (p != NULL) no_of_infections++;
				}
			}
			else {
				C_String s(aux);
				if (list.search(s, list)) no_of_infections++;
			}
		}
		fin.close();
		this->report(file_name, no_of_infections);
	}
	catch (C_Exceptions* e) {
		e->printError(file_name.get_string(), 1);
		delete e;
	}
}

//functia de raportare in fisierul TXT_scanned.txt a numarului de infectii gasit
//apelata la finalul fiecarei scanari a unui worker txt
void C_TxtWorker::report(const C_String& file_name, int& no_of_infections) {
	ofstream fout;
	fout.open("TXT_scanned.txt", ios::app);
	fout << file_name.get_string() << " | ";
	int ID = this->Get_Worker_ID();
	fout << "TxtWorker: " << ID << " | ";
	if(no_of_infections) fout << "No of infections: " << no_of_infections << endl;
	else fout << "Clean file" << endl;
	fout.close();
}
