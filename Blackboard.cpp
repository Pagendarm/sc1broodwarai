//	Blackboard and Blackboard Manager
//	implementation 

#include "IBehaviorTree.h"

bool Blackboard::insert_data (string k, TYPE t, void* d) {
  // Create new DATA
  DATA new_data;
	new_data.type = t;
	new_data.data = d;
	size_t current = table.size();
  // Add to table
	table[k] = &new_data;
  // Check if successful (size increased)
	if (table.size() <= current) return false;
	return true;
}

DATA* Blackboard::recursive_get(string key, Blackboard *parent) {
	if (parent == NULL) return NULL;	
	else if (parent->table.count(key) == 1)
		return parent->table[key];
	else return recursive_get(key,parent->parent);
}

DATA* Blackboard::get(string key) {
	if (table.count(key) == 1) return table[key];
	else return recursive_get(key, parent);
}

void BlackboardManager::set_child (Task *t) {
	children.front() = t;
}

bool BlackboardManager::run (Blackboard *b){
	Blackboard new_blackboard;
	new_blackboard.parent = b;
	return children.front()->run(&new_blackboard);
}
