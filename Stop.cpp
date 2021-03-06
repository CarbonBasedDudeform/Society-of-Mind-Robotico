#include "Stop.h"

Stop::Stop(void) : ArAction("Stop")
{
}

Stop::~Stop(void)
{
}
ArActionDesired* Stop::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	std::cout << "Stopping..." << std::endl;
	m_desire.setVel(0); //MAX_THRESH - THRESHOLD 
	m_desire.setRotVel(0);

	return &m_desire;
}

void Stop::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}

void Stop::setPower(float power) {
	//THRESHOLD = power * MAX_THRESH
}

