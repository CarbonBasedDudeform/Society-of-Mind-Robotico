#pragma once
#include "Society of Mind.h"
#include "Approach.h"
#include "avoidance.h"

class Explore : public ArAction, public automata
{
public:
	Explore(void);
	~Explore(void);
		
	virtual ArActionDesired *Explore::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	void setPower(float power);

private:
	Approach* approach;
	Avoidance* avoidance;
	int TimesFired;
	static const int MAX_THRESHOLD = 1000;
	float threshold;

	bool Approaching;
};
