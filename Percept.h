// Percept.h

#ifndef PERCEPT_H
#define PERCEPT_H

#include <vector>

using namespace std;

class Percept
{
public:
	Percept ();
	Percept (bool stench, bool breeze, bool glitter, bool bump, bool scream);
	Percept (const Percept& percept);
	Percept& operator= (const Percept& percept);
	void SetPercept (bool stench, bool breeze, bool glitter, bool bump, bool scream);
	void Print ();

	bool Stench;
	bool Breeze;
	bool Glitter;
	bool Bump;
	bool Scream;
};

typedef vector<Percept> PerceptList;

#endif // PERCEPT_H

