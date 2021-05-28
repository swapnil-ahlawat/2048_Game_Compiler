#include <stdio.h>
#include <time.h>
#include "game.tab.h"
#include <signal.h>
#include <ctype.h>
#include "g2048.h"
extern FILE* yyin;

BoardState currentBoard; //Board State structure
char interpretation='C'; //Standard Interpretation to follow

int main(){
	srand(time(NULL));
	yyin=stdin;

	printf("2048> Hi, I am the 2048-game Engine.\n");
	
	//Choose interpretation to follow
	printf("2048> Two interpretation of SUBTRACT operation in the game are possible:\n\t\"SUBTRACT LEFT\" ON [4,2,2,4] generates:\n");
	printf("\t A.[4,0,4,0]\t\tB.[4,4,0,0]\n");
	printf("Please choose the implementation you want to follow (A/B):");
	int count=0;
	while(count!=1 || (count==1 && interpretation!='A' && interpretation!='B')){
		count=0;
		char y;
		while(scanf("%c", &y) && y!='\n'){
			interpretation=toupper(y);
			count++;
		}
		if(count!=1 || (count==1 && interpretation!='A' && interpretation!='B')){
			printf("Invalid Entry. Valid Options are A or B. Please enter again:");
		}

	}
	
	initialise();
	setPosition((1+(rand()%2))*2, (rand()%4), (rand()%4), 0);
	printf("2048> The start state is:\n");
	printBoard();
	printStderr();
	do{
		printf("2048> Please type a command.\n");
		int x=1;
		
		//looping parser in case of errors.
		while(x==1 || x==2){
			printf("----> ");
			x= yyparse();
			//printing error in stderr.
			if(x==1 || x==2){
				fprintf(stderr, "-1\n");
			}
		}

		//print current board state.
		if(x>=0){
			printf("2048> The current state is:\n");
			printBoard();
		}

		//print current board state in stderr.
		if(x!=-2){
			printStderr();
		}
	}while(!feof(yyin));

	//free used memory
	destructor();
	
	return 0;
}
