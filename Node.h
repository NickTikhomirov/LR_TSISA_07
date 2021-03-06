#pragma once
#include <utility>
#include <vector>
#include "Job.h"

using std::size_t;
using std::vector;

class Node {
public:
	Node();
	Node* nonFake = nullptr;
	bool isFinish = true;
	virtual vector<Node*>* getStates();
	virtual bool isSimple();
};

