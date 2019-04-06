#pragma once
#include "TxtWorker.h"
#include "ExeWorker.h"

typedef struct WorkerNode {
	C_StdWorker* pointer;
	WorkerNode* next;
}WorkerNode;

class C_ScanManager {
	int max_txt_workers;
	int max_exe_workers;
	int txt_files_scanned;
	int exe_files_scanned;
	WorkerNode *head;
	C_MyList<C_String> txt_base;
	C_MyList<C_String> exe_base;
	static C_ScanManager* mpInstance;
	C_ScanManager(C_MyList<C_String>&, C_MyList<C_String>&,int&,int&);
	C_ScanManager() {}
	~C_ScanManager() {}
public:
	static C_ScanManager* GetInstance(C_MyList<C_String>&, C_MyList<C_String>&, int&, int&);
	WorkerNode* GetHead() const { return this->head; }
	void DestroyInstance();
	void scan(C_MyList<C_String>&, C_MyList<C_String>&, bool);
	int& existing_txt_workers();
	int& existing_exe_workers();
	C_StdWorker* add_to_list(WorkerType);
	C_StdWorker* replace_worker(WorkerType);
	void report();
	void make_workers_ready();
	void deallocate_list();
};
