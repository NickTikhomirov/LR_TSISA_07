#pragma once
#include <utility>
#include <vector>
#include "Job.h";

using std::size_t;
using std::vector;

class Node {
public:
	Node* prev;
	Node* next;
	int early = -1;
	int late = -1;
	size_t getReserve();
	Node();
	~Node();

	void operator++(int);
	void operator++();
	Node& operator~();
};

