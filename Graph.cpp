#include "Graph.h"

Graph::Graph() {
	ConnectionTable* connectionTable = ConnectionTable::getConnectionTable();
	events.resize(25, nullptr);
	events[0] = new Node;


	connectionTable->evaluateEarly();
}


Graph::~Graph()
{
}

vector<Job*> Graph::awailable() {
	vector<Job*> result;
	for (size_t i = 0; i < manager.todo.size(); ++i){
		if(!manager.isDone(i)){
			bool fits = true;
			for (auto r : manager[i].requiredJobs()) {
				if (!manager.isDone(r)) {
					fits = false;
					break;
				}
			}
			if(fits) {
				result.push_back(&(manager[i]));
			}
		}
	}
	return result;
}