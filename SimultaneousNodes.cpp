#include "SimultaneousNodes.h"

vector<Node*> SimultaneousNodes::getStates() {
	return contents;
}

bool SimultaneousNodes::isSimple() {
	return false;
}

