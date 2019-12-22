#pragma once
#include <vector>
#include "JobManager.h"
#include "Node.h"
#include "ConnectionTable.h"

using std::vector;

class Graph{
public:
	static ConnectionTable* connectionTable;
	JobManager manager;
	vector<Node*> events;
	vector<size_t> finishes;
	vector<Job*> awailable;

	void doJob(char job, size_t i);
	void updateFinishes();
	void updateAwailable(Node*);
	void uniteWith(int, Node*);
	Graph();
	~Graph();
};

