#include <iostream>
#include <string>
#include "Constant.hpp"
#include "network.hpp"


#ifndef EXPERIMENT_H
#define EXPERIMENT_H

using namespace std;

class Experiment {
	private:
		//! Answer to conversation with the user
		char answer;
		//! Answer to conversation with the user
		char answer2;
		//! The name of the file for the results
		string nom;
	
	public:
		//! Build the experiment
		//! @Param n the name of the file for the results
		Experiment(string n = "../graphs/Donnée.txt");
	
};


#endif
