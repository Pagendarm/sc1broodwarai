// Blackboard and Behavior Tree
// Testing
//

#include "BehaviorTree.h"
#include <iostream>
#include <stdio.h>
#include <assert.h>

int N = 0;
int pass = 0;

class DoorOpen : public Task
{
public:
   bool run (Blackboard *b) {
		 vector<Task*>::iterator childIter;
		 DATA *d = b->get ("door_status");
		 
		 bool tf = *(bool*) d->data;
		 ::N++;
		 if (tf) return true;
		 return false;
	}
};

class Move : public Task
{
public:
   bool run (Blackboard *b) {
	 	::N++;
		 return true;
	}
};

class OpenDoor : public Task
{
public:
   bool run (Blackboard *b) {
		 ::N++;
		 return true;
	}
};



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
	if (inserted) {
		cout << "Data Inserted" << endl;
		::pass++;
	}
  else cout << "FAILURE: Data Insertion failed" << endl;
  
	// Check data is as expected and type
	// enum functions well
	DATA *d = testboard.get (test_string);
  if (d->type == INT) {
  	cout << "Type enum works" << endl;
		::pass++;
   	int num = * ((int*)d->data);
		cout << "data == test_num:" ;
		bool test_data = (num == test_num);
		if (test_data) {
		cout << "TRUE" << endl;
		::pass++;
		}
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
		if (test_data) {
		cout << "TRUE" << endl;
		::pass++;
		}
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
   bool open = true;
   assert (treeBoard.insert_data ("door_status", BOOLEAN, &open));

   // Build BTree using the Task nodes
   root.add_child (&sel1);
   sel1.add_child (&isOpen);
   sel1.add_child (&seq2);
   seq2.add_child (&moveToDoor);
   seq2.add_child (&openDoor);
   
   // Run BTree with Blackboard
	 // Using N to determine if BT visits correct number
   // of nodes depending on Blackboard
   cout<< "If open== true, N = 1,  else if open == false,  N=3"<<endl;
   root.run (&treeBoard);

	 ::pass++;
	 if (open==true && ::N == 1) cout << "success!"<<endl;
	 else if (open == false && ::N ==3) cout<< "success!"<<endl;
	 else {
		 cout << "FAILURE with BT using Blackboard"<<endl;
		 ::pass--;
	 }
 
   // Use pass variable to determine if all tests
	 // were successful
		cout << endl;
		if (::pass == 5) cout << "ALL TESTS PASSED!"<<endl;
		else cout << "__TEST FAILED: CHECK OUTPUT__" <<endl;

	 return 0;
}
