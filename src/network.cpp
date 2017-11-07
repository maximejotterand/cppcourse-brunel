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
			Neurone n;
			add_neuron(new Neurone(n));
		}
		
		initialisation_connection();
	
}

Network::~Network() {
	destr();
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
			assert(res[i] != nullptr);
			if(res[i] != nullptr) {
				
				//update the buffer of the neuron i
				//neuron i has m post neurons, so possibles excitations/inhibitions
				for(size_t m(0); m < matrice_connections[i].size(); ++m) {
					
					//another seg fault checking
					if (res[matrice_connections[i][m]] != nullptr) {
						//neuron i receive a signal if the post neuron spike only
					if ((*res[matrice_connections[i][m]]).getRefract()) {
						
						//receive either a excitory courant or a inhibitory
						if (m < Ce) {
							(*res[i]).receive(J);
						} else if (m >= Ce) {
							(*res[i]).receive(Ji);
						}
						
					}
				}
			}
			
			
					//update of all neurons
					spike = (*res[i]).update();
				if (spike) {
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
		//The first part of the array are the excitatory post neuron the last the inhibitory
		
		array<int, (Ce + Ci)> a;
		for (size_t i(0); i < Ce; ++i) {
			uniform_int_distribution<int> distribution(0, Ne - 1);
			int r = distribution(generator);
			a[i] = r;
		}
		
		for (size_t j(Ce); j < (Ce + Ci); ++j) {
			uniform_int_distribution<int> distribution(Ne, Ne + Ni);
			int r = distribution(generator);
			a[j] = r;
		}
		
		matrice_connections.push_back(a);
	
	}
	cout << "Network connected" << endl;
}

