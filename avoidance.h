#pragma once
#include "Society of Mind.h"

class Avoidance : public ArAction, public automata
{
public:
	Avoidance(void);
	~Avoidance(void);

	//unsigned int GetSensorReading(int sensor);
	virtual ArActionDesired *Avoidance::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);

private:

	static const int THRESHOLD = 1500;

	bool SensorLess(int sensor);
	bool SensorMore(int sensor);
	int GetLowestReading();

	Forward *forward;
	Rotate *rotate;
	Stop *stop;
};

