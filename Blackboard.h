//	Blackboard and Blackboard Manager
// 
//	Can use FLOAT, STRING, 
//	INT, BOOL  

#ifndef _BLACKBOARD_H_
#define _BLACKBOARD_H_

#include "IBehaviorTree.h"
#include <map>
#include <string>

enum TYPE {FLOAT, STRING, INT, BOOL};
struct DATA {TYPE type; void* data;
	~DATA () {free data;} // Need to free void*
} 

class Blackboard {

	Blackboard parent;
	map<string,DATA> map;

	public:
	//	Returns true if element inserted
	//	false otherwise 
	bool insert_data (string k, TYPE t, void* d); 
	
	// Returns a DATA struct with the element with key
	// if an element with key DNE returns null
	DATA get(string key);

}


class BlackboardManager : public Decorator {
	public:
	void set_child (Task t);
	bool run (Blackboard b);
}

#endif
