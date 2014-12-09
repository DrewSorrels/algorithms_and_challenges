import ThreeBox

class Puzzle(object): 
	
	def __init__(self):
		self.boxes = []
		for _ in xrange(3):
			sublist = []
			for j in xrange(3):
				sublist.append(ThreeBox.ThreeBox())
			self.boxes.append(sublist)
testSudoku = Puzzle()

for i in range(3):
	for j in range(3):
		currentBox = testSudoku.boxes[i][j]
		for k in range(3):
			for l in range(3):
				print currentBox.boxes[k][l]