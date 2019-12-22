#pragma once
#include <vector>
#include "Job.h"

using std::vector;

class JobManager
{
public:
	vector<Job> todo;
	unordered_set<char> done;

	void do_(char);
	bool isDone(char);
	JobManager();
	~JobManager();
	Job& operator[](size_t);
};

