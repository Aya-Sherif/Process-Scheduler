#include "RR.h"
RR::RR(int T, Scheduler* s) :Processor(s)
{
	TimeSlice = T;
}


bool RR::IsIDeal()
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
void RR::SetTotalTurnaroundTime(int t)
{
	TotalTAT = TotalTAT + t;
}

void RR::SetTotalProcessorIDLETime()
{
	TotalIdealTime++;
}
void RR::SetProcessorLoad()
{
	ProcessorLoad = totalBusyTime / TotalTAT;
}
void RR::SetProcessorUtilization()
{
	ProcessorUtilization = totalBusyTime / (totalBusyTime + TotalIdealTime);
}
void RR::Add_process(Process* p)
{
	RRProcesses.push(p);
}
void RR::delete_process(Process* p)
{
	RRProcesses.pop();
}

void RR::SetTotalBusyTime(int c)
{
	totalBusyTime = totalBusyTime + c;
}



void RR::SetRunProces()
{
	if (RRProcesses.size() != 0)
	{
		RunProcess = RRProcesses.front();
		RunProcess->SetProcessState(2);
		RRProcesses.pop();
	}
}









/////////___________Getters____________/////////
int RR::GetTotalTurnaroundTime()
{
	return TotalTAT;

}
Process* RR::GetRunProcess()
{
	return RunProcess;
}
int RR::GetTotalBusyTime()
{
	return totalBusyTime;
}



/////////________RRALGO_____//////
void RR::ProcessorAlgo()
{
	if (RRProcesses.size() == 0)
	{
		SetTotalProcessorIDLETime();
	}
	else if (RRProcesses.size() != 0 && IsIDeal())
	{
		SetRunProces();
		RunProcess->SetCurrentCT();
		SetTotalBusyTime(-1);
		if (countTime == TimeSlice)
		{
			if (RunProcess->GetCurrentCT() == RunProcess->GetCPUTime())
			{
				scheduler->FromRunToTerm(RunProcess);
				SetRunProces();
				countTime = 0;
			}
			else
			{
				if (scheduler->CheckIORequests(RunProcess))
				{
					SetRunProces();
					countTime = 0;
				}
			}
		}
		else
		{
			if (RunProcess->GetCPUTime() == RunProcess->GetCurrentCT())
			{
				scheduler->FromRunToTerm(RunProcess);
				SetRunProces();
				countTime = 0;
			}
			else
			{
				if (scheduler->CheckIORequests(RunProcess))
				{
					SetRunProces();
					countTime = 0;
				}
				else
				{
					countTime++;
				}


			}
		}
	}
	else
	{
		RunProcess->SetCurrentCT();
		SetTotalBusyTime(-1);
		if (countTime == TimeSlice)
		{
			if (RunProcess->GetCurrentCT() == RunProcess->GetCPUTime())
			{
				scheduler->FromRunToTerm(RunProcess);
				SetRunProces();
				countTime = 0;
			}
			else
			{
				if (scheduler->CheckIORequests(RunProcess))
				{
					SetRunProces();
					countTime = 0;
				}
			}
		}
		else
		{
			if (RunProcess->GetCPUTime() == RunProcess->GetCurrentCT())
			{
				scheduler->FromRunToTerm(RunProcess);
				SetRunProces();
				countTime = 0;
			}
			else
			{
				if (scheduler->CheckIORequests(RunProcess))
				{
					SetRunProces();
					countTime = 0;
				}
				else
				{
					countTime++;
				}

			}

		}



	}



}