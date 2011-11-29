#pragma once
#include "Society of Mind.h"

class Backwards : public ArAction, public automata
{
public:
	Backwards(void);
	~Backwards(void);

	virtual ArActionDesired *Backwards::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
private:
	static const int MAX_VELOCITY = -100;
};
