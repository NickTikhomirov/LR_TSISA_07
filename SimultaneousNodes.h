#pragma once
#include "Node.h"

class SimultaneousNodes : public Node {
public:
	vector<Node*> contents;
	vector<Node*> getStates();

	bool isSimple();
};

