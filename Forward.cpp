#include "Forward.h"

Forward::Forward(void) : ArAction("Forward")
{
}

Forward::~Forward(void)
{
}

ArActionDesired* Forward::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	m_desire.setVel(MAX_VELOCITY);

	return &m_desire;
}

void Forward::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}
