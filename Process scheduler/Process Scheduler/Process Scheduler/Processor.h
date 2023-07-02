#pragma once
#include<iostream>
#include<queue>
#include "Process.h"
using namespace std;
class Scheduler;
class Processor
{
	queue <Processor*> AllProcessors;
protected:

	Scheduler* scheduler;

public:
	
	Processor (Scheduler* s)
	{
		scheduler = s;
	}
	virtual bool IsIDeal() = 0;
	virtual void ProcessorAlgo() = 0;


	///___Setters___///
			//Total processor Busy Time is Calculacted from the total Cpu times for all processes in the processor  
	virtual void SetTotalBusyTime(int c) = 0;
	virtual void SetRunProces() = 0;
	virtual void SetTotalTurnaroundTime(int) = 0;      //Total processor turnround Time is Calculacted from the total TT for all processes in the processor  
	virtual void SetTotalProcessorIDLETime() = 0;     
	virtual void SetProcessorLoad() = 0;               //Processor Load=Total processor Busy Time ÷ processor turnround
	virtual void SetProcessorUtilization() = 0;        //Processor Utilization=Total processor Busy Time ÷ processor turnround
	///___getters___///
	virtual int GetTotalTurnaroundTime()  = 0;
	virtual Process* GetRunProcess() = 0;
	virtual int GetTotalBusyTime() = 0;
		
	///__functions__///

	virtual void Add_process(Process* p) = 0;	      
	virtual void delete_process(Process* p) = 0;
	virtual Process* ReturnProces() = 0;
};
