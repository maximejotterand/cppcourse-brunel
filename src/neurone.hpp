#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <random>
#include "Constant.hpp"

#ifndef NEURONE_H
#define NEURONE_H

using namespace std;

	static random_device rd;
	static mt19937 gen(rd());
	static poisson_distribution<> distr((u_ext / 10));

class Neurone {
	private :
		//! Vector containing the time when the spike happened
		vector<double> t_spikes;
		//! The potential
		double pot;
		//! Bool giving if the neuron is refractory (true) or not (false)
		bool refract;
		//! The ring-buffer 
		array<double, 15> buffer;
		//! The current
		double courant;
		//! Bool determinating the nature of the post current of the neuron
		//! True means that it is excitatory
		bool excit;
		
		
	public :
		//! Constructor
		//! @Param e is the nature of the neuron (excitatory(true) or inhibitory)
		//! @Param p is the initial potential
		//! @Param r is the initial refractory booleen
		Neurone(bool e = true, double p = 0.0, bool r = false);
		//! Copy constructor
		//! @Param n is the constant reference to the neuron we want to copy
		Neurone(Neurone const& n);
		//! Getter potential
		double getPot() const;
		//! Setter potential
		void setPot(double p);
		//! Setter for the current
		void setCourant(double i);
		//! Getter of the nature of the neuron
		bool getType() const;
		/*! Getter of t_spikes
		 * @Return The vector t_spikes (containing the time of the spikes)
		 */
		vector<double> getSpikes();
		//! Add a spike to the vector t_spikes
		void addSpike(double v);
		//! Setter refractory
		void setRefract(bool b);
		//! Getter refractory
		bool getRefract() const;

		
		/*! Update methode
		 * @Param t_rep is the number of ms we want to update
		 * @Param poiss (if we want to use the distribution)
		 * @Param for both parameters I put a default parameter
		 * @brief Update the state of the neuron
		 * @Return If there is a spike (true) or not (false)
		 */ 
		bool update(double t_rep = 0.1, bool poiss = true);
		
		/*! Calculation of the potential
		 * @Param poisson (if we want to use the distribution)
		 * calculate The new potential
		 * @Return The new potential
		 */
		double pot_calc(bool poisson = true);
		
		/*! Receive methode
		 * @Param j_ is the current from the pre-neuron
		 * @brief Update the ring-buffer
		 */
		void receive(double j_);
		
		/*! Set the buffer
		 * @brief Sets the ring-buffer after a time step
		 */ 
		void set_buffer();
		
		//! Get the size of our vector t_spikes
		//! @Return The size of t_spikes (the number of spikes of the neuron)
		size_t getSize();
		
		
		//! Calculation of the poisson distribution
		//! @return The background noise generated from the poisson distribution
		double Poisson();
	
};




#endif
