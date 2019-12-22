#include "ConnectionTable.h"

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
	{'k', 5}
};


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
	{'k', {'h', 'i'}}
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
bool Job::isFreeToStart() {
	return inits.find(id)->second.size() == 0;
}

Job::operator char() {
	return id;
}

bool Job::conflicting(Job* a, Job* b) {
	ConnectionTable* c = ConnectionTable::getConnectionTable();
	return (c->contents[a]) == (c->contents[b]);
}
