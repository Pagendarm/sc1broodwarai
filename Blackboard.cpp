//	Blackboard and Blackboard Manager
//	implementation 

#include "Blackboard.h"

bool Blackboard::insert_data (string k, TYPE t, void* d) {
	DATA new_data = new DATA();
	new_data->type = t;
	new_data->data = d;
	size_type current = map.size();
	map[k] = new_data;
	if (map.size() <= current) return false;
	return true;
}

DATA recursive_get(string key, Blackboard parent) {
	if (parent == null) return null;	
	else if (parent.map.count(key) == 1) 
		return parent.map[key];
	else return recursive_get(key,parent.parent);
}

DATA Blackboard::get(string key) {
	if (map.count(key) == 1) return map[key];
	else return recursive_get(key, parent);
}

void BlackboardManager::set_child (Task t) {
	child = t;
}

bool BlackboardManager::run (Blackboard b){
	Blackboard new_blackboard;
	new_blackboard.parent = b;
	return child.run(new_blackboard);
}
