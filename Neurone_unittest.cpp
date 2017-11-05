#include "neurone.hpp"
#include "network.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <cmath>
#include "Constant.hpp"

namespace {


TEST(NeuroneTest, Pos_input)
{
	Neurone n;
	n.setCourant(1.0);
	//First update
	n.update(0.1, false);
	EXPECT_EQ((c1 * 0.0) + (1.0 * R * c2), n.getPot());
	
	//After several updates
	n.update(500, false);
	//The neuron should never value 20 but tend to 20 because external courant is 1.0
	EXPECT_EQ(0, (n.getSpikes()).size());
	EXPECT_GT(1E-3, std::fabs(19.999 - n.getPot()));
	
}



TEST(NeuroneTest, t_spikes)
{
	Neurone n2;
	n2.setCourant(1.01);
	
	n2.update(92.3, false);
	//Update until the first spike to occur
	//EXPECT_EQ(0, (n2.getSpikes()).size());
	EXPECT_EQ(0, n2.getSize());
	
	n2.update(0.1, false);
	//Then the neuron is reset
	EXPECT_EQ(1, n2.getSize());
	EXPECT_EQ(0, n2.getPot());
	
}


TEST(TwoNeurons, receive)
{
	Neurone n1;
	Neurone n2;
	n1.setCourant(1.01);
	
	//Updating until n1 spikes + the delay
		if (n1.update(92.4, false)) {
			n2.receive(J);
		}
		
	n2.update(D, false);
	EXPECT_EQ(0.1, n2.getPot());
}

TEST(TwoNeurons, neuron2_spikes)
{
	Neurone n3;
	Neurone n4;
	
	
	n3.setCourant(1.01);
	n4.setCourant(1.0);
	
		//n4 cannot spike because the input current is 1.0
		//So its potential will tend to 20 but never reach
		//With the excitation of the n3 it will be able to spike
			n4.update(184.9, false);
		if (n3.update(184.9, false)) {
			n4.receive(J);
		}
	
	//Before the spike
	n4.update(D, false);
	EXPECT_EQ(0, n4.getSize());
	//Spike occured
	n4.update(0.1, false);
	EXPECT_EQ(1, n4.getSize());
}


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

}

