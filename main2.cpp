#include <iostream>
#include "neurone.hpp"
#include "network.hpp"
#include "Constant.hpp"


int main() {
		
	Network n;
    
    //Creation of an ofstream to write in Donnée.txt infos to build the graphs
    string nom("Donnée.txt");
	ofstream infile;
	infile.open(nom);
	
	//checking the opening
	if (infile.fail()) {
		cerr << "Error opening file!";
		exit(1);
	}
    
    n.update(infile);
	infile.close();
	n.affich_sp();
	
	return 0;
}
