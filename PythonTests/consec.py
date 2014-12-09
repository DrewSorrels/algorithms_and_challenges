# Finds how many numbers between botVal and topVal there are that 
# do not have a sum of three consecutive digits greater than 9.
# For example, 1346 would not pass this test because 3 + 4 + 6 > 9.
botVal = 10 ** 3
topVal = botVal + 2

def num(s):
	# Get the integer value for an inputted string
	# If it is not an integer, get the float value
	try: 
		return int(s)
	except exceptions.ValueError:
		return float(s)

def threeConsec(num):
	# Finds if three consecutive numbers have a sum of greater than 9
	# Return: 	True if sum < 9
	strNum = str( num )
	listNum = list(strNum)
	for i in enumerate( listNum ) :
		
		if ( num(listNum[i]) + num(listNum[i + 1]) + num(listNum[i - 1]) > 9 ):
			return False
	return True


# Start with a count of 0 and an empty character list
count = 0
char_list = []
sum = 0
for i in xrange(botVal, topVal):
	# Transfer the value i in to a character list.
	# Then check if any three consecutive numbers in that list have a sum of
	# greater than 9.  If not, then add one to the counter
	char_list = list(str(i))
	
	if( threeConsec(char_list) ):
		sum += 1

print sum	

		
