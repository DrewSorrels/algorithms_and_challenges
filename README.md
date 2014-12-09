algorithms_and_challenges
=========================

This repository features a lot of smaller algorithmic challenges and exercises that I have completed that do not merit their own repository.  Challenges come from a variety of sources.

Major Challenges
=========================

Gridwalk:
There is a monkey which can walk around on a planar grid. The monkey can move one space at a time left, right, up or down. That is, from (x, y) the monkey can go to (x+1, y), (x-1, y), (x, y+1), and (x, y-1). Points where the sum of the digits of the absolute value of the x coordinate plus the sum of the digits of the absolute value of the y coordinate are lesser than or equal to 19 are accessible to the monkey. For example, the point (59, 79) is inaccessible because 5 + 9 + 7 + 9 = 30, which is greater than 19. Another example: the point (-5, -7) is accessible because abs(-5) + abs(-7) = 5 + 7 = 12, which is less than 19. How many points can the monkey access if it starts at (0, 0), including (0, 0) itself?

Game of Life Parallel:
A parallel implementation of the classic Conway's game of life.  In this directory, there is both a pthread and a cuda implementation of the game of life cellular automata problem.  In this particular problem, a CUDA implementation offers significant advantages due to the GPUs having tremendous performance for matrix applications.