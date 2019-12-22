#include "ConnectionTable.h"
#include "SimultaneousNodes.h"
#include <bitset>

using std::bitset;

ConnectionTable* ConnectionTable::instance = nullptr;

ConnectionTable::ConnectionTable(){}
ConnectionTable::~ConnectionTable(){}

void ConnectionTable::insert(Node* l, Node* r, Job* j) {
	for (auto p : contents) {
		if (Job::conflicting(p.first, j)) {
			if (r->isSimple())
				* (r) = SimultaneousNodes::evolve(r);
			Node* fake = new Node;
			fake->nonFake = r;
			r->getStates()->push_back(fake);
			contents.insert({ j,{l,fake} });
			return;
		}
	}
	contents.insert({ j,{l,r} });
}

ConnectionTable* ConnectionTable::getConnectionTable() {
	if (!instance)
		instance = new ConnectionTable;
	return instance;
}


vector<char> ConnectionTable::getDoneJobs(Node* arg) {
	unordered_set<char> result;
	unordered_set<Node*> children;
	for (auto r : contents) 
		if (r.second.second == arg) {
			result.insert(*r.first);
			children.insert(r.second.first);
	}
	for (auto p : children) {
		vector<char> item = getDoneJobs(p);
		for (size_t i = 0; i < item.size(); ++i) {
			result.insert(item[i]);
		}
	}
	vector<char> res;
	for (auto k : result) {
		res.push_back(k);
	}
	return res;
}

void ConnectionTable::replace(Node* before, Node* after) {
	unordered_map<Job*, Node*> temp;
	for (auto r : contents) {
		if (r.second.second == before) {
			temp.insert({ r.first, r.second.first });
		}
	}
	for(auto p : temp)
		contents.erase(p.first);
	for (auto k : temp)
		insert(k.second, after, k.first);
}
