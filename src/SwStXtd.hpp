#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

void Sw_St_Xtd(double vb, double x_swing, int NUM_LEGS, VectorXd x_td, 
				double marginalUtility_threshold, VectorXd leg_command_in);