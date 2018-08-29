// wumpsim.cc
//
// Main Wumpus Simulator procedure.

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include "Percept.h"
#include "Action.h"
#include "WumpusWorld.h"
#include "wumpsim.h"

#ifdef PYTHON
#include <Python.h>
#include "PyAgent.h"
#else
#include "Agent.h"
#endif

using namespace std;

int main (int argc, char *argv[])
{
	int worldSize = 4;
	int numTrials = 1;
	int numTries = 1;
	unsigned seed;
	char* worldFile;
	bool seedSet = false;
	bool worldSet = false;

#ifdef PYTHON
	PyObject *pName, *pModule;
	Py_Initialize();
	#if PY_MAJOR_VERSION >= 3
		pName = PyUnicode_FromString("PyAgent");
	#else
		pName = PyString_FromString("PyAgent");
	#endif
	pModule = PyImport_Import(pName);
	if (pModule == NULL) {
		cout << "pModule = NULL\n";
		PyErr_Print();
		exit(1);
	}
	Py_DECREF(pName);
#endif

	// Process command-line options
	int i = 1;
	while (i < argc)
	{
		if (strcmp (argv[i], "-size") == 0)
		{
			i++;
			worldSize = atoi (argv[i]);
			if (worldSize < 2)
			{
				worldSize = 2;
			}
		} else if (strcmp (argv[i], "-trials") == 0)
		{
			i++;
			numTrials = atoi (argv[i]);
		} else if (strcmp (argv[i], "-tries") == 0)
		{
			i++;
			numTries = atoi (argv[i]);
		} else if (strcmp (argv[i], "-seed") == 0)
		{
			i++;
			seed = atoi (argv[i]);
			seedSet = true;
		} else if (strcmp (argv[i], "-world") == 0)
		{
			i++;
			worldFile = argv[i];
			worldSet = true;
		} else {
			cout << "unknown option " << argv[i] << endl;
			exit (1);
		}
		i++;
	}

	// Set random number generator seed
	if (! seedSet)
	{
		seed = (unsigned) time (0);
	}
	srand (seed);

	// Print welcome
	cout << "Welcome to the Wumpus World Simulator v";
        cout << WUMPSIM_VERSION << ".  Happy hunting!" << endl << endl;

	// Run trials
	WumpusWorld* wumpusWorld = NULL;
	Agent* agent = NULL;
	Percept percept;
	Action action;
	int score;
	int trialScore;
	int totalScore = 0;
	float averageScore;
	int numMoves;

	for (int trial = 1; trial <= numTrials; trial++)
	{
		if (worldSet)
		{
			wumpusWorld = new WumpusWorld (worldFile);
		} else {
			wumpusWorld = new WumpusWorld (worldSize);
		}
		//wumpusWorld->Write (".world");
#ifdef PYTHON
		agent = new Agent (pModule);
#else
		agent = new Agent ();
#endif
		trialScore = 0;
		for (int tries = 1; tries <= numTries; tries++)
		{
			wumpusWorld->Initialize();
			agent->Initialize ();
			numMoves = 0;
			cout << "Trial " << trial << ", Try " << tries << " begin" << endl << endl;
			while ((! wumpusWorld->GameOver()) && (numMoves < MAX_MOVES_PER_GAME))
			{
				wumpusWorld->Print();
				percept = wumpusWorld->GetPercept();
				action = agent->Process (percept);
				cout << "Action = ";
				PrintAction (action);
				cout << endl << endl;
				wumpusWorld->ExecuteAction (action);
				numMoves++;
			}
			score = wumpusWorld->GetScore();
			agent->GameOver (score);
			trialScore = trialScore + score;
			cout << "Trial " << trial << ", Try " << tries << " complete: Score = " << score << endl << endl;
		}
		delete agent;
		delete wumpusWorld;
		averageScore = ((float) trialScore) / ((float) numTries);
		cout << "Trial " << trial << " complete: Average score for trial = " << averageScore << endl << endl;
		totalScore = totalScore + trialScore;
	}
	averageScore = ((float) totalScore) / ((float) (numTrials * numTries));
	cout << "All trials completed: Average score for all trials = " << averageScore << endl;
	cout << "Thanks for playing!" << endl << endl;

#ifdef PYTHON
	//Py_DECREF(pModule);
	Py_Finalize();
#endif

	return 0;
}
