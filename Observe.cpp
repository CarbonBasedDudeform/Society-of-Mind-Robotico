#include "Observe.h"

const double Observe::PI = 3.14159265;
const double Observe::E = 2.71828183;
int Observe::timesRecursed = 0;

Observe::Observe(void) : ArAction("Observe")
{
	readings = new float*[DEFUALT_NUM_SENSORS];
	averageReadings = new float[DEFUALT_NUM_SENSORS];
	NumOfSensors = DEFUALT_NUM_SENSORS;
	threshold = MAX_THRESHOLD;
	numOfTicksToWait = MAX_NUM_TICKS;
	numOfTicks = 0;

	//initialise array
	for (int i = 0; i < NumOfSensors; ++i)
	{
		for (int j = 0; j < NumOfSensors; ++j)
		{
			readings[i] = new float[DEFUALT_NUM_SENSORS];
			readings[i][j] = MAX_READING;
		}

		averageReadings[i] = MAX_READING;
	}

	NumOfReadings = 0;

	stop = new Stop();
	explore = new Explore();

	confidence = 0;
}

Observe::~Observe(void)
{
}

bool Observe::HasFoundBall = false;

ArActionDesired* Observe::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	std::cout << "Observing..." <<std::endl;

	do {

		numOfTicks++;
		GetNewReadings();

		if ( AnalyseData()) {
			std::cout << "Found Ball." << std::endl;
			//HasFoundBall = true;
			return stop->fire(currentDesired);
		}
	} while (numOfTicks < numOfTicksToWait);

	std::cout << "Didn't find ball" << std::endl;
	numOfTicks = 0;

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

	stop->setRobot(robot);
	explore->setRobot(robot);
}

void Observe::GetNewReadings() {
	for (int i = 0; i < DEFUALT_NUM_SENSORS; i++)
		for (int j = 0; j < DEFUALT_NUM_SENSORS; j++)
		{
			readings[i][j] = Gaussian(j);
			//std::cout << "reading: " << readings[i][j] << std::endl;
		}

	if (NumOfReadings < NumOfSensors) 
		NumOfReadings++;
}

bool Observe::AnalyseData() {
	confidence = 0;

	for (int i = 0; i < DEFUALT_NUM_SENSORS; ++i) {
		for (int j = 0; j < DEFUALT_NUM_SENSORS; ++j) {
				float stdev = StandardDeviation(j);
				if (stdev >= MAX_THRESHOLD) { 
				confidence++;
				std::cout << "Confidence: [" << confidence << "]" << std::endl;
				if (confidence >= MAX_CONFIDENCE) 
				{
					std::cout << "Observed Change." << std::endl;
					confidence = 0;
					return true;
				} 
			} //else { if (confidence > 0) confidence--;std::cout << "Confidence: [" << confidence << "]" << std::endl; }
		}
	}

	return false;
}

float Observe::Mean(int sensor) {
	float avg = 0;
	for (int i = 0; i < DEFUALT_NUM_SENSORS; ++i)
	{
		avg += readings[i][sensor];
		//std::cout << "reading: " << readings[i][sensor] << " Avg: " << avg << std::endl;
	}

	if (avg < 0 ) {
		for (int i = 0; i < DEFUALT_NUM_SENSORS; ++i)
			std::cout << "Reading["<<i<<"]: " << readings[i][sensor];
	}

	//std::cout << "Avg: " << avg << " ret: " << avg / (float)NumOfReadings << std::endl;
	return ( avg / (float)DEFUALT_NUM_SENSORS );
}

float Observe::Variance(int sensor) {
	float mean = Mean(sensor);
	//std::cout << "Mean: " << mean << std::endl;

	float variance = 0;

	for (int i = 0; i < DEFUALT_NUM_SENSORS; ++i)
	{
		//std::cout << "reading: " << readings[i][sensor] << " Mean: " << mean << " Var: " << variance << std::endl;
		variance += ( (readings[i][sensor] - mean) * (readings[i][sensor] - mean) );
	
	}

	return (variance / (float) NumOfReadings);
}

float Observe::StandardDeviation(int sensor) {
	float std = sqrt(Variance(sensor));
	//std::cout << "std: " << std << std::endl;
	return std;
}

float Observe::Gaussian(int sensor) {
	return GetSensorReading(sensor);
}

void Observe::setPower(float power) {
	threshold = MAX_THRESHOLD * power;
	numOfTicksToWait = MAX_NUM_TICKS * power;
}