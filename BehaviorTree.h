// Behavior Tree Header
// Prototypes for: Sequence, Selector, Important Decorators

// NO actions or conditions in this file

#ifndef _BEHAVIORTREE_H_
#define _BEHAVIORTREE_H_

#include "IBehaviorTree.h"

class Selector: public Task{

	public:
	bool run(Blackboard b);

}

class Sequence: public Task {

	public:
	bool run(Blackboard b);

}

#endif
