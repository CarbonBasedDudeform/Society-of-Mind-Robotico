#include "Avoidance.h"


Avoidance::Avoidance() : ArAction("Avoid")
{
	forward = new Forward();
	rotate = new Rotate();
	stop = new Stop();

	threshold = 300;
}


Avoidance::~Avoidance(void)
{
	delete forward;
	delete rotate;
	delete stop;
}

ArActionDesired *Avoidance::fire(ArActionDesired currentDesired)	{
	m_desire.reset();

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	std::cout << "Avoiding..." << std::endl;

	int lowestReadingSensor = GetLowestReading();

	std::cout << "lowest: " << lowestReadingSensor << std::endl;

	if (SensorLess(lowestReadingSensor)) {
		switch (lowestReadingSensor) {
		case automata::LEFT_FRONT:
		case automata::LEFT_FRONT_SIDE:
		case automata::LEFT_SIDE:
			rotate->Clockwise = false;
			m_desire = *rotate->fire(currentDesired);
			m_desire.setVel(GetSensorReading(lowestReadingSensor) / 5000);
			return &m_desire;
			break;
			//return forward->fire(currentDesired);
			//break;
		case automata::RIGHT_SIDE:
		case automata::RIGHT_FRONT:
		case automata::RIGHT_FRONT_SIDE:
			rotate->Clockwise = true;
			m_desire = *rotate->fire(currentDesired);
			m_desire.setVel(GetSensorReading(lowestReadingSensor) / 5000); //prevent continual rotation
			return &m_desire;
			break;
		}
	}
		
	return forward->fire(currentDesired);
}

int Avoidance::GetLowestReading() {
	int lowestReadingSensor = 0;

	for (int i = 0; i < m_robot->getNumSonar(); i++)
	{
		if (GetSensorReading(i) < GetSensorReading(lowestReadingSensor) || i == 0) { //i == 0 because first reading will never be less than itself
			lowestReadingSensor = i;
		}

		if ( SensorLess(lowestReadingSensor) ) {
			return lowestReadingSensor;
		}
	}

	return lowestReadingSensor;
}
void Avoidance::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}



bool Avoidance::SensorLess(int sensor) {
	if ( (GetSensorReading(sensor) - m_robot->getRobotRadius() ) < threshold) return true;
	
	return false;
}

bool Avoidance::SensorMore(int sensor) {
	if ((GetSensorReading(sensor) - m_robot->getRobotRadius() ) > threshold) return true;

	return false;
}

void Avoidance::setPower(float power) {
	threshold = THRESHOLD * power;
}