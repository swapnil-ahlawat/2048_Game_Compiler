all: game

game: driver.c lex.yy.c game.tab.c game.tab.h g2048.o
	gcc -o game driver.c g2048.o game.tab.c lex.yy.c

game.tab.c game.tab.h:	game.y
	bison -v -d game.y

lex.yy.c: game.l game.tab.h
	flex game.l

g2048.o: g2048.c g2048.h
	gcc -c g2048.c

clean:
	rm game game.tab.c lex.yy.c game.tab.h game.output g2048.o