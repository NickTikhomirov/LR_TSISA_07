#include "Node.h"


Node::Node() {
	nonFake = this;
}

vector<Node*>* Node::getStates() {
	return nullptr;
}

bool Node::isSimple() {
	return true;
}