// WumpusWorld.cc

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "WumpusWorld.h"

#define PIT_PROBABILITY 0.2

using namespace std;

WumpusWorld::WumpusWorld (int size)
{
	int x;
	int y;

	currentState.worldSize = size;
	// Choose wumpus location (anywhere except [1,1])
	x = 1; y=1;
	while ((x == 1) && (y == 1))
	{
		x = (rand() % size) + 1;
		y = (rand() % size) + 1;
	}
	currentState.wumpusLocation = Location (x, y);

	// Choose gold location (anywhere except [1,1])
	x = 1; y=1;
	while ((x == 1) && (y == 1))
	{
		x = (rand() % size) + 1;
		y = (rand() % size) + 1;
	}
	currentState.goldLocation = Location (x, y);

	// Choose pit locations (anywhere except [1,1])
	for (x = 1; x <= size; x++)
	{
		for (y = 1; y <= size; y++)
		{
			if ((x != 1) || (y != 1))
			{
				if ((rand() % 1000) < (PIT_PROBABILITY * 1000))
				{
					currentState.pitLocations.push_back (Location (x, y));
				}
			}
		}
	}
}

WumpusWorld::WumpusWorld (char* worldFile)
{
	ifstream worldFileStream;
	string tokenStr;
	int intArg1;
	int intArg2;

	worldFileStream.open (worldFile);
	if (worldFileStream.is_open())
	{
		worldFileStream >> tokenStr;
		if (tokenStr != "size")
		{
			cout << "Incorrect token in world file: " << tokenStr << endl;
			exit(1);
		} else {
			worldFileStream >> intArg1;
			if (intArg1 < 2)
			{
				intArg1 = 2;
			}
			currentState.worldSize = intArg1;
		}
		worldFileStream >> tokenStr;
		if (tokenStr != "wumpus")
		{
			cout << "Incorrect token in world file: " << tokenStr << endl;
			exit(1);
		} else {
			worldFileStream >> intArg1;
			worldFileStream >> intArg2;
			if ((intArg1 < 1) || (intArg1 > currentState.worldSize) ||
				(intArg2 < 1) || (intArg2 > currentState.worldSize) ||
				((intArg1 == 1) && (intArg2 == 1)))
			{
				cout << "Bad wumpus location in world file" << endl;
				exit (1);
			}
			currentState.wumpusLocation = Location (intArg1, intArg2);
		}
		worldFileStream >> tokenStr;
		if (tokenStr != "gold")
		{
			cout << "Incorrect token in world file: " << tokenStr << endl;
			exit(1);
		} else {
			worldFileStream >> intArg1;
			worldFileStream >> intArg2;
			if ((intArg1 < 1) || (intArg1 > currentState.worldSize) ||
				(intArg2 < 1) || (intArg2 > currentState.worldSize) ||
				((intArg1 == 1) && (intArg2 == 1)))
			{
				cout << "Bad gold location in world file" << endl;
				exit (1);
			}
			currentState.goldLocation = Location (intArg1, intArg2);
		}
		// Read pit locations
		while (worldFileStream >> tokenStr)
		{
			if (tokenStr != "pit")
			{
				cout << "Incorrect token in world file: " << tokenStr << endl;
				exit(1);
			} else {
				worldFileStream >> intArg1;
				worldFileStream >> intArg2;
				if ((intArg1 < 1) || (intArg1 > currentState.worldSize) ||
					(intArg2 < 1) || (intArg2 > currentState.worldSize) ||
					((intArg1 == 1) && (intArg2 == 1)))
				{
					cout << "Bad pit location in world file" << endl;
					exit (1);
				}
				currentState.pitLocations.push_back (Location (intArg1, intArg2));
			}
		}
	} else {
		cout << "Unable to open world file " << worldFile << endl;
		exit (1);
	}
	worldFileStream.close();
	cout << "Read world file" << endl;
}

void WumpusWorld::Initialize ()
{
	numActions = 0;
	currentState.agentLocation = Location(1,1);
	currentState.agentOrientation = RIGHT;
	currentState.agentAlive = true;
	currentState.agentHasArrow = true;
	currentState.agentHasGold = false;
	currentState.agentInCave = true;
	currentState.wumpusAlive = true;

	// Update current percept
	currentPercept.Stench = false;
	currentPercept.Breeze = false;
	currentPercept.Glitter = false;
	currentPercept.Bump = false;
	currentPercept.Scream = false;
	// Check for stench
	if (Adjacent (currentState.agentLocation, currentState.wumpusLocation) ||
		(currentState.agentLocation == currentState.wumpusLocation)) // unlikely at initialization
	{
		currentPercept.Stench = true;
	}
	// Check for breeze
	vector<Location>::iterator itr;
	for (itr = currentState.pitLocations.begin(); itr != currentState.pitLocations.end(); itr++)
	{
		if (Adjacent (currentState.agentLocation, (*itr)))
		{
			currentPercept.Breeze = true;
		}
	}
	// Check for glitter
	if ((currentState.goldLocation.X == 1) && (currentState.goldLocation.Y == 1)) // unlikely at initialization
	{
		currentPercept.Glitter = true;
	}
}

Percept& WumpusWorld::GetPercept()
{
	return currentPercept;
}

void WumpusWorld::ExecuteAction (Action action)
// We assume the agent is alive and in the cave (i.e., game not over)
{
	numActions++;
	currentPercept.Bump = false;
	currentPercept.Scream = false;

	if (action == GOFORWARD)
	{
		if (currentState.agentOrientation == RIGHT)
		{
			if (currentState.agentLocation.X < currentState.worldSize)
			{
				currentState.agentLocation.X++;
			} else {
				currentPercept.Bump = true;
			}
		} else if (currentState.agentOrientation == UP)
		{
			if (currentState.agentLocation.Y < currentState.worldSize)
			{
				currentState.agentLocation.Y++;
			} else {
				currentPercept.Bump = true;
			}
		} else if (currentState.agentOrientation == LEFT)
		{
			if (currentState.agentLocation.X > 1)
			{
				currentState.agentLocation.X--;
			} else {
				currentPercept.Bump = true;
			}
		} else if (currentState.agentOrientation == DOWN)
		{
			if (currentState.agentLocation.Y > 1)
			{
				currentState.agentLocation.Y--;
			} else {
				currentPercept.Bump = true;
			}
		}
		// Update glitter percept
		currentPercept.Glitter = false;
		if ((! currentState.agentHasGold) && (currentState.agentLocation == currentState.goldLocation))
		{
			currentPercept.Glitter = true;
		}
		// Update stench percept (if agent co-located with or adjacent to alive or dead wumpus)
		currentPercept.Stench = false;
		if (Adjacent (currentState.agentLocation, currentState.wumpusLocation) ||
			(currentState.agentLocation == currentState.wumpusLocation))
		{
			currentPercept.Stench = true;
		}
		// Update breeze percept and check for death by pit
		currentPercept.Breeze = false;
		vector<Location>::iterator itr;
		for (itr = currentState.pitLocations.begin(); itr != currentState.pitLocations.end(); itr++)
		{
			if (Adjacent (currentState.agentLocation, (*itr)))
			{
				currentPercept.Breeze = true;
			}
			if (currentState.agentLocation == (*itr))
			{
				currentState.agentAlive = false;
			}
		}
		// Check for death by wumpus
		if (currentState.wumpusAlive && (currentState.agentLocation == currentState.wumpusLocation))
		{
			currentState.agentAlive = false;
		}
	}

	if (action == TURNLEFT)
	{
		if (currentState.agentOrientation == RIGHT)
		{
			currentState.agentOrientation = UP;
		} else if (currentState.agentOrientation == UP)
		{
			currentState.agentOrientation = LEFT;
		} else if (currentState.agentOrientation == LEFT)
		{
			currentState.agentOrientation = DOWN;
		} else if (currentState.agentOrientation == DOWN)
		{
			currentState.agentOrientation = RIGHT;
		}
	}

	if (action == TURNRIGHT)
	{
		if (currentState.agentOrientation == RIGHT)
		{
			currentState.agentOrientation = DOWN;
		} else if (currentState.agentOrientation == UP)
		{
			currentState.agentOrientation = RIGHT;
		} else if (currentState.agentOrientation == LEFT)
		{
			currentState.agentOrientation = UP;
		} else if (currentState.agentOrientation == DOWN)
		{
			currentState.agentOrientation = LEFT;
		}
	}

	if (action == GRAB)
	{
		if ((! currentState.agentHasGold) && (currentState.agentLocation == currentState.goldLocation))
		{
			currentState.agentHasGold = true;
			currentPercept.Glitter = false;
		}
	}
	if (action == SHOOT)
	{
		if (currentState.agentHasArrow)
		{
			currentState.agentHasArrow = false;
			if (currentState.wumpusAlive)
			{
				if (((currentState.agentOrientation == RIGHT) &&
					 (currentState.agentLocation.X < currentState.wumpusLocation.X) &&
					 (currentState.agentLocation.Y == currentState.wumpusLocation.Y)) ||
					((currentState.agentOrientation == UP) &&
					 (currentState.agentLocation.X == currentState.wumpusLocation.X) &&
					 (currentState.agentLocation.Y < currentState.wumpusLocation.Y)) ||
					((currentState.agentOrientation == LEFT) &&
					 (currentState.agentLocation.X > currentState.wumpusLocation.X) &&
					 (currentState.agentLocation.Y == currentState.wumpusLocation.Y)) ||
					((currentState.agentOrientation == DOWN) &&
					 (currentState.agentLocation.X == currentState.wumpusLocation.X) &&
					 (currentState.agentLocation.Y > currentState.wumpusLocation.Y)))
				{
					currentState.wumpusAlive = false;
					currentPercept.Scream = true;
				}
			}
		}
	}

	if (action == CLIMB)
	{
		if ((currentState.agentLocation.X == 1) && (currentState.agentLocation.Y == 1))
		{
			currentState.agentInCave = false;
			currentPercept.Stench = false;
			currentPercept.Breeze = false;
			currentPercept.Glitter = false;
		}
	}
}

bool WumpusWorld::GameOver ()
{
	if ((! currentState.agentInCave) || (! currentState.agentAlive))
	{
		return true;
	}
	return false;
}

int WumpusWorld::GetScore ()
{
	int score = 0;

	// -1 for each action
	score = score - numActions;

	// -10 for shooting the arrow (already lost 1 for the action)
	if (! currentState.agentHasArrow)
	{
		score = score - 9;
	}

	// +1000 for leaving the cave with the gold
	if (currentState.agentHasGold && (! currentState.agentInCave))
	{
		score = score + 1000;
	}

	// -1000 for dying
	if (! currentState.agentAlive)
	{
		score = score - 1000;
	}

	return score;
}

void WumpusWorld::Print ()
{
	int x;
	int y;

	cout << "World size = " << currentState.worldSize << "x" << currentState.worldSize << endl;
	// Print top line
	cout << "+";
	for (x = 1; x <= currentState.worldSize; x++)
	{
		cout << "---+";
	}
	cout << endl;
	// Print each row, starting at top
	for (y = currentState.worldSize; y > 0; y--)
	{
		// Print wumpus/gold/pit line
		cout << "|";
		for (x = 1; x <= currentState.worldSize; x++)
		{
			if (currentState.wumpusLocation == Location(x,y))
			{
				if (currentState.wumpusAlive)
				{
					cout << "W";
				} else {
					cout << "x";
				}
			} else {
				cout << " ";
			}
			if ((! currentState.agentHasGold) && (currentState.goldLocation == Location(x,y)))
			{
				cout << "G";

			} else {
				cout << " ";
			}
			if (find (currentState.pitLocations.begin(), currentState.pitLocations.end(), Location(x,y)) != currentState.pitLocations.end())
			{
				cout << "P";
			} else {
				cout << " ";
			}
			cout << "|";
		}
		cout << endl;
		cout << "|";
		// Print agent line
		for (x = 1; x <= currentState.worldSize; x++)
		{
			if (currentState.agentAlive && (currentState.agentLocation == Location(x,y)))
			{
				if (currentState.agentOrientation == RIGHT)
				{
					cout << " A>|";
				} else if (currentState.agentOrientation == UP)
				{
					cout << " A^|";
				} else if (currentState.agentOrientation == LEFT)
				{
					cout << " A<|";
				} else {
					cout << " Av|";
				}
			} else {
				cout << "   |";
			}
		}
		cout << endl;
		/*
		// Print empty next line
		cout << "|";
		for (x = 1; x <= currentState.worldSize; x++)
		{
			cout << "   |";
		}
		cout << endl;
		*/
		// Print boundary line
		cout << "+";
		for (x = 1; x <= currentState.worldSize; x++)
		{
			cout << "---+";
		}
		cout << endl;
	}
	cout << "Current percept = ";
	currentPercept.Print();
	cout << "Agent has gold = " << currentState.agentHasGold
		 << ", agent has arrow = " << currentState.agentHasArrow << endl;
	cout << "Current score = " << GetScore() << endl << endl;
}

void WumpusWorld::Write (const char* fileName)
{
        ofstream worldFileStream;

        worldFileStream.open (fileName);
        if (worldFileStream.is_open())
	{
		worldFileStream << "size " << currentState.worldSize << endl;
		worldFileStream << "wumpus " << currentState.wumpusLocation.X
			        << " " << currentState.wumpusLocation.Y << endl;
		worldFileStream << "gold " << currentState.goldLocation.X
			        << " " << currentState.goldLocation.Y << endl;
		vector<Location>::iterator itr;
		for (itr = currentState.pitLocations.begin();
		     itr != currentState.pitLocations.end(); itr++)
		{
			worldFileStream << "pit " << (*itr).X << " "
				        << (*itr).Y << endl;
		}
	} else {
                cout << "Unable to write world file " << fileName << endl;
                exit (1);
        }
        worldFileStream.close();
}
