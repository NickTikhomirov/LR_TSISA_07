#include "ConnectionTable.h"

#include <iostream>
using namespace std;


unordered_map<char, size_t> Job::contents{
	{'a', 3},
	{'b', 5},
	{'c', 2},
	{'d', 4},
	{'e', 3},
	{'f', 1},
	{'g', 4},
	{'h', 3},
	{'i', 3},
	{'j', 2},
	{'k', 5},
	{'0', 1}
};

/*
unordered_map<char, unordered_set<char>> Job::inits{
	{'a', {}},
	{'b', {}},
	{'c', {}},
	{'d', {'a'}},
	{'e', {'b'}},
	{'f', {'b'}},
	{'g', {'d'}},
	{'h', {'e'}},
	{'i', {'f', 'c'}},
	{'j', {'g'}},
	{'k', {'h', 'i'}},
	{'0', {'a', 'b', 'c', 'd', 'e', 'g', 'h', 'i', 'j', 'k'}}
};
*/


unordered_map<char, unordered_set<char>> Job::inits{
	{'a', {}},
	{'b', {}},
	{'c', {}},
	{'d', {'c'}},
	{'e', {'c'}},
	{'f', {'a'}},
	{'g', {'a'}},
	{'h', {'d', 'g'}},
	{'i', {'h', 'e'}},
	{'j', {'b', 'f', 'i'}},
	{'k', {'h', 'e'}},
	{'0', {'j', 'k'}}
};



Job::Job(char r){
	id = r;
}


Job::~Job(){
}


size_t Job::getTime(){
	return contents.find(id)->second;
}

unordered_set<char> Job::requiredJobs() {
	return inits.find(id)->second;
}

bool Job::isFictive() {
	return contents.find(id)->second == 0;
}
bool Job::isRequired() {
	for (auto p : inits) {
		if (p.second.find(id) != p.second.end())
			return true;
	}
	return false;
}

Job::operator char() {
	return id;
}

bool Job::conflicting(Job* a, Job* b) {
	ConnectionTable* c = ConnectionTable::getConnectionTable();
	return (c->contents.find(a)) == (c->contents.find(b));
}
