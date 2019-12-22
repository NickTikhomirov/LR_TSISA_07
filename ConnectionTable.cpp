#include "ConnectionTable.h"
#include <bitset>

using std::bitset;

ConnectionTable* ConnectionTable::instance = nullptr;

ConnectionTable::ConnectionTable(){
}


ConnectionTable::~ConnectionTable()
{
}

Job* ConnectionTable::insert(Node* l, Node* r, Job* j) {
	for (auto i : contents) {
		if (i.second.first == l && i.second.second == r)
			return i.first;
	}
	contents.insert({ j, { l,r} });
	l->isFinish = false;
	return nullptr;
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
