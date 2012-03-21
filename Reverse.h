#pragma once
#include "Society of Mind.h"

class Reverse : public ArAction, public automata
{
public:
	Reverse(void);
	~Reverse(void);

	virtual ArActionDesired *Reverse::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	void setPower(float power);

private:
	static const int MAX_VELOCITY = -100;
	float velocity;
};
