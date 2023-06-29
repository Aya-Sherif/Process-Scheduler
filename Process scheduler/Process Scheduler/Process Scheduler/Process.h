#pragma once
#include <iostream>
#include<vector>
#include<queue>
#include<concurrent_priority_queue.h>
#include<stack>


using namespace std;
struct IO
{
    int IO_R;
    int IO_D;
};
class Process
{
    int PID;
    int ArrivalTime;//AT
    int ResponseTime;//RT
    int CPUTIME; //CT
    int RemaningTime;//RT
    int TerminationTime;//TT
    int TurnarroudDuration; // TRT
    int WatingTime;        // WT
    int CurrentCT=0;
    enum ProcessState{        NEW, RDY, RUN, BLK, TRM, ORPH    };
    ProcessState state;
    queue<IO> IoRequests;//Note the TO Will be removed from the queue when we transfar it from blok to Run again 
public:
    Process(int at, int pid, int ct, queue<IO>);
    void display();

    ///////______setters______////// 
   
    //Response time is the defference between arrival time and the time at which the process gets the CPU for the first time
    void SetResponseTime(int );
    //Termination Time when the process finishes execution
    void SetTerminationTime(int );
    //The total time a process spends in the system from its arrival to its termination ----> Turnaround Duration=Termination Time -Arrival Time
    void SetTurnaroundDuration();
    //The total time a process spends in the system not bing executed by the CPU  ----> wating time = turnaround duration - CPU 
    void SetWsitingTime();
    //This function to change between states{    NEW, RDY, RUN, BLK, TRM, ORPH  } 
    void SetProcessState(int );
    //The Process Time executed 
    void SetCurrentCT();


      



    ///////______Getters______////// 

    int GetResponseTime() const;  
    int GetTerminationTime( ) const;
    int GetTurnaroundDuration() const;
    int GetWsitingTime() const;
    int GetArrivalTime() const;
    int GetCPUTime() const;
    int GetCurrentCT() const;
    IO GetIOR() const;
    int GetIOQueueSize() const;



    //////____Other Functions______////
    void DeleteIO();
};

