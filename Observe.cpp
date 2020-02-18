#include "Observe.h"

const double Observe::PI = 3.14159265;
const double Observe::E = 2.71828183;

Observe::Observe(void) : ArAction("Observe")
{
	readings = new unsigned int*[DEFUALT_NUM_SENSORS];
	averageReadings = new int[DEFUALT_NUM_SENSORS];
	NumOfSensors = DEFUALT_NUM_SENSORS;
	threshold = MAX_THRESHOLD;
	numOfTicksToWait = MAX_NUM_TICKS;
	numOfTicks = 0;

	//initialise array
	for (int i = 0; i < NumOfSensors; ++i)
	{
		for (int j = 0; j < NumOfSensors; ++j)
		{
			readings[i] = new unsigned int[DEFUALT_NUM_SENSORS];
			readings[i][j] = MAX_READING;
		}

		averageReadings[i] = MAX_READING;
	}

	NumOfReadings = 1;

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

	ofstream output;
	output.open("output.txt", ios::app);
	time_t t;
	t = time(0);
	struct tm *now;
	now = localtime(&t);

	std::cout << "Observing..." <<std::endl;

	do {

		numOfTicks++;
		GetNewReadings();

		if ( AnalyseData()) {
			std::cout << "Found Ball." << std::endl;
			output << "0 0 0 1 0 " << now->tm_hour << ":" << now->tm_min
			<< ":" << now->tm_sec << endl;
			return stop->fire(currentDesired);
		}
	} while (numOfTicks < numOfTicksToWait);

	std::cout << "Didn't find ball" << std::endl;
	numOfTicks = 0;

	output << "0 0 0 0 0 " << now->tm_hour << ":" << now->tm_min
			<< ":" << now->tm_sec << endl;

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
	{
		for (int j = 0; j < NumOfReadings; j++)
		{
			readings[i][j] = GetSensorReading(j);//Gaussian(j);
		}
	}
	
	if (NumOfReadings < DEFUALT_NUM_SENSORS) {
		NumOfReadings++;
	}
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
			} 
		}
	}

	return false;
}

float Observe::Mean(int sensor) {
	float avg = 0;
	for (int i = 0; i < NumOfReadings; ++i)
	{
		avg += readings[i][sensor];
	}

	if (avg < 0 ) {
		for (int i = 0; i < DEFUALT_NUM_SENSORS; ++i)
			std::cout << "Reading["<<i<<"]: " << readings[i][sensor];
	}

	return ( avg / (float)NumOfReadings );
}

float Observe::Variance(int sensor) {
	float mean = Mean(sensor);

	float variance = 0;

	for (int i = 0; i < NumOfReadings; ++i)
	{
		variance += ( (readings[i][sensor] - mean) * (readings[i][sensor] - mean) );
	
	}

	return (variance / (float) NumOfReadings);
}

float Observe::StandardDeviation(int sensor) {
	float std = sqrt(Variance(sensor));
	return std;
}

float Observe::Gaussian(int sensor) {
	return GetSensorReading(sensor);
}

void Observe::setPower(float power) {
	threshold = MAX_THRESHOLD * power;
	numOfTicksToWait = MAX_NUM_TICKS * power;
}