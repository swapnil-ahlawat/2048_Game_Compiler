#include <stdio.h>
#include <stdlib.h>

#ifndef _g2048
#define _g2048

#define N 4

typedef struct{
	int board[N][N]; //stores the board state
	int numEmptyLocations; //number of empty locations in current board state
	char *variables[N][N][N*N]; //variable names for tiles
	int numVariables[N][N]; //number of variable names per tile
	char *variablesUsed[N*N*N*N]; //pool of all the variables used
	int totalNumVariables; //total number of variables used
} BoardState;

//initialising and destroying board
extern void initialise();
extern void destructor();

//print board states
extern void printBoard();
extern void printStderr();

//functions to implement moves on board
extern void move(int operation, int direction);
extern int moveDir(int operation);
extern void transpose();
extern void horizontalFlip();

//random tiles adder function
extern int generateRandomBlock();

//getter and setters for tiles
extern int getPositionValue(int i, int j, int print);
extern int setPosition(int val, int i, int j, int print);
extern int setVariable(char *variableName, int i, int j);



extern BoardState currentBoard; //global board state
extern char interpretation; //global subtraction interpretation to follow 

#endif
