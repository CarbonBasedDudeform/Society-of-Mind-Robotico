#include "Aria.h"
#include "avoidance.h"
#include <iostream>
#include "Approach.h"

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

	Avoidance avoidance;
	robot.addAction(&avoidance, 20);
	//Approach approach;
	//robot.addAction(&approach, 100);

	//ArModeTeleop teleop(&robot, "teleop", 't', 'T');
	
	//rev those engines; turn the motors on
	robot.enableMotors();

	

	//set the robot running
	robot.runAsync(true);

	//parse command line args
	if(!Aria::parseArgs())
	{
		Aria::logOptions();
		Aria::exit(2);
	}

	while(1) { }

	Aria::shutdown();
	return 0;
}