#include "Aria.h"
#include "avoidance.h"
#include <iostream>
#include "Approach.h"
#include "Observe.h"
#include "Explore.h"
#include "Accelerate.h"
#include "Hit.h"
#include "Reverse.h"
#include "Stop.h"

using namespace std;

enum ARCHITECTURE {
	SYNCHRONOUS,
	ASYNCHRONOUS,
	WEIGHT,
	LIST_ORDER,
	WEIGHT_ORDER
};


SUBAGENT* subagents[10];
int numOfSubagents = 0;
 
int main(int argc, char** argv)
{
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

	//ArModeTeleop teleop(&robot, "teleop", 't', 'T');
	Hit hit;
	//Hit hit;
	hit.setPower(1.0f);
	robot.addAction(&hit, 50);

	ofstream output;
	output.open("output.txt", ios::app);
	output << "Hit Explore Accelerate Observe Approach Avoidance Forward Stop Rotate" << std::endl;

	robot.enableMotors();

	//set the robot running
	robot.runAsync(true);

	//parse command line args
	if(!Aria::parseArgs())
	{
		Aria::logOptions();
		Aria::exit(2);
	}

	while(true) {
		if (Observe::HasFoundBall) {
			Aria::shutdown();
			return 0;
		}
	}

	return 0;
}