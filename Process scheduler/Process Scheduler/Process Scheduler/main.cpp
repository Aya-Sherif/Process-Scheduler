#include "UI.h"
#include "Scheduler.h"
int main()
{
	Scheduler D;
	D.readinputfile("File.txt");
	D.CreatProcessors();
	D.simulation();
	//D.CreatProcessors();
	//D.FromNewToREady();
	//D.CheckIORequests();
	//D.DisplayFileData();
	
}