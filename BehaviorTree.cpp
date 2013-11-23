// Behavior Tree
// Definitions for: Sequence, Selector, Important Decorators

// NO actions or conditions in this file
#include "BehaviorTree.h"
#include <algorithm> // For random shuffle

bool Selector::run(Blackboard *b) {
    vector<Task*>::iterator childIter; //create vector iterator for children
    
    //iterate through each, returning true if any child runs successfully
    for (childIter = children.begin(); childIter != children.end(); childIter++) {
        if (!((*childIter)->run(b))) return true;
    }
	return false;
}	

void Selector::add_child (Task* child) {
	children.push_back(child);
}

bool Sequence::run(Blackboard *b) {
	 vector<Task*>::iterator childIter; //create vector iterator for children
    
    //iterate through each, returning true only if all children run successfully
    for (childIter = children.begin(); childIter != children.end(); childIter++) {
        if (!((*childIter)->run(b))) return false;
    }
	return true;
}

void Sequence::add_child (Task* child) {
	children.push_back(child);
}

//Non-deterministic
bool RandomSelector::run(Blackboard *b) {
    vector<Task*>::iterator childIter; //create vector iterator for children
    
    //shuffle children vector
    random_shuffle(children.begin(), children.end());
  
    //iterate through each, returning true if any child runs successfully
    for (childIter = children.begin(); childIter != children.end(); childIter++) {
        if ((*childIter)->run(b)) return true;
    }
	return false;
    
}

void RandomSelector::add_child (Task* child) {
	children.push_back(child);
}
