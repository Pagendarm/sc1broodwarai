#pragma once

#include <BWAPI.h>
#include <math.h>
#include <string>
#include "IBehaviorTree.h"

using namespace std;

const string ENEMYSET = "enemy";
const string FUNIT = "unit";
const string BTREE = "tree";
const string AVGP = "pos";

const int MAX_SPEED = 5;
const int FRONT = 150;
const int LOW_SHEILDS = 20;
const int LOW_HEALTH = 30;
const int CONCAVE_LENGTH = 160;

class TaskMoveOnLine :
	public Task
{
public:
	virtual bool run(Blackboard*);
};

class TaskOnLineConidition : 
	public Task
{
public:
	virtual bool run(Blackboard*);
};

class TaskLowSheildsCondition : 
	public Task
{
public:
	virtual bool run(Blackboard*);
};

class TaskTakingDamageCondition : 
	public Task
{
public:
	virtual bool run(Blackboard*);
};

class TaskFallBackAction : 
	public Task
{
public:
	virtual bool run(Blackboard*);
};

class TaskAttackMoveAction : 
	public Task
{
public:
	virtual bool run(Blackboard*);
};