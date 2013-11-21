//	Behavior Tree Interface
//	Define Abstract Classes (interfaces)
//	for Task, and Decorator
//	implementations of Tasks and Decorators
//	must implement the run() function

#ifndef _IBEHAVIORTREE_H_
#define _IBEHAVIORTREE_H_

#include <vector>
#include "Blackboard.h"

// Abstract base class: Task
class Task {

	vector<Task> children;

	public:
	virtual bool run (Blackboard b) = 0; 	// Pure Virtual Function

}

// Abstract class: Decorator
//		 use child instead of children
class Decorator: public Task {
	Task child; // Child that decorator affects

	public:
	virtual bool run(Blackboard b) = 0;

}

#endif
