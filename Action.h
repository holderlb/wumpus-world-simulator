// Action.h

#ifndef ACTION_H
#define ACTION_H

#include <vector>

using namespace std;

enum Action {GOFORWARD, TURNLEFT, TURNRIGHT, GRAB, SHOOT, CLIMB};

typedef vector<Action> ActionList;

void PrintAction (Action action);

#endif // ACTION_H
