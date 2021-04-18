#include "SwStXtd.hpp"
#include <stdio.h>

// static double t_liftoff = 0;
static double mass = 9; // [kg]
static double g = 9.81;

void Sw_St_Xtd(double vb, double x_swing, int NUM_LEGS, VectorXd x_td_old, 
				double marginalUtility_threshold, VectorXd leg_command_in) {

	// ----------------------- Check direction of travel ------------------
	bool WAY = true;
	if(vb < 0)
	{
		WAY = false;
	}
	// cout << WAY << endl;

	// --------------------------------------------------------------------
	// ------------------ Definitions -----------------------------------
	static VectorXd t_liftoff = VectorXd::Zero(NUM_LEGS);
	VectorXd x_swingVec = x_swing*VectorXd::Ones(NUM_LEGS);
	VectorXd x_td = x_td_old;
	VectorXd swing_transition_flag = VectorXd::Zero(NUM_LEGS);
	// t_liftoff += 1;

	cout << x_td << endl;

}