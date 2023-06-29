#include "Process.h"
Process::Process(int at, int pid, int ct, queue<IO>io)
{
	this->ArrivalTime = at;
	this->PID = pid;
	this->CPUTIME = ct;
	this->IoRequests = io;
}
void Process::display()
{
	cout << ArrivalTime << " " << PID << " " << CPUTIME << " ("<<IoRequests.front().IO_R<<","<<IoRequests.front().IO_D<<")" <<endl;
}
///_____setters_____////
void Process::SetResponseTime(int FirstTime)
{
	ResponseTime = FirstTime - ArrivalTime;
}

void Process::SetTerminationTime(int finshTime)
{
	TerminationTime = finshTime;
}
void Process::SetTurnaroundDuration()
{
	TurnarroudDuration = TerminationTime - ArrivalTime;
}
void Process::SetWsitingTime()
{
	WatingTime = TurnarroudDuration - CPUTIME;
}

void Process::SetCurrentCT()
{
    CurrentCT = CurrentCT + 1;
}



void Process::SetProcessState(int states) {


    //{ NEW, RDY, RUN, BLK, TRM, ORPH };
    switch (states) {
    case 0:
        this->state = ProcessState::NEW;
        break;
    case 1:
        this->state = ProcessState::RDY;
        break;
    case 2:
        this->state = ProcessState::RUN;
        break;
    case 3:
        this->state = ProcessState::BLK;
        break;
    case 4:
        this->state = ProcessState::TRM;
        break;
    case 5:
        this->state = ProcessState::ORPH;
        break;
    default:
        break;
    }

}


////____Getters_____////



int Process::GetResponseTime() const
{
    return ResponseTime;

}
int  Process::GetTerminationTime() const
{
    return TerminationTime;
}
int Process::GetTurnaroundDuration() const
{
    return TurnarroudDuration;
}
int Process::GetWsitingTime() const
{
    return WatingTime;
}
int Process::GetArrivalTime() const
{
    return ArrivalTime;
}
int Process::GetCPUTime() const
{
    return CPUTIME;
}
int Process::GetCurrentCT() const
{
    return CurrentCT;
}
IO Process::GetIOR() const
{
    return IoRequests.front();
}

int Process::GetIOQueueSize() const
{
    return IoRequests.size();
}



//////______Other Functions_______////
void Process::DeleteIO()
{
    IoRequests.pop();
}
