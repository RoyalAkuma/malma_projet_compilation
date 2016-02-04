#include "structure.hpp"
#include <iostream>
#include <string>
#include <fstream>
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
Atom * GAtom(std::string code, int action, ATOMETYPES type,int i_code) {
	Atom * patom = new Atom;
	patom->code = code;
	patom->action = action;
	patom->type = type;
	patom->i_code = i_code;
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
								GAtom("N",0,NonTerminal,1),
								GAtom("->",0,Terminal,-1)
							),
							GAtom("E",0,NonTerminal,2)
						),
						GAtom(",",0,Terminal,-1)
					)
				),
				GAtom(";",0,Terminal,-1)
			);
	g[1] = GAtom("IDNTER",0,Terminal,-1); // IDNTER 0 et ELTER 1
	g[2] = GConc(GAtom("T",0,NonTerminal,3),GStar(GConc(GAtom("+",0,Terminal,-1),GAtom("T",0,NonTerminal,3))));
	g[3] = GConc(GAtom("F",0,NonTerminal,4),GStar(GConc(GAtom(".",0,Terminal,-1),GAtom("F",0,NonTerminal,4))));
	g[4] = GUnion(GUnion(GUnion(
							GUnion(GAtom("IDNTER",0,Terminal,-1),GAtom("ELTER",0,Terminal,-1)
							),
							GConc(
								GAtom("(",0,Terminal,-1),
								GConc(GAtom("E",0,NonTerminal,2),GAtom(")",0,Terminal,-1))
								)
						),
						GConc(
								GAtom("[",0,Terminal,-1),
								GConc(GAtom("E",0,NonTerminal,2),GAtom("]",0,Terminal,-1))
								)
				),
				GConc(
					GAtom("(/",0,Terminal,-1),
					GConc(GAtom("E",0,NonTerminal,2),GAtom("/)",0,Terminal,-1))
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

bool Analyse(Node * node){
	bool analyse;
	Conc * tmp_conc =  static_cast<Conc*>(node);
	Star * tmp_star =  static_cast<Star*>(node);
	Union * tmp_union =  static_cast<Union*>(node);
	Un * tmp_un =  static_cast<Un*>(node);
	Atom * tmp_atom =  static_cast<Atom*>(node);
	switch(node->classname){
		case CONC:
			if(Analyse(tmp_conc->left)){
				analyse = Analyse(tmp_conc->right);
			}else{
				analyse = false;
			}
			break;
		case UNION:
			if(Analyse(tmp_union->left)){
				analyse = true;
			}else{
				analyse = Analyse(tmp_union->right);
			}
			break;
		case STAR:
			analyse = true;
			while(Analyse(tmp_star->star)){}
			break;
		case UN:
			analyse=true;
			if(Analyse(tmp_un->un)){}
			break;
		case ATOM:
			switch(tmp_atom->type){
				case Terminal:
					// AVOIR FAIT SCAN AVANT L'APPEL DE ANALYSE
					if(tmp_atom->code == scanner->scan_code){
						analyse=true;
						if(tmp_atom->action != 0){
								DoAction(tmp_atom->action);
						}
						scan(); //ON CONTINUE SUR LA TETE DE LECTURE
					}else{

					}
					break;
				case NonTerminal:
					if(Analyse(arbre->g[tmp_atom->i_code])){
						if(tmp_atom->action != 0){
								DoAction(tmp_atom->action);
								analyse = true;
						}else{
								analyse = false;
						}
						scan(); //ON CONTINUE SUR LA TETE DE LECTURE
					}else{

					}
					break;
				default:
					analyse=false;
			}
			break;
		default:
			analyse = false;
	}
	return analyse;
}

int countFile(std::string file){
		std::string path = file;
		std::string line;
		std::ifstream myfile (path.c_str(), std::ios::in);
		int count = 0;
		if(myfile){
				while (getline (myfile,line) )
				{
						count++;
				}
				myfile.close();
		}else std::cout << "FICHIER IMPOSSIBLE A OUVRIR"; 
			
		return count;
}

void scan(){
		std::cout << "-> SCAN FILE IN PROGRESS... " << std::endl;
		std::string path = "grammaire.txt";
		std::string line;
		std::ifstream myfile (path.c_str(), std::ios::in);
		if (myfile)
		{
			int i=0,j=0;
			int count = countFile(path);
			while ( getline (myfile,line) && i < count)
			{
				if(scanner->scan_position_row == i){
					//std::cout << line << '\n';
					std::string delimiter = " ";

					size_t pos = 0;
					std::string token;
					while ((pos = line.find(delimiter)) != std::string::npos && j < line.size()) {
						if(scanner->scan_position_col == j){
							token = line.substr(0, pos);
							std::cout << "->" <<token << std::endl;
							/* ON REMPLIT LA STRUCTURE DE STOCKAGE EXTERNE */
							scanner->scan_token = token;
							line.erase(0, pos + delimiter.length());
						}
						
						//if(token != " ")
							j++;
					}
				}
				i++;
			}
			myfile.close();
		}else std::cout << "FICHIER IMPOSSIBLE A OUVRIR";
		
		scanner->scan_position_col++;
		if(scanner->scan_position_col == line.size()-1)
			scanner->scan_position_row++;
		
}

void DoAction(int code_action){
		std::cout << "I DO AN ACTION" << std::endl;
}

int main(){
	arbre = new Arbre;
	arbre->g = Gforet();
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(arbre->g[0],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(arbre->g[1],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(arbre->g[2],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(arbre->g[3],0);
	std::cout<<" ------------------------------------ " << std::endl;
	printGrammaire(arbre->g[4],0);
	std::cout<<" ------------------------------------ " << std::endl;
	
	//INITIALISATION DU SCAN
	scanner =  new scan_struct;
	scanner->scan_position_col=0;
	scanner->scan_position_row=0;
	//READ FILE;
	scan();
	std::cout<< "rows:" << scanner->scan_position_row; 
	std::cout << " cols:" << scanner->scan_position_col;
	scan();
	std::cout<< "rows:" << scanner->scan_position_row; 
	std::cout << " cols:" << scanner->scan_position_col;
	scan();
	std::cout<< "rows:" << scanner->scan_position_row; 
	std::cout << " cols:" << scanner->scan_position_col;
	
	return 0;
}


