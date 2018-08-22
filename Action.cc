// Action.cc

#include <iostream>
#include "Action.h"

void PrintAction (Action action)
{
	if (action == GOFORWARD)
	{
		cout << "GOFORWARD";
	}
	if (action == TURNLEFT)
	{
		cout << "TURNLEFT";
	}
	if (action == TURNRIGHT)
	{
		cout << "TURNRIGHT";
	}
	if (action == GRAB)
	{
		cout << "GRAB";
	}
	if (action == SHOOT)
	{
		cout << "SHOOT";
	}
	if (action == CLIMB)
	{
		cout << "CLIMB";
	}
}
