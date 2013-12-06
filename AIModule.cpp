#include <BWAPI.h>
#include <math.h>
#include <vector>

#include "ExampleAIModule.h"
#include "BehaviorTree.h"
#include "BWTasks.h"

using namespace BWAPI;
using namespace Filter;
using namespace std;

Blackboard parent;
vector<Blackboard> blackboard;
Unitset myUnits;

int pixelWidth;
int pixelHeight;
Position avgPos;

bool finishedSpread = false;




void ExampleAIModule::onStart()
{
  // Hello World!
  Broodwar->sendText("My life for Aiur!");

  // Print the map name.
  // BWAPI returns std::string when retrieving a string, don't forget to add .c_str() when printing!
  Broodwar << "The map is " << Broodwar->mapName() << "!" << std::endl;

  // Enable the UserInput flag, which allows us to control the bot and type messages.
  Broodwar->enableFlag(Flag::UserInput);

  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
  Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);
  
  // Retrieve you and your enemy's races. enemy() will just return the first enemy.
  // If you wish to deal with multiple enemies then you must use enemies().
  if ( Broodwar->enemy() ) // First make sure there is an enemy
    Broodwar << "The matchup is " << Broodwar->self()->getRace() << " vs " << Broodwar->enemy()->getRace() << std::endl;


  myUnits = Broodwar->self()->getUnits();
  Unitset enemyUnits = Broodwar->enemy()->getUnits();
  avgPos = myUnits.getPosition();

  // Setting up parent blackboard
  parent.insert_data(ENEMYSET, UNITSET, enemyUnits);
  parent.insert_data(AVGP, INT, &avgPos);
  parent.parent = NULL;

  // Setting up vector<Blackboard>
  for ( Unitset::iterator u = myUnits.begin(); u != myUnits.end(); ++u )
  {
	  Blackboard b;

	  // link global blackboard as parent
	  b.parent = &parent;

	  // create action and condition tasks
	  TaskMoveOnLine mol;
	  TaskAttackMoveAction ama;
	  TaskFallBackAction fba;
	  TaskLowSheildsCondition lsc;
	  TaskOnLineConidition olc;
	  TaskTakingDamageCondition tdc;

	  // create sub trees
	  Sequence left;
	  left.add_child(&olc);
	  left.add_child(&mol);

	  Sequence center;
	  center.add_child(&lsc);
	  center.add_child(&tdc);
	  center.add_child(&fba);

	  // connect to root
	  Selector root;
	  root.add_child(&left);
	  root.add_child(&center);
	  root.add_child(&ama);

	  // add unit to blackboard
	  b.insert_data(FUNIT, UNIT, *u);

	  // add tree to blackboard
	  b.insert_data(BTREE, TREE, &root);

	  // add b to blackboard vector
	  blackboard.push_back(b);
  }



  pixelHeight = Broodwar->mapHeight() * 32;
  pixelWidth = Broodwar->mapWidth() * 32;
  avgPos = myUnits.getPosition();

  Position p1(avgPos.x, avgPos.y);
  p1.y -= CONCAVE_LENGTH;
  Position p2(avgPos.x, avgPos.y);
  p2.y += CONCAVE_LENGTH;

  Broodwar->sendText("avgPos.x: %d", avgPos.x);
  Broodwar->sendText("avgPos.y: %d", avgPos.y);
  Broodwar->sendText("desiredLine: (%d, %d) (%d, %d)", p1.x, p1.y, p2.x, p2.y);
  Broodwar->sendText("height: %d", pixelHeight);
  Broodwar->sendText("width: %d", pixelWidth);

}

void ExampleAIModule::onEnd(bool isWinner)
{
  // Called when the game ends
  if ( isWinner )
  {
    // Log your win here!
  }
}

void ExampleAIModule::onFrame()
{
  // Called once every game frame
  drawStats();

  // Display the game frame rate as text in the upper left area of the screen
  Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
  Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );

  // Return if the game is a replay or is paused
  if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
    return;

  // Prevent spamming by only running our onFrame once every number of latency frames.
  // Latency frames are the number of frames before commands are processed.
  if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
    return;

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // loop through all the black board to decide what
  // each unit should do
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  vector<Blackboard>::iterator b;
  for (b = blackboard.begin(); b != blackboard.end(); b++)
  {
	  DATA *data = b->get(BTREE);
	  Task* behaviorTree = (Task*) data->data;
	  behaviorTree->run(&(*b));
  }

}

void ExampleAIModule::onSendText(std::string text)
{

  // Send the text to the game if it is not being processed.
  Broodwar->sendText("%s", text.c_str());


  // Make sure to use %s and pass the text as a parameter,
  // otherwise you may run into problems when you use the %(percent) character!

}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
  // Parse the received text
  Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player)
{
  // Interact verbally with the other players in the game by
  // announcing that the other player has left.
  Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target)
{
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitEvade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitShow(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitHide(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitCreate(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit)
{
	int ecount = Broodwar->enemy()->allUnitCount(UnitTypes::Protoss_Dragoon);
	if (ecount <= 0)
	{
		int count = Broodwar->self()->allUnitCount(UnitTypes::Protoss_Dragoon);
		if (count > ecount)
		{
			Broodwar->sendText("nooblord");
		}
	}
}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onSaveGame(std::string gameName)
{
  Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{
}

void ExampleAIModule::drawStats()
{
  int line = 1;
  Broodwar->drawTextScreen(5, 0, "Began with 12 units");
  for ( UnitType::set::iterator i = UnitTypes::allUnitTypes().begin(); i != UnitTypes::allUnitTypes().end(); ++i )
  {
    int count = Broodwar->self()->allUnitCount(*i);
	int ecount = Broodwar->enemy()->allUnitCount(*i);
    if ( count )
    {
      Broodwar->drawTextScreen(5, 16*line, "- %d friendly %s%c", count, (*i).c_str(), count == 1 ? ' ' : 's');
      ++line;
    }
	if ( ecount )
	{
	  Broodwar->drawTextScreen(5, 16*line, "- %d enemy %s%c", ecount, (*i).c_str(), count == 1 ? ' ' : 's');
	  ++line;
	}
  }
}