#pragma once
#include "automata.h"
#include "Approach.h"
#include "Observe.h"

class Hit: public ArAction, public automata
{
public:
	Hit(void);
	~Hit(void);

	virtual ArActionDesired *Hit::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	void setPower(float power);

private:
	static const int MAX_THRESHOLD = 400;
	static const int DEFAULT_DISTANCE = 10000;
	float threshold;
	
	void RecordPosition();
	void RecordDistance(int sensor);
	bool ExceededDistance();

	//Stop* stop;
	//Forward* forward;
	//Rotate* rotate;
	Accelerate* accelerate;
	Approach* approach;
	Observe* observe;

	float distanceToBall;
	float originalX;
	float originalY;
};

//the doom and gloom
//of your room
//as you write computer code
//stuck in your abode
//entertaining your chode until
//you blow your load
//and compile your code.
//error C2065: fuck not followed by cunt somwhere in your codebase, try line 15. that's not it and it's of no help at all but meh. C++, what a fucking cunt knobjockey asswipe of a language.