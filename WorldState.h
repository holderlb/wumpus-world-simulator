// WorldState.h

#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include <vector>
#include "Location.h"
#include "Orientation.h"

class WorldState
{
public:
	int worldSize;
	Location agentLocation;
	Orientation agentOrientation;
	Location wumpusLocation;
	Location goldLocation;
	vector<Location> pitLocations;
	bool agentAlive;
	bool agentHasArrow;
	bool agentHasGold;
	bool agentInCave;
	bool wumpusAlive;
};

#endif // WORLDSTATE_H
