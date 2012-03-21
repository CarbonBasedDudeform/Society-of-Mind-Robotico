#pragma once
#include "Society of Mind.h"
#include "Approach.h"
#include "Observe.h"
#include "Explore.h"

class Hit: public ArAction, public automata
{
public:
	Hit(void);
	~Hit(void);

	virtual ArActionDesired *Hit::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	void setPower(float power);

	bool AttemptedToHitRecently;

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
	Explore* explore;

	float distanceToBall;
	float originalX;
	float originalY;

	static const int TICKS_THRESHOLD = 50;
	int ticks;
};