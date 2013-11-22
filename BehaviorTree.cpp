// Behavior Tree
// Definitions for: Sequence, Selector, Important Decorators

// NO actions or conditions in this file

#include "BehaviorTree.h"

bool Selector::run(Blackboard b) {
    std::vector<Task>::iterator childIter; //create vector iterator for children
    
    //iterate through each, returning true if any child runs successfully
    for (childIter = children.begin(); childIter != children.end(); childIter++) {
        if (childIter.run(b)) return true;
    }
	return false;
}	

bool Sequence::run(Blackboard b) {
	std::vector<Task>::iterator childIter; //create vector iterator for children
    
    //iterate through each, returning true only if all children run successfully
    for (childIter = children.begin(); childIter != children.end(); childIter++) {
        if (!childIter.run(b)) return false;
    }
	return true;
}

//Non-deterministic
bool RandomSelector::run(Blackboard b) {
    std::vector<Task>::iterator childIter; //create vector iterator for children
    
    //shuffle children vector
    std::random_shuffle(children.begin(), children.end())
    
    //iterate through each, returning true if any child runs successfully
    for (childIter = children.begin(); childIter != children.end(); childIter++) {
        if (childIter.run(b)) return true;
    }
	return false;
    
}