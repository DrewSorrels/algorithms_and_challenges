def ageMessage(years):
	if(years < "16"):
		print "You can't drive"
	elif(years < "18"):
		print "You can't vote"
	elif(years < "25"):
		print "You can't rent a car"
	else :
		print "You can do anything that's legal"

age = raw_input("How old are you? ")
ageMessage(age)
