#pragma once
#include "Society of Mind.h"

class Rotate : public ArAction, public automata
{
public:
	Rotate(void);
	~Rotate(void);

	virtual ArActionDesired *Rotate::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	bool Clockwise;
private:
	static const int MAX_VELOCITY = 100;
};
