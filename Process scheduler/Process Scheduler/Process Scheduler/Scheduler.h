#pragma once
#include <iostream>
using namespace std;
#include "Process.h"
#include "Processor.h"
#include "Linked_List.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
class Scheduler
{
	int RTF, MAxW, STL, ForkProbability,NoOfProceesors;
	queue<int>SignKillTime;
	int NumFCFS, NumSJF, NumRR;
	int TimeSlice;
	IO io ;
	int BLKSteps = 0;
	int StealLimit = 0;
	Scheduler* S;
	LinkedList<Processor * > ProcessorsList;
	queue<Process*> BLK_List;
	queue<Process*> NEW_List;
	queue<Process*> TRM_List;
	struct KillProcess
	{
		int ProcessKillTime, ProcessId;
	};
	
	queue<KillProcess> kill;
	queue<IO> IoRequests;
	int TimeStep = 0;
public:
	void readinputfile(string );
	void DisplayFileData();
	void CreatProcessors();
	void FromNewToREady();
	bool CheckIORequests(Process*);
	void FromBLKToReady();
	void FromRunToTerm(Process*);
	void WorkStealing();
	void simulation();
	int GetRTF()const;
	int GetMaxW()const;
	int GetCurrentTimeStep()const;
	
	void ProcessMigration(int,Process* );
};



