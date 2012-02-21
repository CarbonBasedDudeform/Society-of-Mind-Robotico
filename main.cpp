#include "Aria.h"
#include "avoidance.h"
#include <iostream>
#include "Approach.h"
#include "Observe.h"
#include "Explore.h"
#include "Accelerate.h"
#include "Hit.h"

using namespace std;

enum ARCHITECTURE {
	SYNCHRONOUS,
	ASYNCHRONOUS,
	WEIGHT,
	LIST_ORDER,
	WEIGHT_ORDER
};

enum AGENTS {
	CONTROL,
	ACCELERATE,
	APPROACH,
	AVOIDANCE,
	REVERSE,
	EXPLORE,
	FORWARD,
	HIT,
	OBSERVE,
	ROTATE,
	STOP
};
 
int main(int argc, char** argv)
{
	if (argc < 6) {
		//pring usage
		return 0;
	}

	//initialised to a number less than zero so there is no defualt agent
	int agent = -1;
	string agentArg = string(argv[1]);
	if (agentArg == "Hit") {
		agent = HIT;
	} else if (agentArg == "Explore") {
		agent = EXPLORE;
	}

	int architecture_mode = -1;
	if (string(argv[2]) == "synchronous") {
		architecture_mode = SYNCHRONOUS;
	}

	int architecture_order = -1;
	if (string(argv[3]) == "weight") {
		architecture_order = WEIGHT;
	}

	float strength = -1;
	strength = atof(argv[4]);
	int subagent = -1;
	if (string(argv[4]) == "hit") {
		subagent = HIT;
	}

	float subagent_strength = atof(argv[5]);

	//setup robot connection
	Aria::init();
	ArArgumentParser parser(&argc, argv);
	
	parser.loadDefaultArguments();

	ArKeyHandler handlerOfKeys;
	Aria::setKeyHandler(&handlerOfKeys);

	ArRobot robot;
	robot.attachKeyHandler(&handlerOfKeys);
	ArRobotConnector robotConnector(&parser, &robot);

	//attempt to connect
	if (!robotConnector.connectRobot(&robot)) 
	{
		std::cout << "Error connecting to robot" << std::endl;
		Aria::exit(1);
	}

	ArSonarDevice sonar;
	robot.addRangeDevice(&sonar);

	Hit hit;
	Explore explore;
	switch(agent) {
		case HIT:
			hit.setPower(strength);
			robot.addAction(&hit, 50);
			break;
		case EXPLORE:
			explore.setPower(strength);
			robot.addAction(&explore, 50);
			break;
	}
	
	robot.enableMotors();

	//set the robot running
	robot.runAsync(true);

	//parse command line args
	if(!Aria::parseArgs())
	{
		Aria::logOptions();
		Aria::exit(2);
	}

	while(!Observe::HasFoundBall) {
		if (Observe::HasFoundBall) Aria::shutdown();
	}

	//Aria::shutdown();
	return 0;
}