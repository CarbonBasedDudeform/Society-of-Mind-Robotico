#include "Avoidance.h"


Avoidance::Avoidance() : ArAction("Avoid")
{
	forward = new Forward();
	rotate = new Rotate();
	stop = new Stop();

	threshold = 200;
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

	ofstream output;
	output.open("output.txt", ios::app);
	time_t t;
	t = time(0);
	struct tm *now;
	now = localtime(&t);

	std::cout << "Avoiding..." << std::endl;

	int lowestReadingSensor = GetLowestReading();

	if (SensorLess(lowestReadingSensor)) {
		switch (lowestReadingSensor) {
		case automata::LEFT_FRONT:
		case automata::LEFT_FRONT_SIDE:
		case automata::LEFT_SIDE:
			rotate->Clockwise = false;
			m_desire = *rotate->fire(currentDesired);
			m_desire.setVel(GetSensorReading(lowestReadingSensor) / 5000);
			output << "0 1 0 0 1 " << now->tm_hour << ":" << now->tm_min
				<< ":" << now->tm_sec << endl;
			return &m_desire;
			break;
		case automata::RIGHT_SIDE:
		case automata::RIGHT_FRONT:
		case automata::RIGHT_FRONT_SIDE:
			rotate->Clockwise = true;
			m_desire = *rotate->fire(currentDesired);
			m_desire.setVel(GetSensorReading(lowestReadingSensor) / 5000); //prevent continual rotation
			output << "0 1 0 0 1 " << now->tm_hour << ":" << now->tm_min
				<< ":" << now->tm_sec << endl;
			return &m_desire;
			break;
		}
	} else {
		output << "0 1 1 0 0 " << now->tm_hour << ":" << now->tm_min
				<< ":" << now->tm_sec << endl;
	}

	output.close();
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