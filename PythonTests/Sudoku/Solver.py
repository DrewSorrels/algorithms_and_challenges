import Puzzle


class Solver(object):
	puzzle = Puzzle.Puzzle().boxes
	
	def linCheck(bigX, bigY, x, y):
		original = puzzle[bigX][bigY].boxes[x][y]
		
		hCount = 0
		vCount = 0
		for i in range(3):
			for j in range(3):
				if(puzzle[i][bigY].boxes[j][y] == original):
					hCount++
				if(puzzle[bigX][i].boxes[x][j] == original):
					vCount++
				if(hCount > 1 || vCount > 1):
					return 1
		return 0
	
	def boxCheck(bigX, bigY, x, y):
		original = puzzle[bigX][bigY].boxes[x][y]
		count = 0
		for i in range(3):
			for j in range(3):
				if(puzzle[bigX][bigY].boxes[i][j] == original):
					count++
				if(count > 1):
					return 1
		return 0
		
	def cycleVals(bigX, bigY, x, y):
		bcount = 0
		lcount = 0
		lastVal = 0
		if puzzle[bigX][bigY].boxes[x][y] == 0:
			for i in range(1,9):
				puzzle[bigX][bigY].boxes[x][y] = i
				bcount = bcount + boxCheck(bigX, bigY, x, y)
				lcount = lcount + linCheck(bigX, bigY, x, y)
				if(bcount == 0 && lcount == 0):
					lastVal = puzzle[bigX][bigY].boxes[x][y]
			if(lcount == 0 && bcount == 0):
				puzzle[bigX][bigY].boxes[x][y] = lastVal
			else:
				puzzle[bigX][bigY].boxes[x][y] = 0
				
	def solvePuzzle():
		unsolved = []
		for i in range(3):
			for j in range(3):
				for row in range(3):
					for col in range(3):
						cycleVals(i, j, row, col)
						if puzzle[bigX][bigY].boxes[x][y] == 0:
							unsolved.append([bigX, bigY, x, y])
		
		while(len(unsolved) > 0):
			for i, item in enumerate(unsolved):
				cycleVals(item[0], item[1], item[2], item[3])
				if puzzle[item[0]][item[1]].boxes[item[2]][item[3]] != 0
					unsolved.pop(i)