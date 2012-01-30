#pragma once
#include "Society of Mind.h"

class Forward : public ArAction, public automata
{
public:
	Forward(void);
	~Forward(void);

	virtual ArActionDesired *Forward::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
private:
	static const int MAX_VELOCITY = 200;
};
