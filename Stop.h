#pragma once
#include "Society of Mind.h"

class Stop : public ArAction, public automata
{
public:
	Stop(void);
	~Stop(void);

	virtual ArActionDesired *Stop::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	void setPower(float power);

private:
};
