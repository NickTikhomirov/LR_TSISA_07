#pragma once
#include "Job.h";
#include "Node.h";


class ConnectionTable {
	ConnectionTable();
	static ConnectionTable* instance;
public:
	struct Triple {
		Node* left;
		Node* right;
		Job* job;
		Triple(Node* l = nullptr, Node* r = nullptr, Job* j = nullptr);
	};
	static ConnectionTable* getConnectionTable();


	vector<Triple> contents;
	Job* insert(Node*, Node*, Job*);
	vector<char> getDoneJobs(Node*);
	void evaluateEarly();
	~ConnectionTable();
};

