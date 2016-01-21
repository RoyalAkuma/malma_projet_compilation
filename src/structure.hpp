#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <iostream>

enum ATOMETYPES{
	Terminal,
	NonTerminal
};

enum OPERATIONS {
	CONC,UNION,STAR,UN,ATOM
};

typedef struct _Node { } Node;

typedef struct _Conc : public Node {
	Node * right, *left;
	~_Conc(){
		delete right;
		delete left;
	}
} Conc;
typedef struct _Union : public Node {
	Node * right, * left;
	~_Union(){
		delete right;
		delete left;
	}
} Union;
typedef struct _Star : public Node {
	Node * star;
	~_Star(){
		delete star;
	}
} Star;
typedef struct _Un : public Node {
	Node * un;
	~_Un(){
		delete un;
	}
} Un;

typedef struct _Atom : public Node{
	int code,action;
	ATOMETYPES type;
} Atom;

typedef Node * grammaire;


#endif
