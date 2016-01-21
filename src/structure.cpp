#include "structure.hpp"
#include <iostream>

/*
 * Génère un noeud de type Conc
 */
Conc* GenConc(Node* pleft, Node* pright) {
	Conc * pconc = new Conc;
	pconc->left = pleft;
	pconc->right = pright;
	return pconc;
}

/*
 * Génère un noeud de type Union
 */
Union* GenUnion(Node* pleft, Node* pright) {
	Union * punion = new Union;
	punion->left = pleft;
	punion->right = pright;
	return punion;
}

/*
 * Génère un noeud de type Star
 */
Star * GenStar(Node* ptr) {
	Star * pstar = new Star;
	pstar->Star_e = ptr;
	return pstar;
}

/*
 * Génère un noeud de type UN
 */
Un * GenUN(Node* ptr) {
	Un * pun = new Un;
	pun->Un_e = ptr;
	return pun;
}

/*
 * Génère un noeud de type Atom
 */
Atom* GenAtom(int code, int action, ATOMTYPE type) {
	Atom * patom = new Atom;
	patom->code = code;
	patom->action = action;
	patom->AType = type;
	return patom;
}


int main(){

	
	return 0;
}


