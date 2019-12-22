#include "Node.h"


vector<Node*> Node::getStates() {
	vector<Node*> result;
	result.push_back(this);
	return result;
}

bool Node::isSimple() {
	return true;
}