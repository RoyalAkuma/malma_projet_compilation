#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <iostream>
#include <string>
enum ATOMETYPES{
	Terminal,
	NonTerminal
};

enum OPERATIONS {
	CONC,UNION,STAR,UN,ATOM
};

typedef struct _Node {
		OPERATIONS classname;
} Node;

typedef struct _Conc :  Node {
	Node * right, *left;
	_Conc(){
			classname = CONC;
	}
	~_Conc(){
		delete right;
		delete left;
	}
} Conc;
typedef struct _Union :  Node {
	Node * right, * left;
	_Union(){
			classname = UNION;
	}
	~_Union(){
		delete right;
		delete left;
	}
} Union;
typedef struct _Star :  Node {
	_Star(){
			classname = STAR;
	}
	Node * star;
	~_Star(){
		delete star;
	}
} Star;
typedef struct _Un :  Node {
	Node * un;
	_Un(){
			classname = UN;
	}
	~_Un(){
		delete un;
	}
} Un;

typedef struct _Atom :  Node{
	std::string code;
	int action;
	ATOMETYPES type;
	_Atom(){
			classname = ATOM;
	}
} Atom;

typedef Node * grammaire;

void printGrammaire();
grammaire * Gforet(Node * ptr,int prof);
Atom * GAtom(std::string code, int action, ATOMETYPES type);
Un * GUN(Node* ptr);
Star * GStar(Node* ptr);
Union* GUnion(Node* left, Node* right);
Conc* GConc(Node* left, Node* right);


#endif
