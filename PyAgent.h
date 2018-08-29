// PyAgent.h

#ifndef PYAGENT_H
#define PYAGENT_H

#include <Python.h>
#include "Action.h"
#include "Percept.h"

#if PY_MAJOR_VERSION >= 3
#define PyInt_FromLong PyLong_FromLong
#define PyInt_AsLong PyLong_AsLong
#endif

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
