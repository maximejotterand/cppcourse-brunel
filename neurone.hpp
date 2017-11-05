#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <random>
#include "Constant.hpp"

#ifndef NEURONE_H
#define NEURONE_H

using namespace std;


class Neurone {
	private :
		//! Vector containing the time when the spike happened
		vector<double> t_spikes;
		//! The potential
		double pot;
		//! Bool giving if the neuron is refractory (true) or not (false)
		bool refract;
		//! The ring-buffer 
		array<double, 16> buffer;
		//! The current
		double courant;
		
		
	public :
		//! Constructor
		//! @Param p is the initial potential, r is the initial refractory booleen
		Neurone(double p = 0.0, bool r = false);
		//! Getter potential
		double getPot() const;
		//! Setter potential
		void setPot(double p);
		//! Setter for the current
		void setCourant(double i);
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
