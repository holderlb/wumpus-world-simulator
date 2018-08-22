// Location.h

#ifndef LOCATION_H
#define LOCATION_H

class Location
{
public:
	Location ();
	Location (int x, int y);
	Location (const Location& location);
	Location& operator= (const Location& location);
	bool operator== (const Location& location) const;

	int X;
	int Y;
};

bool Adjacent (const Location& location1, const Location& location2);

#endif // LOCATION_H
