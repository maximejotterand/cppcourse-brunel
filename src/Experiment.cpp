#include "Experiment.hpp"

Experiment::Experiment(string n)
: nom(n)
{
	cout << "If you want to change the experiment, you will have to change the constants in Constant.hpp. The default experiment is C (g = 5 and eta = 2)." << endl;
	
    cout << "Do you want to write the results of the time of spikes of the first 50 neurons in a file (graphs/Donnée.txt) ? (y / n / q to quit)" << endl;
    
    do {
		cin >> answer;
	} while(cin.fail());

	if (answer == 'y') {
		Network n;
		//Creation of an ofstream to write in Donnée.txt infos to build the graphs
		ofstream infile;
		infile.open(nom);
	
		//checking the opening
		if (infile.fail()) {
			cerr << "Error opening file!";
			exit(1);
		}
    
		cout << "Starting the experiment." << endl;
		n.update(infile);
		//closing the file
		infile.close();
		
		cout << "Do you want to print the number of spikes ? (y / n)" << endl;
		cin >> answer2;
		if (answer2 == 'y') {
			n.affich_sp();
		}
	} else if (answer == 'n') {
		Network n;
		n.update();
		cout << "Do you want to print the number of spikes ? (y / n)" << endl;
		cin >> answer2;
		if (answer2 == 'y') {
			n.affich_sp();
		}
	} else if (answer == 'q') {}
}
