#include "Explore.h"

Explore::Explore(void) : ArAction("Explore")
{
	TimesFired = 0;
	threshold = MAX_THRESHOLD;
	Approaching = true;
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

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	TimesFired++;
	std::cout << "Exploring..." << std::endl;


	if (Approaching) {
		if (TimesFired > threshold) {
			Approaching = false;
			TimesFired = 0;
			return avoidance->fire(currentDesired);
		} else {
			return approach->fire(currentDesired);
		}
	} else {
		if (TimesFired > threshold) {
			Approaching = true;
			TimesFired = 0;
			return approach->fire(currentDesired);
		} else {
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

void Explore::setPower(float power) {
	threshold = MAX_THRESHOLD * power;
}