#pragma once
#include "StdWorker.h"


class C_ExeWorker : public C_StdWorker {

public:
	C_ExeWorker(){}
	C_ExeWorker(WorkerType tip) : C_StdWorker(tip){}
	void scan(C_MyList<C_String>&, const C_String&, bool);
	void report(const C_String&, int&);
};