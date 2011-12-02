#pragma once
#include "Society of Mind.h"

class Observe : public ArAction, public automata
{
public:
	Observe(int number_of_sensors);
	~Observe(void);

	virtual ArActionDesired *Observe::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	bool AnalyseData();
	void GetNewReadings();

private:
	static const int MAX_READING = 5000;
	Stop* stop;
	int* readings;
	int NumOfSensors;
	void StoreReadings();

};
