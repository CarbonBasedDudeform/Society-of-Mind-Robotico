#pragma once
#include "Society of Mind.h"

class Explore : public ArAction, public automata
{
public:
	Explore(void);
	~Explore(void);
		
	virtual ArActionDesired *Explore::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
private:
	Approach *approach;
	Avoidance *avoidance;
	int TimesFired;
	static const int MAX_TIMES_FIRED = 30;
	bool Approaching;
};
