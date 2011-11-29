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
}

ArActionDesired *Avoidance::fire(ArActionDesired currentDesired)	{
	m_desire.reset();
	
	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	int lowestReadingSensor = GetLowestReading();

	double left_vel = m_robot->getVel();
	double right_vel = m_robot->getVel();
	//int test = GetSensorReading(lowestReadingSensor);

	if (SensorLess(lowestReadingSensor)) {
		switch (lowestReadingSensor) {
		case automata::LEFT_FRONT_SIDE:
			//left_vel = 1;
			//right_vel = 1;
			return forward->fire(currentDesired);
			break;
		case automata::LEFT_SIDE:
		case automata::LEFT_FRONT:
		case automata::LEFT_BACK:
			//left_vel = ( ( (double)GetSensorReading(lowestReadingSensor) - m_robot->getRobotRadius() ) / ( (double)THRESHOLD + m_robot->getRobotRadius() ) );//(double)m_sonar->getMaxRange() );
			//right_vel = 1;
			rotate->Clockwise = false;
			return rotate->fire(currentDesired);
			break;
		case automata::RIGHT_SIDE:
			//left_vel = 1;
			//right_vel = 1;
			return forward->fire(currentDesired);
			break;
		case automata::RIGHT_FRONT_SIDE:
		case automata::RIGHT_FRONT:
		case automata::RIGHT_BACK:
			//left_vel = 1;
			//right_vel = ( ( (double)GetSensorReading(lowestReadingSensor) - m_robot->getRobotRadius() )   / ( (double)THRESHOLD + m_robot->getRobotRadius() ) );// (double)m_sonar->getMaxRange() );
			rotate->Clockwise = true;
			return rotate->fire(currentDesired);
			break;
		}
	} else {
		//left_vel = 1;
		//right_vel = 1;
		return forward->fire(currentDesired);
	}


	//m_robot->setVel2(left_vel * 100, right_vel * 100);

	return &m_desire;
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