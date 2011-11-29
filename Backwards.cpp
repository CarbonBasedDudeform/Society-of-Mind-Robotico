#include "Backwards.h"

Backwards::Backwards(void) : ArAction("Backwards")
{
}

Backwards::~Backwards(void)
{
}

ArActionDesired* Backwards::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	m_desire.setVel(MAX_VELOCITY);

	return &m_desire;
}

void Backwards::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}
