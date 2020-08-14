#ifndef TASK_SCHEDULE
#define TASK_SCHEDULE
#include "sysDefine.h"
#include "sysFunc.h"
typedef void(*taskScheduleCallback)(int dayW, int hour, int min);
std::map < int , taskScheduleCallback > listTaskSchedule ;

uint32_t lastMin = -1;

void addTaskEvent(int id, taskScheduleCallback func){
	    std::pair < int, taskScheduleCallback > tmpPair(id, func);
		listTaskSchedule.insert(tmpPair);
}
void handlerTaskSchedule(){

	uint32_t dayW = ((calcEpochTime()  / 86400L) + 4 ) % 7; //0 is Sunday
	uint32_t hour = (calcEpochTime()   % 86400L) / 3600; 
	uint32_t min  = (calcEpochTime()  % 3600L) / 60; 
	if(min == lastMin){
		return;
	}
	for (std::pair < int, taskScheduleCallback > func : listTaskSchedule) {	
			func.second(dayW,hour,min);
		}
	lastMin=min;
}

#endif