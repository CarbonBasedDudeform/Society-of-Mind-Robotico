#include "Explore.h"

#include <iostream>

Explore::Explore(void) : ArAction("Explore")
{
	TimesFired = 0;
	Approaching = true;
	std::cout << "Creating objects..." << std::endl;

	approach = new Approach();
	avoidance = new Avoidance();
}

Explore::~Explore(void)
{
	delete approach;
	delete avoidance;
}

ArActionDesired* Explore::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	TimesFired++;
	std::cout << "Firing..." << std::endl;


	if (Approaching) {
		if (TimesFired > MAX_TIMES_FIRED) {
			Approaching = false;
			TimesFired = 0;
			std::cout << "1 avoiding..." << std::endl;
			return avoidance->fire(currentDesired);
		} else {
			std::cout << "1 approaching..." << std::endl;
			return approach->fire(currentDesired);
		}
	} else {
		if (TimesFired > MAX_TIMES_FIRED) {
			Approaching = true;
			TimesFired = 0;
			std::cout << "2 approaching..." << std::endl;
			return approach->fire(currentDesired);
		} else {
			std::cout << "2 avoidance..." << std::endl;
			return avoidance->fire(currentDesired);
		}
	}

	return &m_desire;
}

void Explore::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	approach->setRobot(robot);
	avoidance->setRobot(robot);

	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}