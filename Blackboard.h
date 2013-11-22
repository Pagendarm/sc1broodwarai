/* OLD FILE NO LONGER USED ALL OF THIS IS NOW IN IBehaviorTree.h*/
//
//#ifndef _BLACKBOARD_H_
//#define _BLACKBOARD_H_
//
//using namespace std;
//
//#include "IBehaviorTree.h"
//#include <map>
//#include <string>
//#include <cstdlib>
//
//enum TYPE {FLOAT, STRING, INT, BOOLEAN};
//struct DATA {TYPE type; void* data;
//	~DATA () {free(data);} // Need to free void*
//};
//
//// Class to contain a hashtable
//// of values, if you want to add more
//// types add to TYPE enum
//class Blackboard {
//	public:
//	//	Returns true if element inserted
//	//	false otherwise 
//	bool insert_data (string k, TYPE t, void* d); 
//	
//	// Returns a DATA struct with the element with key
//	// if an element with key DNE returns NULL
//	DATA* get(string key);
//  
//  Blackboard *parent; // Public so BlackboardManager can
//                      // change it
//  private:
//	map<string,DATA*> table; // Map stores key:value
//                         // pairs of string:DATA*
//  
//  DATA* recursive_get(string key, Blackboard *parent);
//};
//
//
//class BlackboardManager : public Task {
//	public:
//  // Set child should be called before run()
//	void set_child (Task *t);
//	bool run (Blackboard *b);
//};
//
//#endif
