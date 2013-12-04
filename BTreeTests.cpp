// Blackboard and Behavior Tree
// Testing
//

#include "BehaviorTree.h"
#include <iostream>
#include <stdio.h>
#include <assert.h>


class DoorOpen : public Task
{
public:
   bool run (Blackboard *b);
};

bool DoorOpen::run (Blackboard *b)
{
   vector<Task*>::iterator childIter;
   DATA *d = b->get ("door_status");
   
   bool tf = *(bool*) d->data;
   
   printf ("DoorOpen? Task\n");
   cout << tf;
   printf ("\n");

   if (tf) return true;
   return false;
}

class Move : public Task
{
public:
   bool run (Blackboard *b);
};

bool Move::run (Blackboard *b)
{
   vector<Task*>::iterator childIter;

   printf ("Move Task\n");
   return true;
}

class OpenDoor : public Task
{
public:
   bool run (Blackboard *b);
};

bool OpenDoor::run (Blackboard *b)
{
   vector<Task*>::iterator childIter;

   printf ("OpenDoor Task\n");
   return true;
}



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

   printf ("\nBuild Tree and Test\n");
   // Declare Task nodes to be used to build BTree
   Selector sel1;
   Sequence root;
   Sequence seq2;
   DoorOpen isOpen;
   Move moveToDoor;
   OpenDoor openDoor;

   // Insert some data into the Blackboard
   // that the BTree will use
   Blackboard treeBoard;
   treeBoard.parent = NULL;
   bool open = false;
   cout << open;
   printf("\n");
   assert (treeBoard.insert_data ("door_status", BOOLEAN, &open));

   // Build BTree using the Task nodes
   root.add_child (&sel1);
   sel1.add_child (&isOpen);
   sel1.add_child (&seq2);
   seq2.add_child (&moveToDoor);
   seq2.add_child (&openDoor);
   
   // Run BTree with Blackboard
   if (root.run (&treeBoard)) printf ("RunTrue\n");
   else printf ("RunFalse\n");

   return 0;

}
