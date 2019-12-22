#include "SimultaneousNodes.h"

vector<Node*>* SimultaneousNodes::getStates() {
	return &contents;
}

bool SimultaneousNodes::isSimple() {
	return false;
}

SimultaneousNodes SimultaneousNodes::evolve(Node* a) {
	SimultaneousNodes* result = new SimultaneousNodes;
	result->contents.push_back(a);
	return *result;
}

