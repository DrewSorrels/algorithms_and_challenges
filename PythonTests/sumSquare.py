sigma = 100000000
print sigma
values = []
sum = 0;

def sigma2(num):
	someNums = [1, 2]
	for i in range(num):
		if ( i > 0 ) :
			if(num % i == 0 ):
				someNums.append(i)
	return someNums.append(num)

for i in range(sigma):
	if ( i > 0 ) :
		if (sigma % i == 0):
			values.extend(sigma2(i))
			
for i in values:
	sum = sum + i**2


print sum