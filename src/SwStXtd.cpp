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
						vector<bool> leg_command_in,
						int lesion,
						vector<bool> lesion_legs,
						vector<float> lesion_leg_xtd,
						vector<float> lesion_leg_xswing)
{
	Sw_St_Xtd_out output;
	vector<bool> swing_transition_flag(NUM_LEGS, false);
	vector<int> leg_command = {8};
	vector<float> x_td_out = {1.5};

	// ----------------------- Check direction of travel ------------------
	string WAY = "backward";
	if(vb >= 0)
	{
		WAY = "forward";
	}

	bool doFacetEnumeration = 0;
	float swingTime = 0.25;
	
	// --------------------------------------------------------------------
	// ------------------ Definitions -----------------------------------
	//static VectorXd t_liftoff = VectorXd::Zero(NUM_LEGS);
	//VectorXd x_swingVec = x_swing*VectorXd::Ones(NUM_LEGS);
	//VectorXd x_td = x_td_old;
	//VectorXd swing_transition_flag = VectorXd::Zero(NUM_LEGS);
	// t_liftoff += 1;

	float t_for_trouble = -1.;
	vector<float> t_liftoff(NUM_LEGS, 1);
	bool can_enter_trouble_response;
	vector<float> waiting_time(4, 0);
	if(t_for_trouble < 0) {
		fill(t_liftoff.begin(), t_liftoff.end(), 1); 
		t_for_trouble = 2*swingTime;
		can_enter_trouble_response = 1;
		fill(waiting_time.begin(), waiting_time.end(), 0); 
	}
	
	vector<float> x_td = x_td_old;
	if (t - t_for_trouble >= swingTime) 
	{
		can_enter_trouble_response = 1;
	}
	vector<float> x_swingVec(NUM_LEGS, x_swing);

	if(lesion && any(lesion_legs)) {
		// These two cases seem to be the same in the matlab code
		if(WAY == "forward") {
			for(int i =0; i<lesion_legs.size();i++) {
		    	if(lesion_legs[i] == true) {
					x_swingVec[i] = lesion_leg_xswing[i];
				}
			}
		}
		else{
			for(int i =0; i<lesion_legs.size();i++) {
				if(lesion_legs[i] == true) {
					x_swingVec[i] = lesion_leg_xswing[i];
				}
			}			
		}
	}	
	int num_rows = MAX_VERTICES;
	vector<vector<vector<double>>> pFIS_single_for_MU;
	pFIS_single_for_MU.push_back({{0,0}});
	pFIS_single_for_MU.push_back({{0,0}});
	pFIS_single_for_MU.push_back({{0,0}});
	pFIS_single_for_MU.push_back({{0,0}});
	vector<float> entry2 = {0,0};
	vector<float> pFIS_interNode ={0,0};
	vector<int> check_leg_in_stance(NUM_LEGS, 0);
	vector<float> x_fh = ecat_data;
	vector<bool> leg_state = leg_command_in;
	check_leg_in_stance[2] = 10;
		
	int N_in_contact = 0;
	for(size_t leg=1; leg<=NUM_LEGS; leg++) {
		if(leg_state[leg-1] && x_fh[leg-1] > nodes[0] + wkspace_margin) {
			N_in_contact = N_in_contact+1;
			check_leg_in_stance[N_in_contact-1] = leg-1;
		}
	}
	vector<float> marginalUtility(NUM_LEGS, 0);
	

	//===============================================
	//=================== Computing the Marginal Utility
	//===============================================
	double vol_of_pFIS_tot_for_MU;
	Polygon_2 cgal_pFIS_tot_for_MU;
	if(N_in_contact) {
		getpFIS_at_x_from_pFIS_stack_out pFIS_tot_for_MU =  getpFIS_at_x_from_pFIS_stack(pFIS_stack,
																						x_fh[check_leg_in_stance[0]],
																						nodes,
																						WAY);		
		if(check_leg_in_stance[0] == 0) {
			pFIS_single_for_MU[0] = pFIS_tot_for_MU.pFIS;
		}
		else if (check_leg_in_stance[0] == 1) {
			pFIS_single_for_MU[1] = pFIS_tot_for_MU.pFIS;
		}
		else if (check_leg_in_stance[0] == 2) {
			pFIS_single_for_MU[2] = pFIS_tot_for_MU.pFIS;
		}
		else if (check_leg_in_stance[0] == 3) {
			pFIS_single_for_MU[3] = pFIS_tot_for_MU.pFIS;
		}
		else {
			pFIS_single_for_MU[0] = pFIS_tot_for_MU.pFIS;
		}
		//for(int i=0; i<pFIS_single_for_MU[0].size(); i++) {
		//	print_vector(pFIS_single_for_MU[0][i]);
		//}
		cgal_pFIS_tot_for_MU = FA_to_cgalPolygon(pFIS_tot_for_MU.pFIS);
	}

	if(N_in_contact > 1) {
		double cVol = 0;
		for(int legs = 0; legs < NUM_LEGS; legs ++ )
		{
			if (std::find(check_leg_in_stance.begin() + 1, check_leg_in_stance.end(), legs) != check_leg_in_stance.end())
			{
				getpFIS_at_x_from_pFIS_stack_out tmp =  getpFIS_at_x_from_pFIS_stack(pFIS_stack,
																					x_fh[legs],
																					nodes,
																					WAY);
				Polygon_2 cgal_tmp = FA_to_cgalPolygon(tmp.pFIS);
				//cout << "============= " << legs << "--------------------" << endl;
				//for(int i=0; i<tmp.pFIS.size(); i++) {
				//	print_vector(tmp.pFIS[i]);
				//}
				//cout << cgal_tmp << endl;
				//cout << cgal_pFIS_tot_for_MU << endl; 
				Polygon_with_holes_2  sum = CGAL::minkowski_sum_by_full_convolution_2(cgal_pFIS_tot_for_MU, cgal_tmp);
				std::vector<Point_2> mink_out;
				std::vector<Point_2> result;
				for(size_t i=0; i< sum.outer_boundary().size(); i++){
					mink_out.push_back(sum.outer_boundary()[i]);
				} 
				CGAL::convex_hull_2( mink_out.begin(), mink_out.end(), std::back_inserter(result) );
			    cgal_pFIS_tot_for_MU = cgalPoint2_to_Polygon(result);
				cVol = cgal_pFIS_tot_for_MU.area();
				if(legs == 0) {
					pFIS_single_for_MU[0] = tmp.pFIS;
				}
				else if (legs == 1) {
					pFIS_single_for_MU[1] = tmp.pFIS;
				}
				else if (legs == 2) {
					pFIS_single_for_MU[2] = tmp.pFIS;
				}
				else if (legs == 3) {
					pFIS_single_for_MU[3] = tmp.pFIS;
				}
				else {
					pFIS_single_for_MU[0] = tmp.pFIS;
				}
			
			}
		}
		vol_of_pFIS_tot_for_MU = cVol;
	}
	else if(N_in_contact == 1) {
		vol_of_pFIS_tot_for_MU = cgal_pFIS_tot_for_MU.area(); 
	}
	else {
		vol_of_pFIS_tot_for_MU = 0;
	}

	/*
	for(int i=0; i<pFIS_single_for_MU[0].size(); i++) {
		print_vector(pFIS_single_for_MU[0][i]);
	}
	cout << "==============================" << endl;
	for(int i=0; i<pFIS_single_for_MU[1].size(); i++) {
		print_vector(pFIS_single_for_MU[1][i]);
	}	
	cout << "==============================" << endl;
	for(int i=0; i<pFIS_single_for_MU[2].size(); i++) {
		print_vector(pFIS_single_for_MU[2][i]);
	}
	cout << "==============================" << endl;
	for(int i=0; i<pFIS_single_for_MU[3].size(); i++) {
		print_vector(pFIS_single_for_MU[3][i]);
	}
	*/
	// ===================================

	Polygon_2 cgal_tmp;
	double tmp_vol = 0;
	for(int legs =0; legs<NUM_LEGS; legs++){
		if(!leg_state[legs]) continue;
		vector<int> tmp_ind;
		vector<vector<double>> tmp;
		vector<vector<double>> entry2;
		for(size_t i=0; i<check_leg_in_stance.size(); i++) {
			if(i==legs) continue;
			tmp_ind.push_back(check_leg_in_stance[i]);
		}
		if(tmp_ind.size() > 0) {
			if(tmp_ind[0] == 0) {
				tmp = pFIS_single_for_MU[0];
			} 
			else if(tmp_ind[0] == 1){
				tmp = pFIS_single_for_MU[1];
			}
			else if(tmp_ind[0] == 2){
				tmp = pFIS_single_for_MU[2];
			}
			else if(tmp_ind[0] == 3){
				tmp = pFIS_single_for_MU[3];
			}
			else{
				tmp = {{0, 0}};
				cout << "Entered otherwise statement when evaluating tmp_ind(1)" << endl;
			}
			cgal_tmp = FA_to_cgalPolygon(tmp);
			if(tmp_ind.size() > 1) {
				int k = 1;
				while(k < tmp_ind.size()) {
					if(tmp_ind[k] == 0) {
						entry2 = pFIS_single_for_MU[0];
					} 
					else if(tmp_ind[k] == 1){
						entry2 = pFIS_single_for_MU[1];
					}
					else if(tmp_ind[k] == 2){
						entry2 = pFIS_single_for_MU[2];
					}
					else if(tmp_ind[k] == 3){
						entry2 = pFIS_single_for_MU[3];
					}
					else{
						entry2 = pFIS_single_for_MU[0];
						cout << "Entered otherwise statement when evaluating tmp_ind(k)" << endl;
					}
					Polygon_2 cgal_entry2 = FA_to_cgalPolygon(entry2);

 					Polygon_with_holes_2  sum = CGAL::minkowski_sum_by_full_convolution_2(cgal_tmp, cgal_entry2);
					std::vector<Point_2> mink_out;
					std::vector<Point_2> result;
					for(size_t i=0; i< sum.outer_boundary().size(); i++){
						mink_out.push_back(sum.outer_boundary()[i]);
					} 
					CGAL::convex_hull_2( mink_out.begin(), mink_out.end(), std::back_inserter(result) );
					cgal_tmp = cgalPoint2_to_Polygon(result);
					tmp_vol = cgal_tmp.area();
					k++;
				}
			}
			else {
				std::vector<Point_2> result;
				vector<Point_2> tmp_point2 = FA_to_cgalPoint2(tmp);
				CGAL::convex_hull_2( tmp_point2.begin(), tmp_point2.end(), std::back_inserter(result) );
				cgal_tmp = cgalPoint2_to_Polygon(result);
				tmp_vol = cgal_tmp.area();
			}
		} 
		else {
			tmp_vol = 0;
		}
		marginalUtility[legs] = 1 - tmp_vol/vol_of_pFIS_tot_for_MU;
	}

	//print_vector(marginalUtility);


	fill(t_liftoff.begin(), t_liftoff.end(), t);
	vector<float> x_fh_at_liftoff(NUM_LEGS, x_td_nom);

	for(size_t i =0; i<NUM_LEGS; i++) {
		vector<bool> cond_to_swing;
		bool x_marg_safety_cond;
		vector<int> neighborLegs;
		if(vb >= 0) {
			for(size_t k =0; k<x_fh.size(); k++) {
				if(x_fh[k] < x_swingVec[k]){
					cond_to_swing.push_back(true);
				}
				else{
					cond_to_swing.push_back(false);
				}
			}
			x_marg_safety_cond = x_marg_safety_cond_f(x_fh[i], wkspace_margin, nodes);
		}
		else {
			for(size_t k =0; k<x_fh.size(); k++) {
				if(x_fh[k] > x_swingVec[k]){
					cond_to_swing.push_back(true);
				}
				else{
					cond_to_swing.push_back(false);
				}
			}
			x_marg_safety_cond = x_marg_safety_cond_b(x_fh[i], wkspace_margin, nodes);
		}
	
	
		if(cond_to_swing[i] && leg_state[i]){
			if(marginalUtility[i] <= marginalUtility_threshold || x_marg_safety_cond || lesion_legs[i]){
				if(i == 1 || i == 4) {
					neighborLegs.push_back(2);
					neighborLegs.push_back(3);
				}
				else if(i==2 || i==3) {
					neighborLegs.push_back(1);
					neighborLegs.push_back(4);					
				}
				else {
					neighborLegs.push_back(1);
					neighborLegs.push_back(4);	
				}
			}
			if(all(leg_state, true)) {
				leg_state[i]=0;
				swing_transition_flag[i] = 1;
				t_liftoff[i] = t;
				x_fh_at_liftoff[i] = x_fh[i];
			}
			else {
				for(auto& neighour:neighborLegs) {
					if(leg_state[neighour] == 0) {
						if(x_marg_safety_cond || (lesion_legs[i] && lesion)) {
							if(x_marg_safety_cond){
								leg_state[neighour-1] = 1;
								leg_state[i] = 0;
								swing_transition_flag[i] = 1;
								t_liftoff[i] = t;
								x_fh_at_liftoff[i] = x_fh[i];
							}
							else {
								waiting_time[i] = waiting_time[i] + 1;
								if(waiting_time[i] >= 5) {
									waiting_time[i] =0;
									leg_state[neighour-1] = 0;
									swing_transition_flag[i] = 1;
									t_liftoff[i] = t;
									x_fh_at_liftoff[i] = x_fh[i];
								}
								else {
									leg_state[neighour-1] = 1;
									leg_state[i] = 1;
								}
							}
						}
					}
				}
			}
		}
		if(leg_state[i] == 0) {
			if(abs(t - t_liftoff[i]) < 3e-3){
				x_td[i] = x_td_nom;
				if(lesion && lesion_legs[i]) {
					if(WAY == "forward") {
						x_td[i] = lesion_leg_xtd[i];
					}
					else {
						x_td[i] = -lesion_leg_xtd[i];
					}
				}
				if(trouble) {
					cout << "trouble = true. Not implemented" << endl;
				}
			}
		}
		else {
			// Unused variable declaration in matlab code
		}
	}

	output.leg_command = leg_state;
	output.swing_state_flag = swing_transition_flag;
	output.x_td_out = x_td;	
	return output;
}