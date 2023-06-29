#pragma once
#include "Processor.h"
#include "Scheduler.h"
class RR :public Processor
{
	queue <Process*> RRProcesses;
	Process* RunProcess=nullptr;
	int TimeSlice;
	int TotalTAT = 0;
	int TotalIdealTime = 0;
	int ProcessorLoad = 0;
	int totalBusyTime = 0;
	int ProcessorUtilization = 0;
	int countTime = 0;
public:
	RR(int T,Scheduler*);
	virtual bool IsIDeal();
	virtual void ProcessorAlgo();


	///___setters___///

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
	virtual Process* GetRunProcess();
	virtual int GetTotalBusyTime();
};

