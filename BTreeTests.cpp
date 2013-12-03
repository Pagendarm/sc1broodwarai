// Blackboard and Behavior Tree
// Testing
//

#include "BehaviorTree.h"
#include <iostream>
#include <stdio.h>
#include <assert.h>

/*
class DoorOpen : public Task
{
public:
   bool run (Blackboard *b);
};

class Move : public Task
{
public:
   bool run (Blackboard *b);
};

class OpenDoor : public Task
{
public:
   bool run (Blackboard *b);
};
*/

int main () {
	cout << "This test should only show TRUE,\n \
should not fail on an assertion,\n \
and should never print FAILURE.\n\n";

	// Setup parent
	Blackboard testboard_parent;
	float parent_num = 15.0;
	testboard_parent.parent = NULL;
	string parent_string = "parent";
	assert(	testboard_parent.insert_data(parent_string,FLOAT,&parent_num));
	
	// Setup child
	Blackboard testboard;
	testboard.parent = &testboard_parent;
	int test_num = 100;
	string test_string = "test_string";

	// Insert the pointer and test it was inserted
	cout << "Test child:" << endl;
	
	bool inserted = testboard.insert_data (test_string, INT, &test_num);   
	if (inserted) cout << "Data Inserted" << endl;
  else cout << "FAILURE: Data Insertion failed" << endl;
  
	// Check data is as expected and type
	// enum functions well
	DATA *d = testboard.get (test_string);
  if (d->type == INT) {
  	cout << "Type enum works" << endl;
   	int num = * ((int*)d->data);
		cout << "data == test_num:" ;
		bool test_data = (num == test_num);
		if (test_data)
		cout << "TRUE" << endl;
  	else cout <<	"FALSE" << endl; 
	
	}
	else cout<<"FAILURE: Type was not INT"<< endl;

	// Test parent	
	cout << "\nTest parent:" << endl;
	d = testboard.get ("parent");
  if (d->type == FLOAT) {
  	cout << "Type enum works" << endl;
   	float num = * ((float*)d->data);
		cout << "data == test_num:" ;
		bool test_data = (num == parent_num);
		if (test_data)
		cout << "TRUE" << endl;
  	else cout <<	"FALSE" << endl; 
	
	}
	else cout<<"FAILURE: Type was not FLOAT"<< endl;
/*
   Selector sel1;
   Sequence seq1;
   Sequence seq2;
   DoorOpen doorOpen;
   Move move;
   OpenDoor openDoor;

   seq1.add_child (&sel1);
   sel1.add_child (doorOpen);
   sel1.add_child (&seq2);
   seq2.add_child (move);
   seq2.add_child (openDoor);
 */  

   return 0;

}
