#include "Avoidance.h"
#include "automata.h"

#include <iostream>

Avoidance::Avoidance(void) : ArAction("Avoid")
{
	forward = new Forward();
	rotate = new Rotate();
	stop = new Stop();
}


Avoidance::~Avoidance(void)
{
	delete forward;
	delete rotate;
	delete stop;
}

ArActionDesired *Avoidance::fire(ArActionDesired currentDesired)	{
	m_desire.reset();

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	int lowestReadingSensor = GetLowestReading();

	if (SensorLess(lowestReadingSensor)) {
		switch (lowestReadingSensor) {
			//case automata::LEFT_FRONT_SIDE:
			//return forward->fire(currentDesired);
			//break;
		case automata::LEFT_SIDE:
		case automata::LEFT_FRONT:
		//case automata::LEFT_BACK:
			rotate->Clockwise = false;
			m_desire = *rotate->fire(currentDesired);
			m_desire.setVel(GetSensorReading(lowestReadingSensor) / 5000);
			return &m_desire;
			break;
		case automata::RIGHT_SIDE:
			return forward->fire(currentDesired);
			break;
		//case automata::RIGHT_FRONT_SIDE:
		case automata::RIGHT_FRONT:
		//case automata::RIGHT_BACK:
			rotate->Clockwise = true;
			m_desire = *rotate->fire(currentDesired);
			m_desire.setVel(GetSensorReading(lowestReadingSensor) / 5000); //prevent continual rotation
			return &m_desire;
			break;
		}
	}
		
	return forward->fire(currentDesired);
}

int Avoidance::GetLowestReading() {
	int lowestReadingSensor = 0;

	for (int i = 0; i < m_robot->getNumSonar(); i++)
	{
		if (GetSensorReading(i) < GetSensorReading(lowestReadingSensor)) {
			lowestReadingSensor = i;
		}

		if ( SensorLess(lowestReadingSensor) ) {
			return lowestReadingSensor;
		}
	}

	return lowestReadingSensor;
}
void Avoidance::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}



bool Avoidance::SensorLess(int sensor) {
	if ( (GetSensorReading(sensor) - m_robot->getRobotRadius() ) < THRESHOLD) return true;
	
	return false;
}

bool Avoidance::SensorMore(int sensor) {
	if ((GetSensorReading(sensor) - m_robot->getRobotRadius() ) > THRESHOLD) return true;

	return false;
}