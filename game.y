%{
#include <stdio.h>
#include <string.h>
#include "g2048.h"
int yyerror(char const *s);
extern int yylex(void);
%}


%union{
	char text[200];
	int val;
}

%token ASSIGN TO COMMA VALUE IN VAR IS NEWLINE END OTHER
%token<text> VARIABLE
%token<val> NUMBER OPERATION DIRECTION

%type<val> QUERYWITHOUTEOL

%define parse.error verbose

%%

RULE : 	 {printf("\n2048> Thanks for playing!\n"); return -2;} //Expression for End of File (Ctrl+D case)
		//Valid commands expressions
		| MOVES
 		| ASSIGNMENT
 		| NAMING 
 		| QUERY
 		//Error Handling expressions
 		| NEWLINE {printf("2048> You need to enter some command.\n"); return 1;}
 		| WITHOUTEOL NEWLINE {printf("2048> You need to end a command with a full-stop.\n"); return 1;}
 		| VAR KEYWORD IS NUMBER COMMA NUMBER END NEWLINE {printf("2048> A keyword cannot be a variable name.\n"); return 1;}
 		| VARINCORRECT NEWLINE {printf("2048> Variable name can only contain alphabets.\n"); return 1;}
 		| error NEWLINE {return 1;}

//Valid Move expressions
MOVES: OPERATION DIRECTION END NEWLINE {move($1, $2);
										return 0;
										}
ASSIGNMENT: ASSIGN NUMBER TO NUMBER COMMA NUMBER END NEWLINE {
																int x=setPosition($2, ($4)-1, ($6)-1, 1);
																return x;
															}
			| ASSIGN QUERYWITHOUTEOL TO NUMBER COMMA NUMBER END NEWLINE {
																			int x=setPosition($2, ($4)-1, ($6)-1, 1);
																			return x;
																		}
NAMING: VAR VARIABLE IS NUMBER COMMA NUMBER END NEWLINE {
															int x=setVariable($2, ($4)-1, ($6)-1);
															if(x==0) return -1; 
															return 1;
														}
QUERY: VALUE IN NUMBER COMMA NUMBER END NEWLINE {
													int x= getPositionValue(($3)-1, ($5)-1, 1);
													if(x==-1) return 1;
													return -2;
												}


//For nested assign expressions
QUERYWITHOUTEOL: VALUE IN NUMBER COMMA NUMBER {
													$$= getPositionValue(($3)-1, ($5)-1, 0);
											}

//All keywords expression
KEYWORD: OPERATION | DIRECTION | ASSIGN | TO | VAR | IS | VALUE | IN

//ALl commands without full-stop expressions.
WITHOUTEOL: OPERATION DIRECTION
			| ASSIGN NUMBER TO NUMBER COMMA NUMBER
			| VAR VARIABLE IS NUMBER COMMA NUMBER
			| VALUE IN NUMBER COMMA NUMBER

//Error expression of naming command with variable name that contains numbers or special characters.
VARINCORRECT: VAR OTHER IS NUMBER COMMA NUMBER END

%%

//Standard error message
int yyerror(char const *s){
	char sCopy[200];
	strcpy(sCopy, s);
	char *token;
	token = strtok(sCopy, " ");
	for(int i=0; i<3; i++){
		token= strtok(NULL, " ");
	}
	token= strtok(token,",");
	if(strcmp(token, "VARIABLE")==0){
		printf("2048> Syntax error.\n");
	}
	else printf("2048> Syntax error. Unexpected %s in command.\n", token);
	return 0;	
}
