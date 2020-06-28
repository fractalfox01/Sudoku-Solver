# Sudoku-Solver
A sudoku solver implementation in C

### Details:
A simple sudoku solver written in C.
Uses iterative backtracking. Originaly as recursive but the stack blows with harder puzzles.
If using code on a unix/linux based machine then slight modification to the code is needed.
in the get_puzzle function the 11 in the read() function should be a 10. simple
but for some reason it's 1 off between systems.

## Using this program:
<pre>$> gcc -g main.c -o sudoku_solver
$> ./sudoku_solver puzzle1
Original:
1 0 0 0 0 0 0 0 0
0 0 0 5 0 4 0 0 0
0 7 0 1 6 9 0 5 0
0 6 0 0 0 0 0 3 0
0 8 1 0 0 0 4 2 0
0 0 9 4 0 8 5 0 0
9 0 0 8 0 5 0 0 1
0 1 0 0 0 0 0 7 0
0 5 0 6 0 3 0 4 0
solved

HARD PUZZLE
2023846
1 9 5 3 2 7 6 8 4
2 3 6 5 8 4 1 9 7
4 7 8 1 6 9 2 5 3
5 6 4 2 9 1 7 3 8
3 8 1 7 5 6 4 2 9
7 2 9 4 3 8 5 1 6
9 4 2 8 7 5 3 6 1
6 1 3 9 4 2 8 7 5
8 5 7 6 1 3 9 4 2</pre>

## Puzzle file format
Puzzles must only contain the numbers 1 - 9 and must substitue all 0 (zeros) for '.' (periods)
!!!And must end in a newline!!! Thems the rules, don't like them? change the code :D
Example:
<pre>1........
...5.4...
.7.169.5.
.6.....3.
.81...420
..94.85..
.1.....7.
.5.6.3.4.

</pre>
