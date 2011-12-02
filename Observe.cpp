#include "Observe.h"

Observe::Observe(int number_of_sensors)
{
	readings = new int[number_of_sensors][number_of_sensors];
	NumOfSensors = number_of_sensors;
}

Observe::~Observe(void)
{
}

ArActionDesired* Observe::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	
	return &m_desire;
}


void Observe::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}