#include "SJF.h"
SJF::SJF(Scheduler* s) :Processor(s)
{

}




bool SJF::IsIDeal()
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
void SJF::SetTotalTurnaroundTime(int t)
{
	TotalTAT = TotalTAT + t;
}

void SJF::SetTotalProcessorIDLETime()
{
	TotalIdealTime++;
}
void SJF::SetProcessorLoad()
{
	ProcessorLoad = totalBusyTime / TotalTAT;
}
void SJF::SetProcessorUtilization()
{
	ProcessorUtilization = totalBusyTime / (totalBusyTime + TotalIdealTime);
}
void SJF::Add_process(Process* p)
{
	SJFProcessoes.push(p);
}
void SJF::delete_process(Process* p)
{
	SJFProcessoes.pop();
}
void SJF::SetTotalBusyTime(int c)
{
	totalBusyTime = totalBusyTime + c;
}

void SJF::SetRunProces()
{
	if (SJFProcessoes.size() != 0)
	{
		RunProcess = SJFProcessoes.top();
		RunProcess->SetProcessState(2);
		SJFProcessoes.pop();

	}
}






/////////___________Getters____________/////////
int SJF::GetTotalTurnaroundTime()
{
	return TotalTAT;

}
Process* SJF::GetRunProcess()
{
	return RunProcess;
}
int SJF::GetTotalBusyTime()
{
	return totalBusyTime;
}



/////////________FCFSALGO_____//////
void SJF::ProcessorAlgo()
{
	if (SJFProcessoes.size() == 0 && IsIDeal())
	{
		SetTotalProcessorIDLETime();
	}
	else if(SJFProcessoes.size() != 0 && IsIDeal())
	{
		SetRunProces();
		SetTotalBusyTime(-1);
		SJFProcessoes.top()->SetCurrentCT();
		if (SJFProcessoes.top()->GetCurrentCT() == SJFProcessoes.top()->GetCPUTime())
		{
			scheduler->FromRunToTerm(SJFProcessoes.top());
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
		SJFProcessoes.top()->SetCurrentCT();
		if (SJFProcessoes.top()->GetCurrentCT() == SJFProcessoes.top()->GetCPUTime())
		{
			scheduler->FromRunToTerm(SJFProcessoes.top());
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