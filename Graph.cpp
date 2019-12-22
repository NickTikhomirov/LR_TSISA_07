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
		for (int i = 0; i < finishes.size(); i++) cout << finishes[i];
		cout << endl;
		for (size_t i = 0; i < finishes.size(); ++i) {
			updateAwailable(events[finishes[i]]);
			if (awailable.size() == 0) {
				size_t nex = getNext(finishes[i]);
				if (nex == size_t(-1)) continue;
				uniteWith(i, events[nex]);
			}
			for (size_t j = 0; j < awailable.size(); ++j) {
				doJob(awailable[j], finishes[i]);
			}
		}
	}

}


Graph::~Graph(){}



void Graph::doJob(Job* job, size_t i) {
	manager.do_(*job);
	events[i]->isFinish = false;
	size_t fin = i + Job::contents[*job];
	cout << i << "_" << fin << "/" << *job << endl;
	cout << int(events[2] == nullptr)<<endl;
	Node* f = events[fin];
	if (!f) events[fin] = new Node;
	connectionTable->insert(events[i], events[fin], job);
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
		fail = false;
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
	connectionTable->replace(a, b);
}

size_t Graph::getNext(size_t i) {
	for (size_t t = i + 1; t < events.size(); ++t)
		if (events[t] && find(finishes.begin(), finishes.end(), t)!=finishes.end())
			return t;
	return -1;
}