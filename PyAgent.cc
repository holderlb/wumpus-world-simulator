// PyAgent.cc

#include "PyAgent.h"

using namespace std;

PyObject * myPyObject_CallObject(PyObject *callable_object, PyObject *args) {
	PyObject *pValue = PyObject_CallObject(callable_object, args);
	if (pValue == NULL) {
		PyErr_Print();
		exit(1);
	}
	return pValue;
}

Agent::Agent (PyObject* module)
{
	pModule = module;
	PyObject *pFunc = PyObject_GetAttrString(pModule, "PyAgent_Constructor");
	myPyObject_CallObject(pFunc, NULL);
	Py_DECREF(pFunc);
}

Agent::~Agent ()
{
	PyObject *pFunc = PyObject_GetAttrString(pModule, "PyAgent_Destructor");
	myPyObject_CallObject(pFunc, NULL);
	Py_DECREF(pFunc);
}

void Agent::Initialize ()
{
	PyObject *pFunc = PyObject_GetAttrString(pModule, "PyAgent_Initialize");
	myPyObject_CallObject(pFunc, NULL);
	Py_DECREF(pFunc);
}

Action Agent::Process (Percept& percept)
{
	PyObject *pValue;
	PyObject *pArgs = PyTuple_New(5);
	if (percept.Stench) {
		pValue = PyInt_FromLong(1);
	} else {
		pValue = PyInt_FromLong(0);
	}
	PyTuple_SetItem(pArgs, 0, pValue);
	if (percept.Breeze) {
		pValue = PyInt_FromLong(1);
	} else {
		pValue = PyInt_FromLong(0);
	}
	PyTuple_SetItem(pArgs, 1, pValue);
	if (percept.Glitter) {
		pValue = PyInt_FromLong(1);
	} else {
		pValue = PyInt_FromLong(0);
	}
	PyTuple_SetItem(pArgs, 2, pValue);
	if (percept.Bump) {
		pValue = PyInt_FromLong(1);
	} else {
		pValue = PyInt_FromLong(0);
	}
	PyTuple_SetItem(pArgs, 3, pValue);
	if (percept.Scream) {
		pValue = PyInt_FromLong(1);
	} else {
		pValue = PyInt_FromLong(0);
	}
	PyTuple_SetItem(pArgs, 4, pValue);
	PyObject *pFunc = PyObject_GetAttrString(pModule, "PyAgent_Process");
	pValue = myPyObject_CallObject(pFunc, pArgs);
	Action action = (Action) PyInt_AsLong(pValue);
	Py_DECREF(pValue);
	Py_DECREF(pArgs);
	Py_DECREF(pFunc);
	return action;
}

void Agent::GameOver (int score)
{
	PyObject *pArgs = PyTuple_New(1);
	PyObject *pValue = PyInt_FromLong(score);
	PyTuple_SetItem(pArgs, 0, pValue);
	PyObject *pFunc = PyObject_GetAttrString(pModule, "PyAgent_GameOver");
	myPyObject_CallObject(pFunc, pArgs);
	Py_DECREF(pArgs);
	//Py_DECREF(pValue);
	Py_DECREF(pFunc);
}

