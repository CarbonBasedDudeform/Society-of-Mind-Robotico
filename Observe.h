#pragma once
#include "automata.h"
#include "Explore.h"
#include "Stop.h"

class Observe : public ArAction, public automata
{
public:
	Observe(void);
	~Observe(void);

	virtual ArActionDesired *Observe::fire(ArActionDesired currentDesired);
	void setRobot(ArRobot *robot);
	bool AnalyseData();
	void GetNewReadings();
	void setPower(float power);
	static bool HasFoundBall;
	static const int MAX_RECURSE = 5;
	static int timesRecursed;
	
private:
	static const int MAX_READING = 5000;
	static const int DEFUALT_NUM_SENSORS = 5;
	static const int MAX_THRESHOLD = 10;
	static const int MAX_NUM_TICKS = 1000;
	static const int MAX_CONFIDENCE = 20;
	static const int MAX_READINGS = 20;
	int confidence;
	int numOfTicksToWait;
	int numOfTicks;
	float threshold;
	Stop* stop;
	Explore* explore;

	unsigned int** readings;
	int* averageReadings;
	int NumOfSensors;
	int NumOfReadings;
	void StoreReadings();

	

	//new methods for guassian stuff
	float StandardDeviation(int sensor);
	float Mean(int sensor);
	float Variance(int sensor); //standard deviation squared
	static const double PI;
	static const double E;
	float Gaussian(int sensor);
};
