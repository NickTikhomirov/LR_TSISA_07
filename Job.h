#pragma once
#include <unordered_map>
#include <unordered_set>

using std::unordered_map;
using std::size_t;
using std::unordered_set;

class Node;

class Job{
public:
	static unordered_map<char, size_t> contents;
	static unordered_map<char, unordered_set<char>> inits;
	
	unordered_set<char> requiredJobs();
	bool isFictive();
	bool isFreeToStart();
	char id = 0;

	size_t getTime();
	Job(char r);
	~Job();
	operator char();
};

