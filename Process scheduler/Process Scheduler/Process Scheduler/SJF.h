#pragma once
#include "Processor.h"
#include "Scheduler.h"
class SJF :public Processor
{
	priority_queue<Process*> SJFProcessoes;
	Process* RunProcess=nullptr;
	Process* StealProcess = nullptr;

	int TotalTAT = 0;
	int TotalIdealTime = 0;
	int ProcessorLoad = 0;
	int totalBusyTime = 0;
	int ProcessorUtilization = 0;
	

public:
	SJF(Scheduler*);
	virtual bool IsIDeal();
	virtual void ProcessorAlgo();
	virtual Process* ReturnProces();



	virtual void SetTotalTurnaroundTime(int);
	virtual void SetTotalProcessorIDLETime();
	virtual void SetProcessorLoad();
	virtual void SetProcessorUtilization();
	virtual void Add_process(Process* p);
	virtual void delete_process(Process* p);
	virtual void SetTotalBusyTime(int c);
	virtual void SetRunProces();


	///___getters___///

	virtual int GetTotalTurnaroundTime();
	virtual Process* GetRunProcess() ;
	virtual int GetTotalBusyTime();

};

