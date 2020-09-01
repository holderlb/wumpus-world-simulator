# PyAgent.py

from Agent import Agent
from Percept import Percept

py_agent = None

def PyAgent_Constructor ():
    global py_agent
    py_agent = Agent()

def PyAgent_Destructor ():
    global py_agent
    py_agent = None

def PyAgent_Initialize ():
    global py_agent
    py_agent.Initialize()

def PyAgent_Process (stench, breeze, glitter, bump, scream):
    global py_agent
    percept = Percept()
    percept.set_percept(bool(stench), bool(breeze), bool(glitter), bool(bump), bool(scream))
    return py_agent.Process(percept)

def PyAgent_GameOver (score):
    global py_agent
    py_agent.GameOver(score)
