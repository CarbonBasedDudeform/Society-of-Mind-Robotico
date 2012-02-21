#include "Hit.h"

Hit::Hit(void) : ArAction("Hit")
{
	approach = new Approach();
	accelerate = new Accelerate();
	observe = new Observe();
	threshold = 0;
	distanceToBall = DEFAULT_DISTANCE; 
	originalX = 0;
	originalY = 0;
}

Hit::~Hit(void)
{
	delete approach;
	delete accelerate;
	delete observe;
}

ArActionDesired* Hit::fire(ArActionDesired currentDesired) {
	m_desire.reset();

	if (m_sonar == NULL) {
		deactivate();
		return NULL;
	}

	std::cout << "Hitting.." << std::endl;

	if ( GetSensorReading(automata::LEFT_FRONT) < threshold ) {
		//record reading aka distance from robot to ball
		//travel a little further than that
		//then stop and observe
		RecordPosition();
		RecordDistance(automata::LEFT_FRONT);	

		if (ExceededDistance()) {
			return observe->fire(currentDesired);
		} else {
			return accelerate->fire(currentDesired);
		}
	} else if (GetSensorReading(automata::RIGHT_FRONT) < threshold) {
		RecordPosition();
		RecordDistance(automata::RIGHT_FRONT);
		
		if (ExceededDistance()) {
			return observe->fire(currentDesired);
		} else {
			return accelerate->fire(currentDesired);
		}
	} else {
		return approach->fire(currentDesired);
	}

	return &m_desire;
}

void Hit::RecordPosition() {
	if (distanceToBall == DEFAULT_DISTANCE)
	{
		originalX = m_robot->getX();
		originalY = m_robot->getY();
	}
}

void Hit::RecordDistance(int sensor) {
	if (distanceToBall == DEFAULT_DISTANCE)
		distanceToBall = m_robot->getSonarReading(sensor)->getPose().findDistanceTo(m_robot->getPose()) - m_robot->getRobotRadius();
}

bool Hit::ExceededDistance() {
	float distanceTravelled = sqrt( ( originalX - m_robot->getX() ) * ( originalX - m_robot->getX() )
								  + ( originalY - m_robot->getY() ) * ( originalY - m_robot->getY() ) );

	if (distanceTravelled > distanceToBall) return true;

	return false;
}

void Hit::setRobot(ArRobot *robot) {
	ArAction::setRobot(robot);
	m_sonar = robot->findRangeDevice("sonar");
	//myRobot is variable from aria, just using mine due to style
	m_robot = myRobot;
	if (robot == NULL) {
		ArLog::log(ArLog::Terse, "automata: found no sonar therefore deactivating");
		deactivate();
	}

	approach->setRobot(robot);
	observe->setRobot(robot);
}

void Hit::setPower(float power) {
	threshold = MAX_THRESHOLD * power;
}