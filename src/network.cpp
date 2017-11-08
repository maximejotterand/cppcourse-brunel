#include "network.hpp"

void Network::add_neuron(Neurone* n) {
	res.push_back(n);
}

void Network::destr() {
	assert(res.size() != 0);
	if (res.size() != 0) {
	for (size_t i(0); i < res.size(); ++i) {
		res[i] = nullptr;
		delete res[i];
	}
}
}

Network::Network()
{
		for (size_t i(0); i < N; ++i) {
			if (i < Ne) {
				Neurone n();
				add_neuron(new Neurone(n));
			} else {
				Neurone n(false);
				add_neuron(new Neurone(n));
			}
		}
		
		initialisation_connection();
	
}

Network::~Network() {
	destr();
}


void Network::update() {
	
	double simtime = 0.0;
    size_t time;
    time = 0;
    do {
	
		bool spike(false);
		nb_sp.push_back(0);
		
		//iteration on all the neuron
		for (size_t i(0); i < res.size(); ++i) {
			spike = false;
			
			//quick check to avoid seg fault (access a function of a nullptr)
			if(res[i] != nullptr) {
				//Check if the neuron spike and so give excitation or inhibition to the his post connections
				if ((*res[i]).update()) {
					for (int k(0); k < matrice_connections[i].size(); ++k) {
						if (res[matrice_connections[i][k]] != nullptr) {
							// Send the appropriate current
							if ((*res[i]).getType() == true) {
								(*res[matrice_connections[i][k]]).receive(J);
							} else {
								(*res[matrice_connections[i][k]]).receive(Ji);
							}
					}
						
					}
					++nb_sp[time - 1];
				}
}
}


time += 1;
simtime += h;
} while(simtime < t_stop);

}

void Network::update(ofstream& c) {
	
	double simtime = 0.0;
    size_t time;
    time = 0;
    do {
	
		bool spike(false);
		nb_sp.push_back(0);
		
		//iteration on all the neuron
		for (size_t i(0); i < res.size(); ++i) {
			spike = false;
			
			//quick check to avoid seg fault (access a function of a nullptr)
			if(res[i] != nullptr) {
				//Check if the neuron spike and so give excitation or inhibition to the his post connections
				if ((*res[i]).update()) {
					for (int k(0); k < matrice_connections[i].size(); ++k) {
						if (res[matrice_connections[i][k]] != nullptr) {
						if ((*res[i]).getType() == true) {
							(*res[matrice_connections[i][k]]).receive(J);
						} else {
							(*res[matrice_connections[i][k]]).receive(Ji);
						}
					}
						
					}
					
					//write in Donnée.txt the info of the first 30 neurons during the all experiment
					if (i < 50) {
					c << time / 10.0 << '\t' << i << '\n';
					}
					++nb_sp[time - 1];
					
				}
}
}


time += 1;
simtime += h;
} while(simtime < t_stop);

}


void Network::affich_sp() {
	cout << "Printing the number of spikes per timestep : " << endl;
	for (size_t k(0); k < nb_sp.size(); ++k) {
		cout << nb_sp[k] << '\n';
	}
}

void Network::initialisation_connection() {
	cout << "Initialisation of the network connections " << endl;
	std::default_random_engine generator;

	for (size_t n(0); n < res.size(); ++n) {
		array<int, (Ce + Ci)> a;
		for (int i(0); i < (Ce + Ci); ++i) {
			uniform_int_distribution<int> distribution(0, N);
			int r = distribution(generator);
			a[i] = r;
		}
		
		matrice_connections.push_back(a);
	
	}
	cout << "Network connected" << endl;
}

