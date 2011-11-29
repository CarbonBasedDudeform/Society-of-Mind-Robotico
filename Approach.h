#pragma once
#include "Society of Mind.h"

class Approach : public ArAction, public automata
{
public:
	Approach(void);
	~Approach(void);
	
	void Update();
	virtual ArActionDesired *Approach::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
private:
	static const int THRESHOLD = 200;
	bool SensorLess(int sensor);
	bool SensorMore(int sensor);
	bool LowestReadingInfront();

	Forward* forward;
	Stop* stop;
	Rotate* rotate;

	int forwardPriority;
	int stopPriority;
	int rotatePriority;
};
