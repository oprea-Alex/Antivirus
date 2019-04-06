#pragma once
#include "StdWorker.h"


class C_TxtWorker : public C_StdWorker {

public:
	C_TxtWorker(){}
	C_TxtWorker(WorkerType& t) :C_StdWorker(t) {}
	void scan(C_MyList<C_String>&, const C_String&, bool);
	void report(const C_String&, int&);



};