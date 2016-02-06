#include "structure.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
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

std::string profon = "";
//FAIRE L'ANALYSE SUR UNE STRUCTURE !!
bool Analyse(Node * node){
	profon += "-";
	std::cout <<profon << "BEGINANALYSE:"<< scanner->scan_token << "-"<< scanner->scan_type  << "-" << scanner->scan_code<< std::endl; 
	bool analyse = false;

	Conc * tmp_conc =  static_cast<Conc*>(node);
	Star * tmp_star =  static_cast<Star*>(node);
	Union * tmp_union =  static_cast<Union*>(node);
	Un * tmp_un =  static_cast<Un*>(node);
	Atom * tmp_atom =  static_cast<Atom*>(node);
	switch(node->classname){
		case CONC:
			//std::cout<<"CONC:(";
			if(Analyse(tmp_conc->left)){
				analyse = Analyse(tmp_conc->right);
			}else{
				analyse = false;
			}
			//std::cout<<")";
			break;
		case UNION:
			//std::cout<<"UNION:(";
			if(Analyse(tmp_union->left)){
				analyse = true;
			}else{
				analyse = Analyse(tmp_union->right);
			}
			//std::cout<<")";
			break;
		case STAR:
			//std::cout<<"STAR:";
			analyse = true;
			while(Analyse(tmp_star->star)){}
			break;
		case UN:
			//std::cout<<"UN:(";
			analyse=true;
			if(Analyse(tmp_un->un)){}
			//std::cout<<")";
			break;
		case ATOM:
			std::cout << profon << "ATOM";
			//std::cout<<"ATOM:(";
			switch(tmp_atom->type){
				case Terminal:
					// AVOIR FAIT SCAN AVANT L'APPEL DE ANALYSE

					if(tmp_atom->code == scanner->scan_code){
						std::cout << tmp_atom->code;
						analyse=true;
						if(tmp_atom->action != 0){
							DoAction(tmp_atom->action);
						}
						scan(); //ON CONTINUE SUR LA TETE DE LECTURE
					}
					break;
				case NonTerminal:
			//		std::cout << "i_code:" << tmp_atom->i_code << ":";
					if(Analyse(arbre->g[tmp_atom->i_code])){
						analyse = true;
						if(tmp_atom->action != 0){
								DoAction(tmp_atom->action);
								
						}
						scan(); //ON CONTINUE SUR LA TETE DE LECTURE
					}
					break;
				default:
					std::cout<<"---PROBLEM---";		
					analyse=false;
			}

			//std::cout<<")";
			break;
		default:
			std::cout<<"DEFAULT=PROBLEM WHEN ANALYSE";
			analyse = false;
	}
	if(analyse)
		std::cout<<profon<<"ANALYSE=true"<<std::endl;
	else
		std::cout<<profon<<"ANALYSE=false"<<std::endl;
	profon = profon.substr(0, profon.size()-1);;
	return analyse;
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void readFile(std::string path){
		std::cout << "-> BEGIN OF READING FILE..." << std::endl;
		std::string line;
		std::ifstream myfile (path.c_str(), std::ios::in);
		if (myfile)
		{
			int i=0,j=0;
			while ( getline (myfile,line))
			{
				std::vector<std::string> tab_line = split(line,' ');
				for(int z=0;z<tab_line.size();z++)
					std::cout << " | " << tab_line[z];
				std::cout << std::endl;
				scanner->grammar_split.push_back(tab_line);
			}
			myfile.close();
		}else std::cout << "FICHIER IMPOSSIBLE A OUVRIR";
		std::cout << "-> END OF READING FILE..." << std::endl;
}

void parseToken(std::string token){
	//std::cout << "------> PARSING TOKEN : " << token << std::endl;
	std::vector<std::string> parse_token_quote = split(token,((char)39));
	// HERE IS A TERMINAL TOKEN BECAUSE SURROUNDED BY QUOTE  
	if(parse_token_quote.size()>=2){
		//CHECK IF THERE IS AN ACTION (SURROUNDED BY A #)
		std::vector<std::string> parse_token_action = split(parse_token_quote[1],((char)35));
		if(parse_token_action.size()==2){
			scanner->scan_action = atoi(parse_token_action[1].c_str());
			scanner->scan_token = parse_token_action[0];
		}else{
			scanner->scan_token= parse_token_action[0];
			scanner->scan_action=0;
		}
		scanner->scan_type=Terminal;
		scanner->scan_code = "ELTER";
		/*for(int i=0;i<parse_token_action.size();i++){
			std::cout << "|--> ACTION PARSING  : " << parse_token_action[i] << std::endl;	
		}*/
	}else if(parse_token_quote.size()==1){
		scanner->scan_token = parse_token_quote[0];
		scanner->scan_code = "IDNTER";
		scanner->scan_type=NonTerminal;
		scanner->scan_action=0;
	}else{
		std::cout << "NOT WELL-FORMATTED" << std::endl;
	}

	for(int i=0;i<parse_token_quote.size();i++){
		std::cout << "\n|--> QUOTE PARSING  : " << parse_token_quote[i] << std::endl;	
	}
	std::cout << "==CODE:" << scanner->scan_code <<std::endl;
	std::cout << "==TYPE:" << scanner->scan_type <<std::endl;
	std::cout << "==TOKEN:" << scanner->scan_token <<std::endl;
	std::cout << "==ACTION:"<< scanner->scan_action <<std::endl;
	std::cout << "==profon: "<< profon.size() << std::endl;
	

	
	
}
void scan(void){
	//std::cout << "row:" << scanner->scan_position_row << " col:" << scanner->scan_position_col;
	bool inTab = (scanner->scan_position_row < scanner->grammar_split.size() && scanner->scan_position_col < scanner->grammar_split[scanner->scan_position_row].size() )?true:false;	
	if(inTab){
		scanner->scan_token = scanner->grammar_split[scanner->scan_position_row][scanner->scan_position_col];
		//std::cout << "-> SCAN NEXT TOKEN : " << scanner->scan_token<< std::endl;
		//PARSE THE TOKEN TO HAVE ACTION_CODE AND KNOW TERMINAL
		parseToken(scanner->scan_token);
		scanner->grammar_split[scanner->scan_position_row][scanner->scan_position_col].erase(0);
		scanner->scan_position_col++;

		if(scanner->scan_position_col == scanner->grammar_split[scanner->scan_position_row].size()){
			scanner->scan_position_row++;
			scanner->scan_position_col = 0;
		}
	}
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
	readFile("grammaire.txt");
	//FIRSTLY WE HAVE TO READ THE FIRST TOKEN;
	//for(int i =0;i<10;i++){
	//	std::cout << std::endl;
		scan();

	//}
	//NOW WE CAN ANALYSE THE GRAMMAR TO KNOW HOW IT'S WELL-FORMATTED
	bool analyse = Analyse(arbre->g[0]);
	std::cout << "[GRAMMAR STATUS] : " << analyse << std::endl;


	
	return 0;
}


