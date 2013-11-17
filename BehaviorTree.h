// Behavior Tree Header
// Prototypes for: Sequence, Selector, Important Decorators

// NO actions or conditions in this file

#include "IBehaviorTree.h"

class Selector: public Task{

	public:
	bool run();

}

class Sequence: public Task {

	public:
	bool run();

}
