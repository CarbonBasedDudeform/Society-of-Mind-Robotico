#include "Approach.h"
#include "automata.h"

Approach::Approach(void) : ArAction("Approach")
{
	forward = new Forward();
	stop = new Stop();
	rotate = new Rotate();
}

Approach::~Approach(void)
{
	delete forward;
	delete rotate;
	delete stop;
}

void Approach::Update() {

}


ArActionDesired* Approach::fire(ArActionDesired currentDesired) {
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

	std::cout << "Approaching..." << std::endl;

	//check if going in the correct direction
	if (LowestReadingInfront())
	{
		//stop rotating/moving forward
		if (SensorLess(automata::LEFT_FRONT) && SensorLess(automata::RIGHT_FRONT)) //stop everything!
		{
			output << "1 0 0 1 0 " << now->tm_hour << ":" << now->tm_min
		<< ":" << now->tm_sec << endl;
			return stop->fire(currentDesired);
		} else if (SensorMore(automata::LEFT_FRONT) && SensorMore(automata::RIGHT_FRONT))
		{
			output << "1 0 1 0 0 " << now->tm_hour << ":" << now->tm_min
		<< ":" << now->tm_sec << endl;
			return forward->fire(currentDesired);
		}
	} else {
		//start rotating until lowestreading is infront
		int lowestReadingSensor = GetLowestReading();

		switch (lowestReadingSensor) {
			case automata::LEFT_FRONT:
			case automata::LEFT_FRONT_SIDE:
				rotate->Clockwise = true;
				break;
			case automata::RIGHT_FRONT:
			case automata::RIGHT_FRONT_SIDE:
				rotate->Clockwise = false;
				break;
		}

		output << "1 0 0 0 1 " << now->tm_hour << ":" << now->tm_min
		<< ":" << now->tm_sec << endl;

		return rotate->fire(currentDesired);
	}
	
	return &m_desire;
}

int Approach::GetLowestReading() {
	int lowestReadingSensor = 0;

	for (int i = 0; i < m_robot->getNumSonar(); i++)
	{
		if (GetSensorReading(i) < GetSensorReading(lowestReadingSensor) || i == 0) { //i == 0 because first reading will never be less than itself
			lowestReadingSensor = i;
		}
	}

	return lowestReadingSensor;
}

void Approach::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}

bool Approach::SensorLess(int sensor) {
	if ( (GetSensorReading(sensor) - m_robot->getRobotRadius() ) < threshold) return true;
	
	return false;
}

bool Approach::SensorMore(int sensor) {
	if ((GetSensorReading(sensor) - m_robot->getRobotRadius() ) > threshold) return true;

	return false;
}

bool Approach::LowestReadingInfront() {
	unsigned int lowestSensorReading = 6000; //higher than high can be
									//higher than the highest possible reading
	int sensor = -1; //no sensor
	for (int i = 0; i < m_robot->getNumSonar(); i++) {
		if (GetSensorReading(i) < lowestSensorReading)
		{
				lowestSensorReading = GetSensorReading(i);
				sensor = i;
		}
	}

	if (sensor == automata::LEFT_FRONT || sensor == automata::RIGHT_FRONT) return true;

	return false;
}

void Approach::setPower(float power) {
	threshold = THRESHOLD * power;
}