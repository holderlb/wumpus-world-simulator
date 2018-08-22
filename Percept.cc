// Percept.cc

#include <iostream>
#include "Percept.h"

Percept::Percept ()
{
	Stench = false;
	Breeze = false;
	Glitter = false;
	Bump = false;
	Scream = false;
}

Percept::Percept (bool stench, bool breeze, bool glitter, bool bump, bool scream)
{
	Stench = stench;
	Breeze = breeze;
	Glitter = glitter;
	Bump = bump;
	Scream = scream;
}

Percept::Percept (const Percept& percept)
{
	Stench = percept.Stench;
	Breeze = percept.Breeze;
	Glitter = percept.Glitter;
	Bump = percept.Bump;
	Scream = percept.Scream;
}

Percept& Percept::operator= (const Percept& percept)
{
	if (this == &percept)
	{
		return *this;
	}
	Stench = percept.Stench;
	Breeze = percept.Breeze;
	Glitter = percept.Glitter;
	Bump = percept.Bump;
	Scream = percept.Scream;
	return *this;
}

void Percept::SetPercept (bool stench, bool breeze, bool glitter, bool bump, bool scream)
{
	Stench = stench;
	Breeze = breeze;
	Glitter = glitter;
	Bump = bump;
	Scream = scream;
}

void Percept::Print ()
{
	cout << "[Stench=" << Stench << ","
		 << "Breeze=" << Breeze << ","
		 << "Glitter=" << Glitter << ","
		 << "Bump=" << Bump << ","
		 << "Scream=" << Scream << "]" << endl;
}
