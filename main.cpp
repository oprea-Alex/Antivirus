#include "Antivirus.h"

//programul scaneaza doar fisiere cu extensia .txt sau .exe

void main() {


	C_Antivirus Karspersky;//instantierea antivirusului folosind Ctor implicit

	C_MyList<C_String> new_txt_base, new_exe_base; //instantiez 2 baze noi de cunostinte, una txt si una exe
	new_txt_base.fill_txt_list();// cer utilizatorului sa introduca elementele fiecarei baze de cunostinte
	new_exe_base.fill_exe_list();
	//daca nu introduce nimic, se va scana folosind o baza standard de cunostinte
	//(vezi functia fill_exe_list_std/fill_txt_list_std) din clasa C_MyList

	Karspersky.update(new_txt_base, txt_Worker);//se face update-ul pr-zis pt care am overloadat 
	Karspersky.update(new_exe_base, exe_Worker);//operatorii != si += intre 2 instante C_MyList


	Karspersky.scan();//incepe scanarea

}