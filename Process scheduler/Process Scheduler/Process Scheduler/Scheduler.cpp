#include "Scheduler.h"
#include <fstream>
#include <string>
#include <sstream>

void Scheduler::readinputfile(string filename)
{
	ifstream file;
	file.open(filename);
	if (!file)
	{
		cout << " Error " << endl;
		return;
	}
	string line;
	int number;
	//this is the output of the first line 
	file >> NumFCFS >> NumSJF >> NumRR;
	//this is the output of the second line 
	file >> TimeSlice;
	//this is the output of the third line 
	file >> RTF >> MAxW >> STL >> ForkProbability;
	//this is the output of the fourth line 
	file >> NoOfProceesors;
	// Ignore the newline character
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//this for loop to get the processes data
	for (int i = 0; i < NoOfProceesors; i++)
	{
		getline(file, line); //read the file line by line
		istringstream iss(line); //to treat the line as file stream
		int AT, PID, CT, NOM, IOR, IOD;
		char x; //we use it to ignore the unusable symboles
		//to read the first four numbers in the line
		iss >> AT >> PID >> CT >> NOM;
		//this loop to read the io_requests and then put each pair in the queue
		while (iss >> x >> IOR >> x >> IOD >> x)
		{
			io.IO_R = IOR;
			io.IO_D = IOD;
			IoRequests.push(io);
			//to ignore the comma between each pair
			if (iss.peek() == ',')
			{
				iss.ignore();
			}
		}


		Process* temp = new Process(AT, PID, CT, IoRequests);
		NEW_List.push(temp);
		for (int i = 0; i < NOM; i++)
		{
			IoRequests.pop();
		}
	}
	KillProcess temp;
	while (getline(file, line))
	{
		istringstream iss(line);
		iss >> temp.ProcessKillTime >> temp.ProcessId;
		kill.push(temp);
		if (file.eof())
		{
			break;
		}
	}
	file.close();
}

void  Scheduler::CreatProcessors()
{
	for (int i = 0; i < NumFCFS; i++)
	{
		FCFS* FCFSProcesseor = new FCFS(S);
		ProcessorsList.InsertBeg(FCFSProcesseor);
	}
	for (int i = NumFCFS; i < (NumSJF + NumFCFS); i++)
	{
		SJF* SJFProcessor = new SJF(S);
		ProcessorsList.InsertBeg(SJFProcessor);
	}
	for (int i = (NumSJF + NumFCFS); i < (NumSJF + NumFCFS + NumRR); i++)
	{
		RR* RRProcessor = new RR(TimeSlice, S);

		ProcessorsList.InsertBeg(RRProcessor);
	}

}
void  Scheduler::FromNewToREady()
{

	int ShortestQueue = -1;
	int NodeNumber = -1;
	while (!NEW_List.empty() && NEW_List.front()->GetArrivalTime() == TimeStep)
	{
		for (int i = 1; i < (NumFCFS + NumRR + NumSJF + 1); i++)
		{
			if (ProcessorsList.Data_found(i)->GetTotalBusyTime() == 0)
			{
				ProcessorsList.Data_found(i)->Add_process(NEW_List.front());
				NEW_List.front()->SetProcessState(1);
				ProcessorsList.Data_found(i)->SetTotalBusyTime(NEW_List.front()->GetCPUTime());
				NEW_List.pop();
				NodeNumber = -1;
				ShortestQueue = -1;
				break;
			}
			else if (ShortestQueue > ProcessorsList.Data_found(i)->GetTotalBusyTime())
			{
				ShortestQueue = ProcessorsList.Data_found(i)->GetTotalBusyTime();
				NodeNumber = i;

			}
		}
		if (NodeNumber != -1)
		{
			ProcessorsList.Data_found(NodeNumber)->Add_process(NEW_List.front());
			NEW_List.front()->SetProcessState(1);
			ProcessorsList.Data_found(NodeNumber)->SetTotalBusyTime(NEW_List.front()->GetCPUTime());
			NEW_List.pop();
			NodeNumber = -1;
			ShortestQueue = -1;

		}





	}
}

bool  Scheduler::CheckIORequests(Process* processes)
{
	int CurrentCT;
	int CT;

	if (processes)
	{
		CurrentCT = processes->GetCurrentCT();
		CT = processes->GetCPUTime();
		if (processes->GetIOQueueSize() != 0 && processes->GetIOR().IO_R == CurrentCT)
		{
			//Transfer the prosses from Run to blk	queue
			BLK_List.push(processes);
			//set the state of this process to be bloked
			processes->SetProcessState(3);
			return true;

		}

	}

	return false;



}
void  Scheduler::FromBLKToReady()
{
	if (BLK_List.size() == 0)
	{
		return;
	}
	else if (BLK_List.size() != 0)
	{
		if (BLK_List.front()->GetIOR().IO_D == BLKSteps)
		{
			int ShortestQueue = -1;
			int NodeNumber = -1;
			BLK_List.front()->DeleteIO();
			for (int i = 1; i < (NumFCFS + NumRR + NumSJF + 1); i++)
			{
				if (ProcessorsList.Data_found(i)->GetTotalBusyTime() == 0)
				{
					ProcessorsList.Data_found(i)->Add_process(BLK_List.front());
					BLK_List.front()->SetProcessState(1);
					ProcessorsList.Data_found(i)->SetTotalBusyTime((BLK_List.front()->GetCPUTime() - BLK_List.front()->GetCurrentCT()));
					BLK_List.pop();
					NodeNumber = -1;
					ShortestQueue = -1;
					BLKSteps = 0;
					break;
				}
				else if (ShortestQueue > ProcessorsList.Data_found(i)->GetTotalBusyTime())
				{
					ShortestQueue = ProcessorsList.Data_found(i)->GetTotalBusyTime();
					NodeNumber = i;

				}
			}
			if (NodeNumber != -1)
			{
				ProcessorsList.Data_found(NodeNumber)->Add_process(BLK_List.front());
				BLK_List.front()->SetProcessState(1);
				ProcessorsList.Data_found(NodeNumber)->SetTotalBusyTime((BLK_List.front()->GetCPUTime() - BLK_List.front()->GetCurrentCT()));
				BLK_List.pop();
				NodeNumber = -1;
				ShortestQueue = -1;
				BLKSteps = 0;

			}
		}
		else
		{
			BLKSteps++;
		}


	}

}

void  Scheduler::FromRunToTerm(Process* processes)
{
	TRM_List.push(processes);
	processes->SetTerminationTime(TimeStep);
	processes->SetTurnaroundDuration();
	processes->SetWaitingTime();
	processes->SetProcessState(4);


}
/// <summary>
/// With a work-stealing approach, the shortest ready queue in the system looks at the longest 
//ready queue to see how full it is.If the longest queue is(notably) more full, the shortest one
//will ‘steal” one or more process from it to help balance load
/// </summary>

void Scheduler::WorkStealing()
{
	int SQF = -1;  //longest queue finish time
	int LQF = -1; //shortest queue finish time
	int ShortestNode = 0;
	int longestNode = 0;
	//To find the shortest and longest queue
	for (int i = 1; i < (NumFCFS + NumRR + NumSJF + 1); i++)
	{
		int expectedFinishTime = ProcessorsList.Data_found(i)->GetTotalBusyTime() + TimeStep;
		if (SQF > expectedFinishTime)
		{
			SQF = expectedFinishTime;
			ShortestNode = i;
		}
		if (LQF < expectedFinishTime)
		{
			LQF = expectedFinishTime;
			longestNode = i;
		}
	}
	StealLimit = ((LQF - SQF) / LQF) * 100;
	while (StealLimit > 40)
	{
		ProcessorsList.Data_found(ShortestNode)->Add_process(ProcessorsList.Data_found(longestNode)->ReturnProces());

		// Update the finish times and StealLimit

		LQF = ProcessorsList.Data_found(longestNode)->GetTotalBusyTime() + TimeStep;
		SQF = ProcessorsList.Data_found(ShortestNode)->GetTotalBusyTime() + TimeStep;
		StealLimit = ((LQF - SQF) / LQF) * 100;

	}

	// Reset variables
	SQF = -1;
	LQF = -1;
	ShortestNode = 0;
	longestNode = 0;
}
int Scheduler::GetRTF()const
{
	return RTF;
}int Scheduler::GetMaxW()const
{
	return MAxW;
}int Scheduler::GetRTF()const
{
	return TimeStep;
}
//The num will be used to check if the process will be migrate from RR or FCFS if num=1 it will be RR and if 2 it will be FCFS
void Scheduler::ProcessMigration(int num, Process* MigratedProcess)
{
	int ShortestNode = 0;
	int ShortesRT = -1;
	if (num == 1)
	{
		for (int i = (NumFCFS); i < (NumSJF + NumFCFS); i++)
		{
			if (ShortesRT > ProcessorsList.Data_found(i)->GetTotalBusyTime())
			{
				ShortestNode = i;
				ShortesRT = ProcessorsList.Data_found(i)->GetTotalBusyTime();
			}
		}
		ProcessorsList.Data_found(ShortestNode)->Add_process(MigratedProcess);

		//reset values
		ShortestNode = 0;
			ShortesRT = -1;


	}

	else if (num == 2)
	{
		for (int i = (NumSJF + NumFCFS); i < (NumSJF + NumFCFS + NumRR); i++)
		{
			ShortestNode = i;
			ShortesRT = ProcessorsList.Data_found(i)->GetTotalBusyTime();
		}
		ProcessorsList.Data_found(ShortestNode)->Add_process(MigratedProcess);
		//reset values
		ShortestNode = 0;
		ShortesRT = -1;
	}
	else
	{
		return;
	}
}


void Scheduler::simulation()
{
	FromNewToREady();
	for (int i = 1; i < (NumFCFS + NumRR + NumSJF + 1); i++)
	{
		ProcessorsList.Data_found(i)->ProcessorAlgo();

	}
	FromBLKToReady();
	if (!(TimeStep % STL))
	{
		WorkStealing();
	}
	TimeStep++;
}


















void  Scheduler::DisplayFileData()
{
	cout << NumFCFS << " " << NumSJF << " " << NumRR << endl;
	cout << "Time Slice : " << TimeSlice << endl;
	cout << RTF << " " << MAxW << " " << STL << " " << ForkProbability << endl;
	cout << "No. Processors  : " << NoOfProceesors << endl;

	while (!NEW_List.empty())
	{
		NEW_List.front()->display();
		NEW_List.pop();
	}
	while (!kill.empty())
	{
		cout << kill.front().ProcessId << " " << kill.front().ProcessId << endl;
		kill.pop();
	}
}
