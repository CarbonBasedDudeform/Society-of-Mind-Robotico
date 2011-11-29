#include "Rotate.h"

Rotate::Rotate(void) : ArAction("Rotate")
{
	Clockwise = true;
}

Rotate::~Rotate(void)
{
}

ArActionDesired* Rotate::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	if (Clockwise) 
		m_desire.setRotVel(MAX_VELOCITY);
	else
		m_desire.setRotVel(-MAX_VELOCITY);

	return &m_desire;
}

void Rotate::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}
