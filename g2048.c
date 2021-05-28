#include <stdio.h>
#include <string.h>
#include "g2048.h"

//initialise currentBoard State structure values
void initialise() {
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			currentBoard.board[i][j]=0;
			currentBoard.numVariables[i][j]=0;
		}
	}
	currentBoard.totalNumVariables=0;
	currentBoard.numEmptyLocations = N*N;
}

//add a random tile
int generateRandomBlock(){
	int pos = rand() % currentBoard.numEmptyLocations, val = rand() % 2 + 1, currentEmpty = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (currentBoard.board[i][j] == 0) {
				if (currentEmpty == pos) {
					currentBoard.board[i][j] = 1 << val;
				}
				currentEmpty++;
			}
		}
	}
	currentBoard.numEmptyLocations--;
	return 1;

}

//print current board state in STDOUT
void printBoard() {
	for( int i = 0; i < N; i++ )
	{
	    printf("+-------+-------+-------+-------+\n| ");
	    for( int j = 0; j < N; j++ )
	    {
			if(currentBoard.board[i][j]==0) printf("     ");
			else printf("%5d", currentBoard.board[i][j]);
			printf(" | ");
	    }
	    printf("\n");
	}
	printf("+-------+-------+-------+-------+\n");
}

//print current board state in STDERR
void printStderr(){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			fprintf(stderr, "%d ", currentBoard.board[i][j]);
		}
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(currentBoard.numVariables[i][j]!=0){
				fprintf(stderr, "%d,%d", i+1, j+1);
				for(int k=0; k<currentBoard.numVariables[i][j]; k++){
					fprintf(stderr, "%s", currentBoard.variables[i][j][k]);
					if(k!=currentBoard.numVariables[i][j]-1){
						fprintf(stderr, ",");
					}
				}
				fprintf(stderr, " ");
			}
		}
	}
	fprintf(stderr, "\n");
}

//function to move left
int moveDir(int operation){
	int flag = 0;
	for (int i = 0; i < N; i++) {
		int j=0, k=0;
		while(j<N){
			if(currentBoard.board[i][j]){
				if(k!=j){
					currentBoard.board[i][k]= currentBoard.board[i][j];
					for(int l=0; l<currentBoard.numVariables[i][j]; l++){
						currentBoard.variables[i][k][currentBoard.numVariables[i][k]]= currentBoard.variables[i][j][l];
						currentBoard.variables[i][j][l]=NULL;
						currentBoard.numVariables[i][k]++; 
					}
					currentBoard.board[i][j] = 0;
					currentBoard.numVariables[i][j]=0;
					flag = 1;
				}
				k++;
			}
			j++;
		}
		j=0;
		while(j<(N-1)){
			if(currentBoard.board[i][j] && currentBoard.board[i][j]== currentBoard.board[i][j+1]){
				currentBoard.board[i][j+1]=0;
				for(int l=0; l<currentBoard.numVariables[i][j+1]; l++){
					currentBoard.variables[i][j][currentBoard.numVariables[i][j]]= currentBoard.variables[i][j+1][l];
					currentBoard.variables[i][j+1][l]=NULL;
					currentBoard.numVariables[i][j]++; 
				}
				currentBoard.board[i][j+1] = 0;
				currentBoard.numVariables[i][j+1]=0;
				switch(operation){
					case 0: currentBoard.board[i][j] *=2;
						break;
					case 1: setPosition(0, i, j, 0);
						break;
					case 2: currentBoard.board[i][j] *= currentBoard.board[i][j];
						break;
					case 3: currentBoard.board[i][j] = 1;
						break;
				}
				flag = 1;
				currentBoard.numEmptyLocations++;
				for(int k=j+1; k<N-1; k++){
					currentBoard.board[i][k]=currentBoard.board[i][k+1];
					for(int l=0; l<currentBoard.numVariables[i][k+1]; l++){
						currentBoard.variables[i][k][currentBoard.numVariables[i][k]]= currentBoard.variables[i][k+1][l];
						currentBoard.variables[i][k+1][l]=NULL;
						currentBoard.numVariables[i][k]++; 
					}
					currentBoard.board[i][k+1] = 0;
					currentBoard.numVariables[i][k+1]=0;
				}	
			}
			j++;
		}
		if(operation==1 && interpretation=='B'){
			j=0, k=0;
			while(j<N){
				if(currentBoard.board[i][j]){
					if(k!=j){
						currentBoard.board[i][k]= currentBoard.board[i][j];
						for(int l=0; l<currentBoard.numVariables[i][j]; l++){
							currentBoard.variables[i][k][currentBoard.numVariables[i][k]]= currentBoard.variables[i][j][l];
							currentBoard.variables[i][j][l]=NULL;
							currentBoard.numVariables[i][k]++; 
						}
						currentBoard.board[i][j] = 0;
						currentBoard.numVariables[i][j]=0;
						flag = 1;
					}
					k++;
				}
				j++;
			}
		}

	}
	return flag;
}

//transposing current board state
void transpose() 
{ 
    for (int i = 0; i < N; i++){ 
        for (int j = 0; j < i; j++){
        	int temp= currentBoard.board[i][j];
        	currentBoard.board[i][j]= currentBoard.board[j][i];
        	currentBoard.board[j][i]=temp;

        	for(int k=0; k<N*N; k++){
        		char *a= currentBoard.variables[i][j][k];
        		currentBoard.variables[i][j][k]= currentBoard.variables[j][i][k];
        		currentBoard.variables[j][i][k]= a;
        	}
        	temp = currentBoard.numVariables[i][j];
        	currentBoard.numVariables[i][j]= currentBoard.numVariables[j][i];
        	currentBoard.numVariables[j][i]= temp;
        } 
    }
}

//horizontal flipping current board state
void horizontalFlip() 
{ 
    for (int i = 0; i < N; i++){ 
        for (int j = 0; j < N/2; j++){
        	int temp= currentBoard.board[i][j];
        	currentBoard.board[i][j]= currentBoard.board[i][N-j-1];
        	currentBoard.board[i][N-j-1]=temp;

        	for(int k=0; k<N*N; k++){
        		char *a= currentBoard.variables[i][j][k];
        		currentBoard.variables[i][j][k]= currentBoard.variables[i][N-j-1][k];
        		currentBoard.variables[i][N-j-1][k]= a;
        	}
        	temp = currentBoard.numVariables[i][j];
        	currentBoard.numVariables[i][j]= currentBoard.numVariables[i][N-j-1];
        	currentBoard.numVariables[i][N-j-1]= temp;
        } 
    }
}

//function to make moves
void move(int operation, int direction) {
	int flag = 0;
	printf("2048> Thanks, ");
	
	switch (direction) {
		//case left
		case 0:	flag = moveDir(operation);
				printf("left");
			break;
		//case right: horizontal flip board, move left and then again flip
		case 1:	horizontalFlip();
				flag = moveDir(operation);
				horizontalFlip();
				printf("right");
			break;
		//case up: transpose board, move left and then again transpose
		case 2:	transpose();
				flag = moveDir(operation);
				transpose();
				printf("up");
			break;
		//case down: transpose and flip board, move left and then transpose and flip
		case 3:	transpose();
				horizontalFlip();	
				flag = moveDir(operation);
				horizontalFlip();
				transpose();
				printf("down");
			break;
		default:		flag = 0;
	}
	printf(" move done. ");
	if (flag && currentBoard.numEmptyLocations) {
		printf("Random tile added.\n");
		generateRandomBlock();
	}
	else{
		printf("No change in board state. Hence, no random tile added.\n");
	}
}

// get Tile value at position specified
int getPositionValue(int i, int j, int print){
	if(i<0 || i>=N || j<0 || j>=N){
		if(print) printf("2048> There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
		return -1;
	}
	if(currentBoard.board[i][j]){
		if(print) printf("The value at position %d,%d is: %d\n", i+1, j+1, currentBoard.board[i][j]);
	}
	else{
		if(print) printf("2048> The tile is empty, i.e., value is 0.\n");
	}
	if(print){
		fprintf(stderr, "%d\n", currentBoard.board[i][j]);
	}
	return currentBoard.board[i][j];
}

//Assign value to Tile at position i,j
int setPosition(int val, int i, int j, int print){
	if(i<0 || i>=N || j<0 || j>=N){
		printf("2048> There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
		return 1;
	}
	if(val==0){
		if(currentBoard.board[i][j]){
			currentBoard.numEmptyLocations++;
			currentBoard.board[i][j]=0;
			for(int k=0; k<currentBoard.numVariables[i][j]; k++){
				for(int l=0; l<currentBoard.totalNumVariables; l++){
					if(currentBoard.variablesUsed[l]==currentBoard.variables[i][j][k]){
						free(currentBoard.variablesUsed[l]);
						currentBoard.variablesUsed[l]=NULL;
					}
				}
				currentBoard.variables[i][j][k]=NULL;
			}
			currentBoard.numVariables[i][j]=0;
			int k=0, l=0;
			while(l<currentBoard.totalNumVariables){
				if(currentBoard.variablesUsed[l]){
					currentBoard.variablesUsed[k++]= currentBoard.variablesUsed[l];
				}
				l++;
			}
			currentBoard.totalNumVariables=k;
		}
	}
	else if(val<0){
		printf("2048> Assignment not possible.\n");
	}
	else{
			if(!currentBoard.board[i][j]) currentBoard.numEmptyLocations--;
			currentBoard.board[i][j]=val;		
	}
	if(print){
		printf("2048> Thanks, value assigned.\n");
	}
	return 0;
}

//assign variable to tile at position i,j
int setVariable(char *variableName, int i, int j){
	for(int i=0; i<currentBoard.totalNumVariables; i++){
		if(strcmp(currentBoard.variablesUsed[i], variableName)==0){
			printf("2048> The variable name is already in use.\n");
			return 1;
		}
	}
	if(i<0 || i>=N || j<0 || j>=N){
		printf("2048> There is no tile like that. The tile co-ordinates must be in the range 1,2,3,4.\n");
		return 1;
	}
	else if(currentBoard.board[i][j]==0){
		printf("2048> %d,%d is an empty tile. Variable can't be assigned to an empty tile.\n", i+1, j+1);
		return 1;
	}
	currentBoard.variablesUsed[currentBoard.totalNumVariables]= (char *)malloc(200*sizeof(char));
	strcpy(currentBoard.variablesUsed[currentBoard.totalNumVariables], variableName);
	currentBoard.variables[i][j][currentBoard.numVariables[i][j]]= currentBoard.variablesUsed[currentBoard.totalNumVariables];
	currentBoard.numVariables[i][j]++;
	currentBoard.totalNumVariables++;
	printf("2048> Thanks, naming done.\n");
	return 0;
}

//destructor to free memory
void destructor(){
	for(int i=0; i<currentBoard.totalNumVariables; i++){
		free(currentBoard.variablesUsed[i]);
	}
} 
