#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <fstream>
#include <string>
#include "neurone.hpp"
#include "Constant.hpp"

#ifndef NETWORK_H
#define NETWORK_H

using namespace std;


class Network {
	private :
	//! Vector containing the neurons of the network (pointers on all the neurons)
	vector<Neurone*> res;
	//! Vector containing the number of times per steps
	vector<int> nb_sp;
	//! Matrix giving the index pre-neurons connected to the neuron
	vector<array<int, (Ce + Ci)>> matrice_connections;
	
	public :
	//! Network constructor
	//! Use initialisation_connections() to create all the connection of the neurons
	Network();
	//! Network destructor
	~Network();
	/*! Add a neuron :
	 * @Param the address of a neuron n
	 * @brief Add a neuron to our network (in res)
	 */
	void add_neuron(Neurone* n);
	//! Destruction of the network, called in the destructor
	void destr();
	/*! Update the network :
	 * @Param in is the string(the infos) we will write in Donnée.txt
	 * @brief Update every neurons of the network and those who are depending on others
	 */
	void update(ofstream& in);
	//! Print the info of our network
	void affich_sp();
	//! Initialise all the connections in our network
	void initialisation_connection();
	
};



#endif
