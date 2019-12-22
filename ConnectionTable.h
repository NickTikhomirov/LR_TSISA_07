#pragma once
#include "Job.h";
#include "Node.h";

using std::pair;

class ConnectionTable {
	ConnectionTable();
	static ConnectionTable* instance;
public:
	static ConnectionTable* getConnectionTable();

	unordered_map<Job*, pair<Node*, Node*>> contents;
	Job* insert(Node*, Node*, Job*);
	//todo ���������������???
	vector<char> getDoneJobs(Node*);
	
	~ConnectionTable();
};

