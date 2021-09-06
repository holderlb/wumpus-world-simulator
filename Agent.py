# Agent.py

import sys
import Action

_GetInput = raw_input if sys.version_info[0] < 3 else input #if Python 2 else Python 3

class Agent:
    def __init__(self):
        pass
    
    def __del__(self):
        pass
    
    def Initialize(self):
        pass
    
    def Process(self, percept):
        valid_action = False
        while not valid_action:
            valid_action = True
            c = _GetInput("Action? ")
            if c == 'f':
                action = Action.GOFORWARD
            elif c == 'l':
                action = Action.TURNLEFT
            elif c == 'r':
                action = Action.TURNRIGHT
            elif c == 'g':
                action = Action.GRAB
            elif c == 's':
                action = Action.SHOOT
            elif c == 'c':
                action = Action.CLIMB
            else:
                print("Huh?")
                valid_action = False
        return action
    
    def GameOver(self, score):
        pass
