#include "structure.hpp"
#include <iostream>
#include <string>

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
Atom * GAtom(std::string code, int action, ATOMETYPES type) {
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
								GAtom("N",0,NonTerminal),
								GAtom("->",0,Terminal)
							),
							GAtom("E",0,NonTerminal)
						),
						GAtom(",",0,Terminal)
					)
				),
				GAtom(";",0,Terminal)
			);
	g[1] = GAtom("IDNTER",0,Terminal); // IDNTER 0 et ELTER 1
	g[2] = GConc(GAtom("T",0,NonTerminal),GStar(GConc(GAtom("+",0,Terminal),GAtom("T",0,NonTerminal))));
	g[3] = GConc(GAtom("F",0,NonTerminal),GStar(GConc(GAtom(".",0,Terminal),GAtom("F",0,NonTerminal))));
	g[4] = GUnion(GUnion(GUnion(
							GUnion(GAtom("IDNTER",0,Terminal),GAtom("ELTER",0,Terminal)
							),
							GConc(
								GAtom("(",0,Terminal),
								GConc(GAtom("E",0,NonTerminal),GAtom(")",0,Terminal))
								)
						),
						GConc(
								GAtom("[",0,Terminal),
								GConc(GAtom("E",0,NonTerminal),GAtom("]",0,Terminal))
								)
				),
				GConc(
					GAtom("(/",0,Terminal),
					GConc(GAtom("E",0,NonTerminal),GAtom("/)",0,Terminal))
				)
			); 
	
	return g;
}

void printGrammaire(Node * ptr,int prof){
	int va = 1;
	prof++;
	for(int i = 0;i<prof;i++){
		std::cout << "---";
	}
	Conc * tmp_conc =  static_cast<Conc*>(ptr);
	Star * tmp_star =  static_cast<Star*>(ptr);
	Union * tmp_union =  static_cast<Union*>(ptr);
	Un * tmp_un =  static_cast<Un*>(ptr);
	Atom * tmp_atom =  static_cast<Atom*>(ptr);
	switch(ptr->classname){
			case CONC :
				std::cout << ">CONC" << std::endl;
				
				printGrammaire(tmp_conc->left,prof);
				printGrammaire(tmp_conc->right,prof);
				break;
			case STAR :
				
				std::cout << ">STAR" << std::endl;
				printGrammaire(tmp_star->star,prof);
				break;
			case UNION :
				
				std::cout << ">UNION" << std::endl;
				printGrammaire(tmp_union->left,prof);
				printGrammaire(tmp_union->right,prof);
				break;
			case ATOM :
				std::cout << tmp_atom->code << std::endl;
				break;
			case UN :
				
				std::cout << ">UN" << std::endl;
				printGrammaire(tmp_un->un,prof);
				break;
			default :
				std::cout << "PROBLEM" << std::endl;
	}
}

int main(){
	grammaire * g = Gforet();
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(g[0],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(g[1],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(g[2],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(g[3],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(g[4],0);
	std::cout<<" ------------------------------------ " << std::endl;
	return 0;
}


