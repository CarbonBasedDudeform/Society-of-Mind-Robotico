#include "automata.h"

automata::automata(void) {
}

automata::~automata(void) {
}


unsigned int automata::GetSensorReading(int sensor) {

	ArSensorReading* reading = m_robot->getSonarReading(sensor);

	return reading->getRange();
}