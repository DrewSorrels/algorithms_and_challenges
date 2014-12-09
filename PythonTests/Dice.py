import random

def total(a, b) :
	return a+b

print "LET THE GAMES BEGIN!!"
numGames = int(raw_input("How many games do you want to play? "))
for i in range(0,numGames):
	die = random.randint(1,6)
	die2 = random.randint(1,6)
	print "Roll #1: %d" %die
	print "Roll #2: %d" %die2
	print "Total: %d" %total(die,die2)
	print "===================="