#pragma once
#include "Aria.h"

class automata
{
public:
	automata(void);
	~automata(void);

	static const enum SENSORS { LEFT_SIDE = 0, LEFT_FRONT_SIDE, LEFT_FRONT, 
								RIGHT_FRONT, RIGHT_FRONT_SIDE, RIGHT_SIDE, 
								RIGHT_BACK, LEFT_BACK };

	void run();

	void SetVelocity(double left, double right);
	double GetLeftVelocity();
	double GetRightVelocity();

	unsigned int GetSensorReading(int sensor);
	void setRobot(ArRobot *robot);
	float power;

protected:
	ArRangeDevice *m_sonar;
	ArRobot *m_robot;
	ArActionDesired m_desire;
};