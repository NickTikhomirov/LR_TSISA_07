#include "Graph.h"


#include <iostream>
using namespace std;

ConnectionTable* Graph::connectionTable = ConnectionTable::getConnectionTable();

using std::move;

Graph::Graph() {
	events.resize(25, nullptr);
	events[0] = new Node;
	while (manager) {
		updateFinishes();
		--hugeProstoi;
		for (size_t i = 0; i < finishes.size(); ++i) {
			bool temp = false;
			if (updateAwailable(finishes[i])) {
				hugeProstoi = 3;
				break;
			}
			for (size_t j = 0; j < awailable.size(); ++j) {
				doJob(awailable[j], finishes[i]);
				temp = true;
			}
			if(temp) finishes[i] = 0;
		}
	}

}


Graph::~Graph(){}



void Graph::doJob(Job* job, size_t i) {
	manager.do_(*job);
	events[i]->isFinish = false;
	size_t fin = i + Job::contents[*job];
	Node* f = events[fin];
	if (!f) events[fin] = new Node;
	connectionTable->insert(events[i], events[fin], job);
}

void Graph::updateFinishes() {
	prevFin = finishes;
	finishes.clear();
	for(size_t i=0; i<events.size(); ++i){
		if (events[i] == nullptr) continue;
		if (events[i]->isFinish || hugeProstoi>0)
			finishes.push_back(i);
	}
}

bool Graph::updateAwailable(int a) {
	Node* pos = events[a];
	vector<Job*> result;
	bool fail = false;
	for(size_t i=0; i<manager.todo.size(); ++i){
		fail = false;
		if (manager.isDone(i)) continue;
		unordered_set<char> requirements = manager[i].requiredJobs();
		for (auto r : requirements) {
			if (!connectionTable->searchJob(pos, r)) {
				for (auto p : finishes) {
					if ((p >= a) || (p==0) || !events[p]->isFinish) continue;
					if (connectionTable->searchJob(events[p], r)) {
						uniteWith(p, events[a]);
						return true;
					}
				}
				fail = true;
				break;
			}
		}
		if (!fail) result.push_back(&manager[i]);
	}
	awailable = move(result);
	return false;
}


void Graph::uniteWith(int i, Node* b) {
	Node* a = events[i];
	events[i] = nullptr;
	connectionTable->replace(a, b);
}

size_t Graph::getNext(size_t i) {
	for (size_t t = i + 1; t < events.size(); ++t)
		if (events[t] && find(finishes.begin(), finishes.end(), t)!=finishes.end())
			return t;
	return -1;
}