To run the game engine, write the following commands in terminal:
1. >> make
2. >>./game

On running the game engine, the engine will ask you to choose the interpretation for subtract that you want to follow throughout the game.
You can choose A or B depending on your preference.
After choosing a preference, the game engine required for the assignment would start.

Assumptions:
1. In case a valid move command doesn't change board state, it will be considered a successful move but no random tile will be added.
2. Two interpretation are incorporated for subtraction moves. Interpretation that the engine should follow can be chosen at the start of the game. It is assumed that automated testing would only be done after choosing an interpretation.
3. Empty tile has following assumptions:
	3.1 It has value 0 when queried.
	3.2 No variable name can be assigned to it.
	3.3 All variable names are dropped when value 0 is assigned to a tile.
4. Variable name only contains alphabets.
5. STDERR Outputs:
	5.1. Successful moves, naming and assignment: board state
	5.2. Successful query: value of tile
	5.3. Any error: -1
6. On merging tiles, variable names of the tile to which the other tile is merged would come first.
7. Board State on STDOUT would only be shown on successful moves and assignment commands.

Folder contents:
1. game.l: flex scanner
2. game.y: bison parser
3. g2048.h: header file for game board structure and functions
4. g2048.c: implementations of game functions
5. driver.c: main .c file
6. Makefile: for easy compilation

Package versions used:
1. gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
2. flex 2.6.4
3. bison (GNU Bison) 3.5.1
