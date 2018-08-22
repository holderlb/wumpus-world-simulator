// Orientation.cc

#include <iostream>
#include "Orientation.h"

using namespace std;

void PrintOrientation (Orientation orientation)
{
	if (orientation == UP)
	{
		cout << "UP";
	}
	if (orientation == DOWN)
	{
		cout << "DOWN";
	}
	if (orientation == LEFT)
	{
		cout << "LEFT";
	}
	if (orientation == RIGHT)
	{
		cout << "RIGHT";
	}
}
