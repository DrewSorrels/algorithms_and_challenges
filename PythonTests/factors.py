sequel = input("Enter a number to find all factors: ") 

for i in range(1, sequel):
	if sequel % i == 0:
		print i
