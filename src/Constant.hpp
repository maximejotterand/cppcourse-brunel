#include <cmath>

#ifndef CONSTANT_H
#define CONSTANT_H

using namespace std;

//! The duration of one time step (0.1ms)
constexpr double h(0.1);
//! Threshold potential above which we observe a spike
constexpr double v_th(20.0);
//! The time limit of the experiment
//! 20 means that it will be 200 time steps
constexpr double t_stop(100);
//! The input current
constexpr double c(0.0);
//! The resistance of the membrane
constexpr double R(20);
//! Capacity of the membrane
constexpr double C(1);
//! tau is the resistance and capacity ratio
constexpr double t(R * C);
//! Ji / J, the ratio of excitatory current and inhibitory one
constexpr double g(5);
//! eta factor (u_seuil and u_ext)
constexpr int eta(2);

//! The excitatory current
constexpr double J(0.1);
//! The inhibitory "current"
constexpr double Ji(-g * J);
//! The delay of the receiving spike current
constexpr int D(1.5);
//! The poisson coefficient
constexpr double Jp(0.1);

//! The total number of neurons in the network
constexpr int N(12500);
//! The number of excitatory neurons
constexpr int Ne((N * 4) / 5);
//! The number of inhibitory neurons
constexpr int Ni(N / 5);
//! Ratio of connected neurons to one neuron and all neuron of the specific state
constexpr double E(0.1);
//! The number of excitatory neurons connected to one neuron
constexpr int Ce(Ne * E);
//! The number of inhibitory neurons connected to one neuron
constexpr int Ci(Ni * E);

//! The first constant in the calculation of the potential
constexpr double c1(pow(M_E, (-h / t)));
//! The second constant in the calculation of the potential
constexpr double c2(1 - c1);

//! u_th according the brunel course
const double u_th (v_th / (J * t));
//! u_ext according the brunel course
const double u_ext (eta * u_th);

#endif
