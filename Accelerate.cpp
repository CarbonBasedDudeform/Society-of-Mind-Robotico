#include "Accelerate.h"

Accelerate::Accelerate(void) : ArAction("Accelerate")
{
	speed = 0;
	acceleration = 50; //default value
}

Accelerate::~Accelerate(void)
{
}

ArActionDesired* Accelerate::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	std::cout << "Accelerating..." << std::endl;
	m_desire.setVel(speed += acceleration);
	
	return &m_desire;
}

void Accelerate::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}

void Accelerate::setPower(float power) {
	acceleration = ACCELERATION_MAX * power;
}
