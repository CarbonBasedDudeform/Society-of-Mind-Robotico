#include "Explore.h"

Explore::Explore(void) : ArAction("Explore")
{
	TimesFired = 0;
	Approaching = true;
	approach = new Approach();
	avoidance = new Avoidance();
}

Explore::~Explore(void)
{
}

ArActionDesired* Explore::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	TimesFired++;

	if (Approaching) {
		if (TimeFired > MAX_TIMES_FIRED) {
			Approaching = false;
			TimesFired = 0;
			m_desire = avoidance;
		} else {
			m_desire = approach;
		}
	} else {
		if (TimeFired > MAX_TIMES_FIRED) {
			Approaching = true;
			TimesFired = 0;
			m_desire = approach;
		} else {
			m_desire = avoidance;
		}
	}

	return &m_desire;
}

void Explore::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}