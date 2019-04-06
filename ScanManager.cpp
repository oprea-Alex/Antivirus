#include "ScanManager.h"

C_ScanManager* C_ScanManager::mpInstance = NULL;

C_ScanManager* C_ScanManager::GetInstance(C_MyList<C_String>& txt_base, C_MyList<C_String>& exe_base, int& max_txt_workers, int& max_exe_workers) {
	try {
		if (mpInstance == NULL) {
			mpInstance = new C_ScanManager(txt_base, exe_base,max_txt_workers,max_exe_workers);
			if (mpInstance == NULL) throw new C_Exceptions("Eroare de alocare a memoriei pentru instantierea Scan Managerului!");
		}
		return mpInstance;
	}
	catch (C_Exceptions* e) {
		e->showError();
		delete e;
		exit(1);
	}
}

void C_ScanManager::DestroyInstance() {
	if (mpInstance != NULL)
		delete mpInstance;
	mpInstance = NULL;
}

char* citire_fisiere_de_scanat() {//functie care pune toate fisierele de scanat intr-un char* cu SPACE intre ele
	cout << "Introduceti numele fisierelor ce urmeaza a fi scanate cu <<space>> intre ele[0 pt. stop]: " << endl;
	char aux[20];
	char file_names[300];
	int counter = 1;
	cin >> aux;
	strcpy(file_names, aux);
	strcat(file_names, " ");
	while (1) {
		cin >> aux;
		if (!strcmp(aux, "0")) break;
		else counter++;
		strcat(file_names, aux);
		strcat(file_names, " ");
	}
	return file_names;
}

C_ScanManager::C_ScanManager(C_MyList<C_String>& txt_base, C_MyList<C_String>& exe_base, int& max_txt_workers, int& max_exe_workers){
	this->head = NULL;
	this->txt_base = txt_base;
	this->exe_base = exe_base;
	this->max_txt_workers = max_txt_workers;
	this->max_exe_workers = max_exe_workers;
	this->txt_files_scanned = 0;
	this->exe_files_scanned = 0;
}

void char_to_list(C_MyList<C_String>& to_scan, char* file_names) {//pune fisierele de scanat din char-ul* cu intr-o lista template
	char* p = strtok(file_names, " ");
	while (p != NULL) {
		C_String P(p);
		to_scan.push(P);
		p = strtok(NULL, " ");
	}
}

WorkerType check_file_Type(C_String& temp) {//functie ce returneaza tipul fisierului din lista de C_Stringuri
	int len = strlen(temp.get_string());
	if (temp.get_string()[len - 1] == 't') return txt_Worker;
	else if (temp.get_string()[len - 1] == 'e') return exe_Worker;
}

void C_ScanManager::deallocate_list() {//functia care dezaloca lista de workeri, apelata in destructorul Scan Manager-ului
	if (this->head == NULL) return;
	WorkerNode* temp = this->head;
	while (this->head != NULL) {
		delete this->head->pointer;
		this->head->pointer = NULL;
		temp = this->head;
		this->head = this->head->next;
		delete temp;
	}
}

int& C_ScanManager::existing_txt_workers() {//functie ce returneaza nr de workeri de tip txt existenti in lista de workeri de la nivelul SM
	WorkerNode* temp = this->head;
	int counter = 0;
	while (temp != NULL) {
		if (temp->pointer->get_Type() == txt_Worker) counter++;
		temp = temp->next;
	}
	return counter;
}

int& C_ScanManager::existing_exe_workers() {//analog ca mai sus pt workeri exe
	WorkerNode* temp = this->head;
	int counter = 0;
	while (temp != NULL) {
		if (temp->pointer->get_Type() == exe_Worker) counter++;
		temp = temp->next;
	}
	return counter;
}

C_StdWorker* C_ScanManager::add_to_list(WorkerType t) {//creeaza lista de workeri, primind tipul care va fi creat si returnand
														//pointer la workerul creat
	if (t == txt_Worker) {
		if (this->head == NULL) {
			this->head = new WorkerNode;
			this->head->pointer = new C_TxtWorker(t);
			this->head->pointer->set_ready(false);
			this->head->next = NULL;
			return this->head->pointer;
		}
		else {
			WorkerNode* temp = this->head;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new WorkerNode;
			temp = temp->next;
			temp->pointer = new C_TxtWorker(t);
			temp->pointer->set_ready(false);
			temp->next = NULL;
			return temp->pointer;
		}
	}
	else if (t == exe_Worker) {
		if (this->head == NULL) {
			this->head = new WorkerNode;
			this->head->pointer = new C_ExeWorker(t);
			this->head->pointer->set_ready(false);
			this->head->next = NULL;
			return this->head->pointer;
		}
		else {
			WorkerNode* temp = this->head;
			while (temp->next != NULL) temp = temp->next;
			temp->next = new WorkerNode;
			temp = temp->next;
			temp->pointer = new C_ExeWorker(t);
			temp->pointer->set_ready(false);
			temp->next = NULL;
			return temp->pointer;
		}
	}
}

void C_ScanManager::report() {//functie care scrie infectiile gasite in fisiere, apelata la finalul fiecare scanari a SM
	ofstream fout;
	fout.open("TXT_scanned.txt", ios::app);
	fout << "\nAu fost scanate " << this->txt_files_scanned << " fisier(e) .txt si " << this->exe_files_scanned;
	fout << " fisier(e) .exe de catre " << C_StdWorker::Get_Worker_counter() << " workeri." << endl;
	fout.close();
	fout.open("EXE_scanned.txt", ios::app);
	fout << "\nAu fost scanate " << this->txt_files_scanned << " fisier(e) .txt si " << this->exe_files_scanned;
	fout << " fisier(e) .exe de catre " << C_StdWorker::Get_Worker_counter() << " workeri." << endl;
	fout.close();
}

C_StdWorker* C_ScanManager::replace_worker(WorkerType t) {//inlocuieste workerul disponibil cu altul de tipul primit ca parametru
															//returneaza pointer la workerul nou, sau NULL daca nu s-a putut crea
	WorkerNode* temp = this->head;
	while (temp != NULL) {
		if ((temp->pointer->get_Type() != t) && temp->pointer->isReady()){
			C_StdWorker* aux = temp->pointer;
			temp->pointer = NULL;
			if (t == txt_Worker) temp->pointer = new C_TxtWorker(t);
			else if (t == exe_Worker) temp->pointer = new C_ExeWorker(t);
			delete aux;
			return temp->pointer;
		}
		temp = temp->next;
	}
	return NULL;
}

void C_ScanManager::make_workers_ready() {//apelata la sfarsitul fiecarei scanari a SM pentru a face toti workerii existenti "ready"
											//adica pregatiti de o noua scanare sau eventual de inlocuire prin replace_worker()
	WorkerNode* temp = this->head;
	while (temp != NULL) {
		temp->pointer->set_ready(true);
		temp = temp->next;
	}
}

C_StdWorker* search_a_ready_txt_worker(WorkerNode* head) {//cauta un worker txt pentru a fi inlocuit de un exe
	if (head == NULL) return NULL;
	while (head != NULL) {
		if (head->pointer->get_Type() == txt_Worker && head->pointer->isReady())
			return head->pointer;
		head = head->next;
	}
	return NULL;
}

C_StdWorker* search_a_ready_exe_worker(WorkerNode* head) {//analog pt exe
	if (head == NULL) return NULL;
	while (head != NULL) {
		if (head->pointer->get_Type() == exe_Worker && head->pointer->isReady())
			return head->pointer;
		head = head->next;
	}
	return NULL;
}

//functia de scan a Scan Managerului
//primeste bazele de cunostinte txt si exe si daca se scaneaza in modul strict sau nu
//scoate cate un fisier de scanat din lista de tip C_MyList<C_String>
//ii verifica tipul si instantiaza workerul de tip necesar
// sau cauta altul de alt tip pentru a fi inlocuit de un worker necesar
void C_ScanManager::scan(C_MyList<C_String>& txt_base, C_MyList<C_String>& exe_base, bool strict_mode) {
	int flag = 1;
	C_String file_to_scan;
	char aux[1000];
	WorkerType needed_type;
	C_MyList<C_String> to_scan;
		while (flag) {
			flag = 0;
			try {
				strcpy(aux, citire_fisiere_de_scanat());
				char_to_list(to_scan, aux);
				while (!to_scan.isVoid()) {
					file_to_scan = to_scan.pop();
					if (check_file_Type(file_to_scan) == txt_Worker) {
						if (this->existing_txt_workers() < this->max_txt_workers) {
							C_StdWorker* work_temp;
							work_temp = this->add_to_list(txt_Worker);
							work_temp->scan(txt_base, file_to_scan, strict_mode);
							work_temp->set_ready(false);
							this->txt_files_scanned++;
						}
						else if (this->existing_txt_workers() == this->max_txt_workers) {
							try {
								C_StdWorker* temp;
								temp = search_a_ready_txt_worker(this->head);
								if (temp != NULL) {
									temp->set_ready(false);
									temp->scan(txt_base, file_to_scan, strict_mode);
								}
								else {
									needed_type = txt_Worker;
									throw new C_Exceptions("Se incearca instantierea unui nou worker txt inlocuind un worker exe.");
								}
							}
							catch (C_Exceptions* e) {
								e->showError();
								delete e;
								C_StdWorker *m = NULL;
								m = this->replace_worker(needed_type);
								if (m == NULL) throw new C_Exceptions("Fail! | Nu a fost gasit niciun worker exe disponibil.");
								else {
									if (needed_type == txt_Worker) m->scan(txt_base, file_to_scan, strict_mode);
									else if (needed_type == exe_Worker) m->scan(exe_base, file_to_scan, strict_mode);
									cout << "Succes! | S-a reusit instantierea unui worker txt in locul unuia de tip exe disponibil." << endl;
								}
							}
						}
					}
					else if (check_file_Type(file_to_scan) == exe_Worker) {
						if (this->existing_exe_workers() < this->max_exe_workers) {
							C_StdWorker* temp_work;
							temp_work = this->add_to_list(exe_Worker);
							temp_work->scan(exe_base, file_to_scan, strict_mode);
							temp_work->set_ready(false);
							this->exe_files_scanned++;
						}
						else if (this->existing_exe_workers() == this->max_exe_workers) {
							try {
								C_StdWorker* temp;
								temp = search_a_ready_exe_worker(this->head);
								if (temp != NULL) {
									temp->set_ready(false);
									temp->scan(exe_base, file_to_scan, strict_mode);
								}
								else {
									needed_type = exe_Worker;
									throw new C_Exceptions("Se incearca instantierea unui nou worker exe inlocuind un worker txt.");
								}
							}
							catch (C_Exceptions* e) {
								e->showError();
								delete e;
								C_StdWorker* p = NULL;
								p = this->replace_worker(needed_type);
								if (p == NULL) throw new C_Exceptions("Fail! | Nu a fost gasit niciun worker txt disponibil.");
								else {
									if (needed_type == txt_Worker) p->scan(txt_base, file_to_scan, strict_mode);
									else if (needed_type == exe_Worker) p->scan(exe_base, file_to_scan, strict_mode);
									cout << "Succes! | S-a reusit instantierea unui worker exe in locul unuia de tip txt disponibil." << endl;
								}
							}
						}
					}
				}
				this->report();
				this->make_workers_ready();
				if (!flag) {
					cout << "Continuati cu o alta scanare?[0/1]\n";
					cin >> flag;
				}
			}
			catch (C_Exceptions* e) {
				e->showError();
				delete e;
				this->report();
				this->make_workers_ready();
				if (!flag) {
					cout << "Continuati cu o alta scanare?[0/1]\n";
					cin >> flag;
				}
			}
		}
}