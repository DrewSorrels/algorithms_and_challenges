def collatz(num):
	# A basic implementation of the collatz algorithm.
	# If the number is even, divide by two
	# otherwise, multiply by three and add 1.
	# Calculates the number of steps to get to 1 from num.
	# Ex: Path from 5: 5 > 16 > 8 > 4 > 2 > 1
	if(num > 1):
		
		if(num % 2 == 0):
			return 1 + collatz(num/2)
		else:
			return 1 + collatz(3 * num + 1)
	return 0

num = raw_input("Enter a number and I will show you how many steps it takes to get to 0: ")

print "Number of steps for ", num, ": ", str(collatz(int(num)))
