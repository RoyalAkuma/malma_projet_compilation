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
	return p_union;
}
Star * GStar(Node* ptr) {
	Star * p_star = new Star;
	p_star->star = ptr;
	return p_star;
}
Un * GUN(Node* ptr) {
	Un * nun = new Un;
	nun->un = ptr;
	return nun;
}
Atom * GAtom(int code, int action, ATOMETYPES type) {
	Atom * patom = new Atom;
	patom->code = code;
	patom->action = action;
	patom->type = type;
	return patom;
}

grammaire * Gforet(){
	grammaire * g = new grammaire[5]; 
	// 78 = 'N' ; 62 = '>' ; 69 = 'E' ; 44 = ',' ; 59 =';' 46 = '.' ; 70 = 'F'
	g[0] = GConc(
				GStar(
					GConc(
						GConc(
							GConc(
								GAtom(78,0,NonTerminal),
								GAtom(62,0,Terminal)
							),
							GAtom(static_cast<int>('E'),0,NonTerminal)
						),
						GAtom(44,0,Terminal)
					)
				),
				GAtom(59,0,Terminal)
			);
	g[1] = GAtom(0,0,Terminal); // IDNTER 0 et ELTER 1
	g[2] = GConc(GAtom(84,0,NonTerminal),GStar(GConc(GAtom(43,0,Terminal),GAtom(84,0,NonTerminal))));
	g[3] = GConc(GAtom(70,0,NonTerminal),GStar(GConc(GAtom(46,0,Terminal),GAtom(70,0,NonTerminal))));
	g[4] = GUnion(GUnion(GUnion(
							GUnion(GAtom(0,0,Terminal),GAtom(1,0,Terminal)
							),
							GConc(
								GAtom(static_cast<int>('('),0,Terminal),
								GConc(GAtom(static_cast<int>('E'),0,NonTerminal),GAtom(static_cast<int>(')'),0,Terminal))
								)
						),
						GConc(
								GAtom(static_cast<int>('['),0,Terminal),
								GConc(GAtom(static_cast<int>('E'),0,NonTerminal),GAtom(static_cast<int>(']'),0,Terminal))
								)
				),
				GConc(
					GAtom(1000,0,Terminal),
					GConc(GAtom(static_cast<int>('E'),0,NonTerminal),GAtom(1001,0,Terminal))
				)
			); 
	/** 
	 * 1000 = '(/'
	 * 1001 = '/)'
	 */
	
	return g;
}

int main(){
	
	
	return 0;
}


