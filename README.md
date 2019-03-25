# Kirakojatek A*-al
# 8 Puzzle Solver Algorithm
Command Line Arguments
Compilation of Source.cpp like: 
For windows OS
  g++ -o main Source.cpp 
  and for running the program:
  .\main -input file.txt -solseq -pcost -nvisited -h 1
You can choose all or just any one command

The input file -input <FILE>
The file needs to contains a number as the first element of the text file that number will be the number of rows and columns.
After that you can enter your ideal puzzle.
For example:
3
1 0 4
5 6 7
8 2 3
-solseq returns to the command line the solution sequence
-pcost returns the number of moves
-nvisited returns the number of visited nodes
-h <number> is the the heuristic which you choose it can be either
1 Hamming or 2 Manhattan distance heuristic. If you don't specify the heuristic it will be Manhattan.

Study results:
# <3x3>
1)
Heuristic                           Hamming                 Manhattan
Number of steps:                    10                      10
Number of nodes visited:            47                      33
2)    
Number of steps:                    20                      20
Number of nodes visited:            3021                    393
3)    
Number of steps:                    24                      24
Number of nodes visited:            19857                   1003
 
# <4x4>
1)
Number of steps:                    30                      30
Number of nodes visited:            1721556                 17199
2)
Number of steps:                    28                       28
Number of nodes visited:            886432                   91080
# <5x5>
1)
Number of steps:                    21                      21
Number of nodes visited:            10084                   2182
2)
Number of steps:                    20                      20
Number of Nodes visited:            6434                    1399
