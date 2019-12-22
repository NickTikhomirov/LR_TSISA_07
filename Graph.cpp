#include "Graph.h"

ConnectionTable* Graph::connectionTable = ConnectionTable::getConnectionTable();

using std::move;

Graph::Graph() {
	events.resize(25, nullptr);
	events[0] = new Node;
	while (manager) {
		updateFinishes();
		for (size_t i = 0; i < finishes.size(); ++i) {
			updateAwailable(events[finishes[i]]);
			if (awailable.size() == 0) {
				if (i == finishes.size() - 1) continue;

			}
		}
	}

}


Graph::~Graph(){}



void Graph::doJob(char job, size_t i) {
	
	
}

void Graph::updateFinishes() {
	finishes.clear();
	for(size_t i=0; i<events.size(); ++i){
		if (events[i] == nullptr) continue;
		if (events[i]->isFinish)
			finishes.push_back(i);
	}
}

void Graph::updateAwailable(Node* pos) {
	vector<Job*> result;
	vector<char> base = connectionTable->getDoneJobs(pos);
	bool fail = false;
	for(size_t i=0; i<manager.todo.size(); ++i){
		if (manager.isDone(i)) continue;
		unordered_set<char> requirements = manager[i].requiredJobs();
		for (auto r : requirements) {
			if (find(base.begin(), base.end(), r) == base.end()) {
				fail = true;
				break;
			}
		}
		if (!fail) result.push_back(&manager[i]);
	}
	awailable = move(result);
}


void Graph::uniteWith(int i, Node* b) {
	Node* a = events[i];
	events[i] = nullptr;

}

