// PyAgent.h

#ifndef PYAGENT_H
#define PYAGENT_H

#include <Python.h>
#include "Action.h"
#include "Percept.h"

class Agent
{
public:
	Agent (PyObject *module);
	~Agent ();
	void Initialize ();
	Action Process (Percept& percept);
	void GameOver (int score);

	PyObject *pModule;
};

#endif // PYAGENT_H
