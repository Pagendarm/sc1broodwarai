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

	Blackboard testboard;
	testboard.parent = NULL;

	// Initalize a value we want to test for
	int test_num = 100;
  int* int_ptr = new int;
	*int_ptr = test_num; // Dereference pointer and set value to test
	
	// Create a string to refer to the number
	string test_string = "test_string";

	// Insert the pointer and test it was inserted
	bool inserted = testboard.insert_data (test_string, INT, int_ptr);   
	if (inserted) cout << "Data Inserted\n";
  else cout << "Data Insertion FAILED\n";
  
	// Check data is as expected and type
	// enum functions well
	DATA *d = testboard.get (test_string);
  if (d->type == INT) {
  	cout << "Type enum works" << endl;
   	int num = * ((int*)d->data);
    cout << "Number is: " <<num;	
		cout << "data == test_num:" ;
		bool test_data = (num == test_num);
		cout << test_data << endl;
   }
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
