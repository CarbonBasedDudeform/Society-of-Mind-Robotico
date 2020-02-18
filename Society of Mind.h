#pragma once
#include "automata.h"
#include "Aria.h"
#include "Stop.h"
#include "Forward.h"
#include "Reverse.h"
#include "Rotate.h"
#include "Accelerate.h"
#include <iostream>
#include <fstream>

using namespace std;

struct SUBAGENT {
	int type;
	float power;
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
