#pragma once
#include "Exceptions.h"
#include "String.h"

//clasa C_Node este, practic un wrapper pentru un obiect T, pentru ca acesta sa poata fi inclus in lista template
template <class T>
class C_Node {
private:
	T string;
	C_Node<T>* next;

public:
	C_Node() {
		this->next = NULL;
	}
	T get_string() const { return this->string; }
	void set_string() { this->string = NULL; }
	void set_string(T& str) { this->string = str; }
	void set_string(char* str) { this->string = str; }
	C_Node<T>* get_next() const { return this->next; }
	void set_next() { this->next = NULL; }
	void set_next(C_Node<T>* p) { this->next = p; }
};

//Clasa C_MyList reprezinta clasa listei template cu operatorii !=, == si += overload-ati astfel incat sa permita update-ul 
//"bazei de cunostinte"
template <class T>
class C_MyList : public C_Node<T> {
	C_Node<T>* head;

public:
	C_MyList() {
		this->head = NULL;
	}
	~C_MyList() {
		while (this->head != NULL) {
			C_Node<T>* temp = this->head->get_next();
			delete this->head;
			this->head = temp;
		}
	}
	C_Node<T>* get_head() const { return this->head; }
	void push(T& string) {
		try {
			if (this->head == NULL) {
				this->head = new C_Node<T>;
				if (this->head == NULL) throw new C_Exceptions("Eroare la alocarea primului nod din lista template!");
				this->head->set_string(string);
				this->head->set_next();
			}
			else {
				C_Node<T>* temp = this->head;
				while (temp->get_next() != NULL) temp = temp->get_next();
				temp->set_next(new C_Node<T>);
				if (temp->get_next() == NULL) throw new C_Exceptions("Eroare la alocarea unui nou nod in lista template!");
				temp = temp->get_next();
				temp->set_string(string);
				temp->set_next(NULL);
			}
		}
		catch (C_Exceptions* e) {
			e->showError();
			delete e;
			exit(1);
		}
	}
	T pop() {
		if (this->head == NULL) throw new C_Exceptions("Lista de cuvinte malitioase este goala!\n");
		C_Node<T>* temp = this->head;
		this->head = this->head->get_next();
		T aux = temp->get_string();
		delete temp;
		return aux;
	}
	bool isVoid() {
		if (this->head == NULL) return true;
		return false;
	}
	void fill_txt_list() {
		cout << "Introduceti cuvintele malitioase ale noii baze de cunostinte txt[unul cate unul]:" << endl;
		char aux[20];
		int flag = 1;
		while (flag) {
			cin >> aux;
			C_String str(aux);
			this->push(str);
			cout << "Continuati?[0/1]" << endl;
			cin >> flag;
		}
	}
	void fill_exe_list() {
		cout << "Introduceti numele fisierelor .exe ce contin semnaturi ale virusilor[unul cate unul][0 pt. stop]:" << endl;
		char aux[30];
		cin >> aux;
		while (strcmp(aux, "0")) {
			C_String str(aux);
			this->push(str);
			cin >> aux;
		}
	}
	void fill_txt_list_std() {///FUNCTIE APELATA LA CONSTRUCTIA ANTIVIRUSULUI PENTRU UMPLEREA BAZEI DE CUNOSTINTE DE .txt MALITIOS
		C_String str("malitios");
		C_String str1("virus");
		this->push(str); this->push(str1);
		C_String str2("executabil"); this->push(str2);
	}
	void fill_exe_list_std() {
		C_String str("malitios.exe");
		this->push(str);
	}
	bool operator==(const C_MyList<T>& rhs) {
		try {
			C_Node<T>* head1 = this->get_head();
			C_Node<T>* head2 = rhs.get_head();
			if (head1 == NULL || head2 == NULL) throw new C_Exceptions("Listele nu pot fi comparate, sunt goale!");
			C_Node<T>* temp = head2;
			while (head2 != NULL) {
				if (!this->search(head2->get_string(), *this)) return false;
				head2 = head->get_next();
			}
			return true;
		}
		catch (C_Exceptions* e) {
			e->showError();
			delete e;
			return false;
		}
	}
	bool search(T searchFor,const C_MyList<T>& searchIn){
		C_Node<T>* head = searchIn.head;
		while (head != NULL) {
			if (head->get_string() == searchFor) return true;
			head = head->get_next();
		}
		return false;
	}
	void operator+=(const C_MyList<T>& rhs) {
		try {
			C_Node<T>* head1 = this->get_head();
			C_Node<T>* head2 = rhs.get_head();
			if (head1 == NULL || head2 == NULL) throw new C_Exceptions("Listele nu pot fi comparate, sunt goale!");
			C_Node<T>* temp = head2;
			while (head2 != NULL) {
				if (search(head2->get_string(), (*this)) == false) this->push(head2->get_string());
				head2 = head2->get_next();
			}
		}
		catch (C_Exceptions* e) {
			e->showError();
			delete e;
		}
	}
	void operator=(const C_MyList<T>& rhs) {
		C_Node<T>* head2 = rhs.get_head();
		while (head2 != NULL) {
			this->push(head2->get_string());
			head2 = head2->get_next();
		}
	}
	void display_list() {
		try {
			if (this->head == NULL) throw new C_Exceptions(104, "Nu pot afisa lista. Este goala!");
			while (!this->isVoid()) cout << this->pop() <<" ";
			cout << endl;
		}
		catch (C_Exceptions* e) {
			e->showError();
			delete e;
		}
	}
	bool operator!=(const C_MyList<T>& rhs) {
		if (*this == rhs) return false;
		return true;
	}
};