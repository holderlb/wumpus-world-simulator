# Percept.py

class Percept:
	def __init__(self):
		self.set_percept(False, False, False, False, False)
	
	def __str__(self):
		s = "[Stench=" + str(self.stench)
		s += ",Breeze=" + str(self.breeze)
		s += ",Glitter=" + str(self.glitter)
		s += ",Bump=" + str(self.bump)
		s += ",Scream=" + str(self.scream) + "]"
		return s
		
	def set_percept(self, stench, breeze, glitter, bump, scream):
		self.stench = stench
		self.breeze = breeze
		self.glitter = glitter
		self.bump = bump
		self.scream = scream

