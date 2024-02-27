# Makefile for treeParser
treeParser	: tree.tab.o tree.o
		g++ -o $@ tree.tab.o tree.o

tree.o		: tree.c tree.tab.h
		g++ -c tree.c -std=c++11

tree.tab.o	: tree.tab.c tree.tab.h Node.h NodeStore.h
		g++ -c tree.tab.c -std=c++11

tree.c		: tree.lex
		flex -o $@ tree.lex

tree.tab.c	: tree.y
		bison -d tree.y --debug --verbose

tree.tab.h	: tree.y
		bison -d tree.y --debug --verbose

clean		:
		rm treeParser *.o tree.tab.h tree.tab.c *.output
