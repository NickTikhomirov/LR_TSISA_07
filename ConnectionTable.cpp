#include "ConnectionTable.h"
#include <bitset>

using std::bitset;

ConnectionTable* ConnectionTable::instance = nullptr;

ConnectionTable::Triple::Triple(Node* l, Node* r, Job* j) {
	left = l;
	right = r;
	job = j;
}

ConnectionTable::ConnectionTable(){

}


ConnectionTable::~ConnectionTable()
{
}

Job* ConnectionTable::insert(Node* l, Node* r, Job* j) {
	for (size_t i = 0; i < contents.size(); ++i) {
		if (contents[i].left == l && contents[i].right == r)
			return contents[i].job;
	}
	contents.push_back({ l,r,j });
	return nullptr;
}

ConnectionTable* ConnectionTable::getConnectionTable() {
	if (!instance)
		instance = new ConnectionTable;
	return instance;
}

void ConnectionTable::evaluateEarly() {
	bool a = true;
	unordered_map<Node*, int> times;
	bitset<21> bits;
	while(a){
		a = false;
		for (size_t i = 0; i < contents.size(); ++i) {
			if (bits[i]) continue;
			if (contents[i].left->early == -1) {
				a = true;
				continue;
			}
			int length = contents[i].job->getTime() + contents[i].left->early;
			auto temp = times.find(contents[i].right);
			if(temp != times.end()) {
				if (temp->second < length)
					temp->second = length;
			} else times.insert({contents[i].right, length});
			bits[i] = true;
		}
	}
}

vector<char> ConnectionTable::getDoneJobs(Node* arg) {
	unordered_set<char> result;
	unordered_set<Node*> children;
	for (auto r : contents) 
		if (r.right == arg) {
			result.insert(*r.job);
			children.insert(r.left);
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
