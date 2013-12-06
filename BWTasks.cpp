#include "BWTasks.h"

// TaskMoveOnLine
bool TaskMoveOnLine::run(Blackboard* b)
{
	DATA* data = b->parent->get(AVGP);
	BWAPI::Position* avgPos = (BWAPI::Position*) data->data;

	BWAPI::Position p1(avgPos->x, avgPos->y);
	p1.y -= CONCAVE_LENGTH;
	BWAPI::Position p2(avgPos->x, avgPos->y);
	p2.y += CONCAVE_LENGTH;

	int distance = p1.getDistance(p2);
	int inc = distance / 12;

	int dy = 0;

	data = b->get(FUNIT);
	BWAPI::Unit u = (BWAPI::Unit) data->data;

	u->move(BWAPI::Position(avgPos->x + FRONT, p1.y + dy));
	dy += inc;
	if (dy > p2.y)
	{
		dy = 0;
	}

	return true;
}

// TaskMoveOnLineCondition
bool TaskOnLineConidition::run(Blackboard* b)
{
	DATA* data = b->get(FUNIT);
	BWAPI::Unit u = (BWAPI::Unit) data->data;

	if (u->isMoving())
	{
		return false;
	}
	else
	{
		return true;
	}
}

// TaskLowSheildsCondition
bool TaskLowSheildsCondition::run(Blackboard* b)
{
	DATA* data = b->get(FUNIT);
	BWAPI::Unit u = (BWAPI::Unit) data->data;

	if (u->getHitPoints() <= LOW_HEALTH)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// TaskTakingDamageCondition
bool TaskTakingDamageCondition::run(Blackboard* b)
{
	DATA* data = b->get(FUNIT);
	BWAPI::Unit u = (BWAPI::Unit) data->data;

	if (u->isUnderAttack())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// TaskFallBackAction
bool TaskFallBackAction::run(Blackboard* b)
{
	DATA* data = b->get(FUNIT);
	BWAPI::Unit u = (BWAPI::Unit) data->data;

	int x = u->getPosition().x - u->getType().dimensionRight() - u->getType().dimensionLeft();
	u->move(BWAPI::Position(x, u->getPosition().y));

	return true;
}

// TaskAttackMoveAction
bool TaskAttackMoveAction::run(Blackboard* b)
{
	DATA* data = b->get(FUNIT);
	BWAPI::Unit u = (BWAPI::Unit) data->data;
  
	if (u->isIdle())
	{
		Blackboard* parent = b->parent;
		DATA* edata = parent->get(ENEMYSET);
		BWAPI::Unitset* enemyUnits = (BWAPI::Unitset*) edata->data;
		BWAPI::Position avgE = enemyUnits->getPosition();

		u->attack(avgE);
	}

	return true;
}