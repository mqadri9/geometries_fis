#include "SwStXtd.h"

// static double t_liftoff = 0;

Sw_St_Xtd_out Sw_St_Xtd(std::map<std::string, FIA> pFIS_stack,
						std::map<int, FA> FFS_stack,
						vector<float> nodes,
						vector<float> ecat_data,
						int NUM_LEGS,
						float vb,
						float vx_des,
						float marginalUtility_threshold,
						float wkspace_margin,
						float x_swing,
						float x_td_nom,
						vector<float> x_td_old,
						float internode_dx,
						int trouble,
						int t,
						vector<float> leg_command_in,
						int lesion,
						vector<float> lesion_legs,
						vector<float> lesion_leg_xtd,
						vector<float> lesion_leg_xswing)
{
	Sw_St_Xtd_out output;
	// ----------------------- Check direction of travel ------------------
	bool WAY = true;
	if(vb < 0)
	{
		WAY = false;
	}
	// cout << WAY << endl;

	// --------------------------------------------------------------------
	// ------------------ Definitions -----------------------------------
	//static VectorXd t_liftoff = VectorXd::Zero(NUM_LEGS);
	//VectorXd x_swingVec = x_swing*VectorXd::Ones(NUM_LEGS);
	//VectorXd x_td = x_td_old;
	//VectorXd swing_transition_flag = VectorXd::Zero(NUM_LEGS);
	// t_liftoff += 1;

	//cout << x_td << endl;
	vector<int> swing_state_flag = {7};
	vector<int> leg_command = {8};
	vector<float> x_td_out = {1.5};

	output.leg_command = leg_command;
	output.swing_state_flag = swing_state_flag;
	output.x_td_out = x_td_out;	
	return output;
}