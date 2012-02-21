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
	void setPower(float power);

private:
	static const int THRESHOLD = 200;
	float threshold;

	bool SensorLess(int sensor);
	bool SensorMore(int sensor);
	bool LowestReadingInfront();

	Forward* forward;
	Stop* stop;
	Rotate* rotate;
};
