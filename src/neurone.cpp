#include "neurone.hpp"

Neurone::Neurone(bool e, double p, bool r)
:excit(e), pot(p), refract(r)  {
	buffer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	courant = c;
}

Neurone::Neurone(Neurone const& n)
:excit(n.getType()), pot(n.getPot()), refract(n.getRefract()) {
		buffer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		courant = c;
}

bool Neurone::update(double t_rep, bool poiss) {
	double t(0.0);
	bool spike(false);
	
do {
	if(pot >= v_th){
		addSpike(t);
        pot = 0;
        refract = true;
        spike = true;
    }else{
		refract = false;
        pot = pot_calc(poiss);
        spike = false;
    }
    set_buffer();
    t += h;
    
} while(t_rep > t);

return spike;
	
}

double Neurone::pot_calc(bool poisson) {
    if (poisson) {
		//Calculation of the potential along brunel course
        return ((c1 * pot) + (courant * R * c2) + buffer.front() + Poisson());
        } else {
		return ((c1 * pot) + (courant * R * c2) + buffer.front());
		}
}


void Neurone::receive(double j_) {
	buffer[(D / h) - 1] += j_;
}

double Neurone::getPot() const {
	return pot;
}

void Neurone::setPot(double p) {
	pot = p;
}

bool Neurone::getType() const {
	return excit;
}

void Neurone::setCourant(double i) {
	courant = i;
}

vector<double> Neurone::getSpikes(){
	return t_spikes;
}

void Neurone::addSpike(double v) {
	t_spikes.push_back(v);
}

void Neurone::setRefract(bool b) {
	refract = b;
}

bool Neurone::getRefract() const {
	return refract;
}

void Neurone::set_buffer(){
	//Set the buffer after one time step
    for(size_t i(0); i < (buffer.size() - 1); ++i){
       buffer[i] = buffer[i + 1];
    }
    
    buffer[buffer.size() - 1] = 0;
}


size_t Neurone::getSize() {
	return t_spikes.size();
}

double Neurone::Poisson() {
	return (distr(gen) * Jp);
}


