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
	void setPower(float power);

private:
	int NumOfSubagents;
	ArAction* Subagents;
	static const int THRESHOLD = 1500;
	float threshold;

	bool SensorLess(int sensor);
	bool SensorMore(int sensor);
	int GetLowestReading();

	Forward *forward;
	Rotate *rotate;
	Stop *stop;
};

