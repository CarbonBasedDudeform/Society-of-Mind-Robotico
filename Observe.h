#pragma once
#include "Society of Mind.h"

class Observe : public ArAction, public automata
{
public:
	Observe(void);
	~Observe(void);

	virtual ArActionDesired *Observe::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	bool AnalyseData();
	void GetNewReadings();

private:
	static const int MAX_READING = 5000;
	Stop* stop;
	int** readings;
	float* averageReadings;
	int NumOfSensors;
	int NumOfReadings;
	void StoreReadings();
	float CalcAverage(int sensor);

};
