// Location.cc

#include "Location.h"

Location::Location ()
{
	X = 0;
	Y = 0;
}

Location::Location (int x, int y)
{
	X = x;
	Y = y;
}

Location::Location (const Location& location)
{
	X = location.X;
	Y = location.Y;
}

Location& Location::operator= (const Location& location)
{
	if (this == &location)
	{
		return *this;
	}
	X = location.X;
	Y = location.Y;
	return *this;
}

bool Location::operator== (const Location& location) const
{
	if ((X == location.X) && (Y == location.Y))
	{
		return true;
	}
	return false;
}

bool Adjacent (const Location& location1, const Location& location2)
{
	int X1 = location1.X;
	int X2 = location2.X;
	int Y1 = location1.Y;
	int Y2 = location2.Y;

	if (((X1 == X2) && (Y1 == (Y2 - 1))) ||
		((X1 == X2) && (Y1 == (Y2 + 1))) ||
		((X1 == (X2 - 1)) && (Y1 == Y2)) ||
		((X1 == (X2 + 1)) && (Y1 == Y2)))
	{
		return true;
	}
	return false;
}
