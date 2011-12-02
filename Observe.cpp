#include "Observe.h"

Observe::Observe(void) : ArAction("Observe")
{
	readings = new int*[5];
	averageReadings = new float[5];
	NumOfSensors = 5;

	//initialise array
	for (int i = 0; i < NumOfSensors; ++i)
	{
		for (int j = 0; j < NumOfSensors; ++j)
		{
			readings[i] = new int[5];
			readings[i][j] = MAX_READING;
		}

		averageReadings[i] = MAX_READING;
	}


	NumOfReadings = 0;
}

Observe::~Observe(void)
{
}

#include <iostream>

ArActionDesired* Observe::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	std::cout << "Observe firing... ";

	GetNewReadings();

	if (AnalyseData()) std::cout << "Detected change" << std::endl;

	return &m_desire;
}


void Observe::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}
}

void Observe::GetNewReadings() {
	for (int i = 0; i < NumOfReadings; ++i)
		for (int j = 0; j < NumOfSensors; ++j)
			readings[i][j] = GetSensorReading(j);

	if (NumOfReadings >= NumOfSensors) NumOfReadings = 0;
	else NumOfReadings++;
}

bool Observe::AnalyseData() {
	for (int i = 0; i < NumOfReadings; ++i) {
		for (int j = 0; j < NumOfSensors; ++j) {
			if (CalcAverage(j) != averageReadings[j]) {
				averageReadings[j] = CalcAverage(j);
				
				return true;
			}
std::cout << "calced " << j << ": " << CalcAverage(j);
			averageReadings[j] = CalcAverage(j);
		}
	}

	return false;
}

float Observe::CalcAverage(int sensor) {
	float avg = 0;
	for (int i = 0; i < NumOfReadings; ++i)
		avg += readings[i][sensor];

	return ( avg / (float)NumOfReadings );
}
