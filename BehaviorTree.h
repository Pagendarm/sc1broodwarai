// Behavior Tree Header
// Declarations for: Sequence, Selector, Important Decorators

// NO actions or conditions in this file

#ifndef _BEHAVIORTREE_H_
#define _BEHAVIORTREE_H_

#include "IBehaviorTree.h"

using namespace std;

class Selector: public Task{

	public:
	bool run(Blackboard *b);
	void add_child(Task* child);
};

class Sequence: public Task {

	public:
	bool run(Blackboard *b);
	void add_child(Task* child);

};

class RandomSelector: public Task {
	public:
	bool run(Blackboard *b);
	void add_child(Task* child);
};

#endif
