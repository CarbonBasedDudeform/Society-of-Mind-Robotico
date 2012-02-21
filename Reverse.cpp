#include "Reverse.h"

Backwards::Backwards(void) : ArAction("Reverse")
{
}

Backwards::~Backwards(void)
{
}

ArActionDesired* Backwards::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	std::cout << "Reversing..." << std::endl;

	m_desire.setVel(velocity);

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

void Backwards::setPower(float power) {
	velocity = MAX_VELOCITY * power;
}