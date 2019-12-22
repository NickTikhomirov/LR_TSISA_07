#include "JobManager.h"

#include <iostream>
using namespace std;

JobManager::JobManager()
{
	for (auto j : Job::contents) {
		todo.push_back({ j.first });
	}
}


JobManager::~JobManager()
{
}

void JobManager::do_(char r){
	done.insert(r);
}

bool JobManager::isDone(char r) {
	return done.find(todo[r]) != done.end();
}


Job& JobManager::operator[](size_t i) {
	return todo[i];
}

JobManager::operator bool() {
	return done.size() != todo.size();
}