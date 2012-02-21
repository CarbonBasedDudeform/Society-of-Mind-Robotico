#pragma once
#include "Society of Mind.h"

class Accelerate : public ArAction, public automata
{
public:
	Accelerate(void);
	~Accelerate(void);

	virtual ArActionDesired *Accelerate::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	void setPower(float power);

private:
	int speed;
	float acceleration;
	static const int ACCELERATION_MAX = 100;
};
