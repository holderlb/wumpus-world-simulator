// Agent.cc

#include <iostream>
#include "Agent.h"

using namespace std;

Agent::Agent ()
{

}

Agent::~Agent ()
{

}

void Agent::Initialize ()
{

}

Action Agent::Process (Percept& percept)
{
	char c;
	Action action;
	bool validAction = false;

	while (! validAction)
	{
		validAction = true;
		cout << "Action? ";
		cin >> c;
		if (c == 'f') {
			action = GOFORWARD;
		} else if (c == 'l') {
			action = TURNLEFT;
		} else if (c == 'r') {
			action = TURNRIGHT;
		} else if (c == 'g') {
			action = GRAB;
		} else if (c == 's') {
			action = SHOOT;
		} else if (c == 'c') {
			action = CLIMB;
		} else {
			cout << "Huh?" << endl;
			validAction = false;
		}
	}
	return action;
}

void Agent::GameOver (int score)
{

}

