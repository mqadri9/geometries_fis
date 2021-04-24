#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <stdio.h>

using namespace Eigen;
using namespace std;

typedef std::vector<std::vector<double>> FA;
typedef std::vector<std::tuple<FA, double>> FIA;

struct Sw_St_Xtd_out {
	vector<int> swing_state_flag;
	vector<int> leg_command;
	vector<float> x_td_out;
};

static double mass = 9; // [kg]
static double g = 9.81;

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
						vector<float> lesion_leg_xswing);
