#include "structure.hpp"
#include <iostream>

Conc* GConc(Node* left, Node* right) {
	Conc * conc = new Conc;
	conc->left = left;
	conc->right = right;
	return conc;
}
Union* GUnion(Node* left, Node* right) {
	Union * p_union = new Union;
	p_union->left = left;
	p_union->right = right;
	return punion;
}
Star * GStar(Node* ptr) {
	Star * pstar = new Star;
	p_star->star = ptr;
	return pstar;
}
Un * GUN(Node* ptr) {
	Un * pun = new Un;
	pun->un = ptr;
	return pun;
}
Atom* GAtom(int code, int action, ATOMETYPES type) {
	Atom * patom = new Atom;
	patom->code = code;
	patom->action = action;
	patom->AType = type;
	return patom;
}


int main(){

	
	return 0;
}


