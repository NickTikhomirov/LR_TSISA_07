#include <iostream>
#include "Graph.h"

using std::cout;
using std::endl;
using std::size_t;

int main() {
	Graph graph;
	unordered_map<Node*, size_t> translator;
	for (size_t t = 0; t < graph.events.size(); ++t) {
		translator.insert({graph.events[t], t});
	}
	for (auto k : graph.connectionTable->contents) {
		cout << translator[k.second.first] << "====>" << translator[k.second.second] << " :" << k.first->id << endl;
	}

}