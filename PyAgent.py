# PyAgent.py

import Action
import Orientation

def PyAgent_Constructor ():
    print "PyAgent_Constructor"

def PyAgent_Destructor ():
    print "PyAgent_Destructor"

def PyAgent_Initialize ():
    print "PyAgent_Initialize"

def PyAgent_Process (stench,breeze,glitter,bump,scream):
    perceptStr = ""
    if (stench == 1):
        perceptStr += "Stench=True,"
    else:
        perceptStr += "Stench=False,"
    if (breeze == 1):
        perceptStr += "Breeze=True,"
    else:
        perceptStr += "Breeze=False,"
    if (glitter == 1):
        perceptStr += "Glitter=True,"
    else:
        perceptStr += "Glitter=False,"
    if (bump == 1):
        perceptStr += "Bump=True,"
    else:
        perceptStr += "Bump=False,"
    if (scream == 1):
        perceptStr += "Scream=True"
    else:
        perceptStr += "Scream=False"
    print "PyAgent_Process: " + perceptStr
    
    return Action.GOFORWARD

def PyAgent_GameOver (score):
    print "PyAgent_GameOver: score = " + str(score)
