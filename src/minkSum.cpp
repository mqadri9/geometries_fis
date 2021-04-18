#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include "igl/sort.h"
#include "igl/slice_mask.h"

using namespace Eigen;
using namespace std;

ArrayXXf minkSum(ArrayXXf V1, ArrayXXf V2) {

	int m1 = V1.rows();
	int n = V1.cols();

	int m2 = V2.rows();

	ArrayXXf V1_new(m1+1,n);
	V1_new << V1,
			  0, 0;

	ArrayXXf V2_new(m2+1,n);
	V2_new << V2,
			  0, 0;

	ArrayXXf dV1(m1,n);
	dV1 = V1_new.block(1,0,V1_new.rows()-1,n) - V1_new.block(0,0,V1_new.rows()-1,n);
	

	ArrayXXf dV2(m2,n);
	dV2 = V2_new.block(1,0,V2_new.rows()-1,n) - V2_new.block(0,0,V2_new.rows()-1,n);

	ArrayXXf Vs(m1+m2,n);
	Vs << dV1,
		  dV2;

	ArrayXf tans(m1+m2);
	for(int i = 0; i < tans.rows(); i++) {
		tans(i) = atan2(Vs(i,1),Vs(i,0));
	}

	ArrayXf tans2 = tans + 2*M_PI;
	tans = (tans.array() < 0).select(tans2,tans);

	ArrayXi IX(tans.size());
	ArrayXf Y(tans.size());
	igl::sort(tans,1,true,Y,IX);

	ArrayXXf ab = ArrayXXf::Zero(IX.size()+1, 2);
	ArrayXXf v = ArrayXXf::Zero(1,2);
	for(int i = 0; i < IX.size(); i++) {
		v += Vs.row(IX(i));
		ab.row(i+1) = v;
	}
	ArrayXXf S_minkSummed = igl::slice_mask(ab, ab.col(1).array()>=0,1);

	return S_minkSummed;


}
