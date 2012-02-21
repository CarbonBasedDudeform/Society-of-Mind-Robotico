#include "Rotate.h"

Rotate::Rotate(void) : ArAction("Rotate")
{
	Clockwise = true;
	velocity = MAX_VELOCITY;
}

Rotate::~Rotate(void)
{
}

ArActionDesired* Rotate::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	std::cout << "Rotating..." << std::endl;

	if (Clockwise) 
		m_desire.setRotVel(velocity);
	else
		m_desire.setRotVel(-velocity);

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

void Rotate::setPower(float power) {
	velocity = MAX_VELOCITY * power;
}