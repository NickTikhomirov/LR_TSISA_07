#pragma once
#include <vector>
#include "JobManager.h"
#include "Node.h"
#include "ConnectionTable.h"

using std::vector;

class Graph{
public:
	JobManager manager;
	vector<Node*> events;
	
	vector<Job*> awailable();
	Graph();
	~Graph();
};

