# 2048 Game Compiler
The project has been done as an assignment of Compiler Construction course.

## Commands to run the engine
To run the game engine, write the following commands in terminal:
1. >> make
2. >>./game

## Folder contents:
1. game.l: flex scanner
2. game.y: bison parser
3. g2048.h: header file for game board structure and functions
4. g2048.c: implementations of game functions
5. driver.c: main .c file
6. Makefile: for easy compilation

## The Game
It is a 2048-game ”family”: Here, variations on the original 2048 game are to be also provided
for. The variations are:
1. Allowing subtraction, multiplication and division in addition to the plain doubling operation at tile mergers. Thus, each move, when it is making two same-value tiles merge, may obliterate them together (making them 0 by subtraction), or reduce them to 1 by divition, or square them by multiplication. In this variation, the goal also will be flexible, any number not necessarily a power of 2 will be achievable.
2. Allowing variables in place of tile values to make puzzles


### The Operations
**16 Moves**: ADD/SUBTRACT/MULTIPLY/DIVIDE LEFT/RIGHT/UP/DOWN. : Natural, except the extensions due to the airthmetic operations added, and the variables assigned.
**Assignment**: ASSIGN <<value>> TO <<x>>,<<y>>: Setting a tile value.
**Naming**: VAR <<varname>> is <<x>>,<<y>>: Naming a tile. Each subsequent move will move the name also to the destination of this tile according to merging and
stopping results. This may result in a tile getting several names.
Query: VALUE IN <<x>>,<<y>>: This value can be used in an assignment.

## The Scanner
The keywords are (they are case-sensitive):
ADD
SUBTRACT
MULTIPLY
DIVIDE
LEFT
RIGHT
UP
DOWN
ASSIGN
TO
VAR
IS
VALUE
IN
Remaining token types will be identifiers, numbers, and punctuation symbols <,.?>. Commands must end with a full-stop. Co-ordinates must be separated by a comma, and optional whitespace. However, in the stderr output, there must not be whitespace
between two co-ordinates of a tile, only a comma should be there.

## The Parser
A suitable grammar to represent the operations has been made. Then make a syntax-directed translation scheme using bison or otherwise.
If you incorporate advanced error handling into the scheme (from semantic all the way
down to lexical errors), you will get bonus credit.

On running the game engine, the engine will ask you to choose the interpretation for subtract that you want to follow throughout the game.
You can choose A or B depending on your preference.
After choosing a preference, the game engine required for the assignment would start.

## Assumptions:
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

## Package versions used:
1. gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
2. flex 2.6.4
3. bison (GNU Bison) 3.5.1
