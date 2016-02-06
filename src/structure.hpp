#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <iostream>
#include <string>

#include <vector>
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
	int i_code;
	int action;
	ATOMETYPES type;
	_Atom(){
			classname = ATOM;
	}
} Atom;

typedef Node * grammaire;

typedef struct Arbre{
		grammaire * g;
		std::vector<Node *> gpl;
}Arbre;
extern Arbre * arbre = NULL;

typedef struct _scan_struct{
	std::vector< std::vector<std::string> > grammar_split;
	int scan_position_row,scan_position_col;
	std::string scan_code;
	int scan_action;
	ATOMETYPES scan_type;
	std::string scan_token;
}scan_struct;
extern scan_struct * scanner = NULL;

void parseToken(std::string);
void scan(void);
void readFile(std::string);
void DoAction(int);
bool Analyse(Node *);
void printGrammaire();
grammaire * Gforet(Node * ptr,int prof);
Atom * GAtom(std::string code, int action, ATOMETYPES type,int i_code);
Un * GUN(Node* ptr);
Star * GStar(Node* ptr);
Union* GUnion(Node* left, Node* right);
Conc* GConc(Node* left, Node* right);


#endif
