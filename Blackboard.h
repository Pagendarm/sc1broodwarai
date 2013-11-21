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
struct DATA {TYPE type; void* data} 

class Blackboard {

	Blackboard parent;
	map<string,void*> map;

	public:
	void insert_data (string k, TYPE t, void* d); 

	DATA get(string key);

}


class BlackboardManager : public Decorator {
	public:
	void set_child (Task t);
	bool run (Blackboard b);
}

#endif
