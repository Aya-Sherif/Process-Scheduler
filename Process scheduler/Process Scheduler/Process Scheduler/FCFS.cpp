#include "FCFS.h"
FCFS::FCFS(Scheduler* scheduler) :Processor(scheduler)
{

}
bool FCFS::IsIDeal()
{
	if (RunProcess)
	{
		return false;
	}
	else
	{
		return true;
	}
}
 Process* FCFS::ReturnProces()
{
	  StealProcess = FCFSProcesses.Front();
	 FCFSProcesses.DeleteFirst();
	 SetTotalBusyTime(-StealProcess->GetCPUTime());
	 return StealProcess;

}
void FCFS::SetTotalTurnaroundTime(int t)
{
	TotalTAT = TotalTAT + t;
}

void FCFS::SetTotalProcessorIDLETime()
{
	TotalIdealTime++;
}
void FCFS::SetProcessorLoad()
{
	ProcessorLoad = totalBusyTime / TotalTAT;
}
void FCFS::SetProcessorUtilization()
{
	ProcessorUtilization = totalBusyTime / (totalBusyTime + TotalIdealTime);
}
void FCFS::Add_process(Process* p)
{
	FCFSProcesses.InsertEnd(p);
}
void FCFS::delete_process(Process* p)
{
	FCFSProcesses.DeleteFirst();
}

void FCFS::SetTotalBusyTime(int c)
{
	totalBusyTime = totalBusyTime + c;
}
void FCFS::SetRunProces()
{
	if (!FCFSProcesses.ISEMPTY())
	{
		RunProcess = FCFSProcesses.Front();
		RunProcess->SetProcessState(2);
		FCFSProcesses.DeleteFirst();
		//check if it will be migrated 
		int waiting = scheduler->GetCurrentTimeStep() - RunProcess->GetArrivalTime() - RunProcess->GetCurrentCT();
		if (waiting>scheduler->GetMaxW())
		{
			scheduler->ProcessMigration(2, RunProcess);

			SetRunProces();
		}
	}
}








/////////___________Getters____________/////////
int FCFS::GetTotalTurnaroundTime()
{
	return TotalTAT;

}
Process* FCFS::GetRunProcess()
{
	return RunProcess;
}
int FCFS::GetTotalBusyTime()
{
	return totalBusyTime;
}

/////////________FCFSALGO_____//////
void FCFS::ProcessorAlgo()
{
	if (FCFSProcesses.ISEMPTY() && IsIDeal())
	{
		SetTotalProcessorIDLETime();
	}
	else if (!FCFSProcesses.ISEMPTY() && IsIDeal())

	{
		SetRunProces();
		SetTotalBusyTime(-1);
		FCFSProcesses.Front()->SetCurrentCT();
		if (FCFSProcesses.Front()->GetCurrentCT() == FCFSProcesses.Front()->GetCPUTime())
		{
			scheduler->FromRunToTerm(FCFSProcesses.Front());
			SetRunProces();
		}
		else
		{
			if (scheduler->CheckIORequests(RunProcess))
			{
				//Set the total busy time of the cureent processor
				SetTotalBusyTime(-(RunProcess->GetCPUTime() - RunProcess->GetCurrentCT()));
				//set Another process to run state  
				SetRunProces();
			}


		}

	}
	else if (!IsIDeal())
	{
		SetTotalBusyTime(-1);
		FCFSProcesses.Front()->SetCurrentCT();
		if (FCFSProcesses.Front()->GetCurrentCT() == FCFSProcesses.Front()->GetCPUTime())
		{
			scheduler->FromRunToTerm(FCFSProcesses.Front());
			SetRunProces();
		}
		else
		{
			if (scheduler->CheckIORequests(RunProcess))
			{
				//Set the total busy time of the cureent processor
				SetTotalBusyTime(-(RunProcess->GetCPUTime() - RunProcess->GetCurrentCT()));
				//set Another process to run state  
				SetRunProces();
			}


		}

	}


}


