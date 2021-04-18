// #include <Eigen/Dense>
// #include <iostream>

// using namespace Eigen;
// using namespace std;
#include "SwStXtd.cpp"

//#include "./matplotlib-cpp/matplotlibcpp.h"

#include <cmath>
#include <algorithm>
// #include <math.h>
#include <typeinfo>
// #include <valarray> 
#include "igl/sort.h"
#include "igl/slice_mask.h"
#include "igl/slice.h"
#include "minkSum.cpp"

#include <CGAL/minkowski_sum_2.h>
#include "bops_linear.h"
#include "pgn_print.h"
#include <CGAL/convex_hull_2.h>
#include <CGAL/property_map.h>
#include <CGAL/convex_hull_2.h>

// #include "./libigl/include/igl/copyleft/cgal/convex_hull.h"

//namespace plt = matplotlibcpp;

int main()
{
  // Matrix3d m = Matrix3d::Random();
  // m = (m + Matrix3d::Constant(1.2)) * 50;
  // cout << "m =" << endl << m << endl;
  // Vector3d v(1,2,3);
  
  // cout << "m * v =" << endl << m * v << endl;

  double vb = -0.4;
  double x_swing = -0.15;
  int NUM_LEGS = 4;
  VectorXd x_td = VectorXd::Ones(NUM_LEGS)*0.15;
  double marginalUtility_threshold = 0.2;
  VectorXd leg_command_in = VectorXd::Ones(NUM_LEGS);

  for(int i = 0; i < 1; i++) {
  	Sw_St_Xtd(vb, x_swing, NUM_LEGS, x_td, marginalUtility_threshold, leg_command_in);
  }
  
  // plt::plot({1,3,2,4});
  // plt::show();

  // cout << x_td[x_td > 0] << endl;

  // std::vector<int> v;
  // v.push_back(1);
  // v.push_back(3);
  // v.push_back(10);
  // auto it = std::find_if(v.begin(), v.end(), [](int i){return i>1;});
  // // for(int i = 0; i < it.size(); i++) {
  // // 	cout << it[i] << endl;
  // // }
  // cout << it[1] << endl;
  // cout << v.size() << endl;

  Array3f aa, bb;
  aa << 1.0,2.0,3.0;
  bb = Array3f::Random();
  // aa(1) = 3;
  // cout << aa[1] << endl;
  cout << bb << endl;
  cout << (aa.array() == 1).select(bb,aa) << endl;

  ArrayXXf V(5,3);
  V << 0, 0, 0,
  	   1, 1, 0,
  	   1, 2, 0,
  	   0, 0.5, 0,
  	   0, 2, 0;

  cout << V << endl;
  cout << "----------------" << endl;
  cout << V.block(1,0,V.rows()-1,V.cols()) << endl;
  cout << V.cols() << endl;

  // ArrayXXf Vs(10,3);
  // Vs << V,
  // 		V;
  // cout << Vs << endl;

  // cout << V-V << endl;

  // V.block(1,0,V.rows()-1,1).array() / V.block(1,1,V.rows()-1,2).array();
  // atan2(V.block(1,0,V.rows()-1,1), V.block(1,1,V.rows()-1,2));
  // cout << typeid(V.block(1,0,V.rows()-1,1).array()).name() << endl;

  // cout << atan2(V(1,0),V(1,1)) << endl;

  ArrayXf tans(4,1);
  for(int i = 1; i < tans.rows(); i++) {
  	tans(i-1) = atan2(V(i,0),V(i,1));
  }
  tans(3) = -1;

  cout << tans << endl;

  ArrayXf tans2 = tans + 2*M_PI;
  cout << (tans.array() < 0).select(tans2,tans) << endl;;

  // cout << tans << endl;


  // ArrayXi IX(4,1);
  // ArrayXf Y(4,1);
  // igl::sort(tans,1,true,Y,IX);

  // cout << "----------------" << endl;
  // cout << Y.size() << endl;

  // ArrayXXf ab(4,2);
  // ab << 1,2,
  // 		3,-1,
  // 		-4,2,
  // 		-5,-3;

  // cout << "----------------" << endl;
  // cout << ab << endl;

  // ArrayXXf S_minkSummed = igl::slice_mask(ab, ab.col(1).array()>=0,1);

  // cout << "----------------" << endl;
  // cout << S_minkSummed << endl;

  ArrayXXf V1(4,2), V2(3,2);
  V1 << 0,0,
  		0,1,
  		1,1,
  		1,0;
  V2 << 0,0,
  		-0.5,1,
  		-1,0.5;

  cout << "Vertices " << endl;
  cout << "----------------" << endl;
  cout << V1 << endl;
  cout << V2 << endl;
  cout << "----------------" << endl;
  ArrayXXf S_minkSummed = minkSum(V1,V2);
  cout << S_minkSummed << endl;
  int n1 = S_minkSummed.rows();

  std::vector<float> s1(n1),s2(n1);
  for(int i=0; i<S_minkSummed.rows(); i++) {
  	s1.at(i) = S_minkSummed(i,0);
  	s2.at(i) = S_minkSummed(i,1);
  }

  // plt::fill({S_minkSummed.col(0).array()}, {S_minkSummed.col(1).array()});
  //plt::plot(s1, s2);
  //plt::show();

  // TRY CGAL MKSUM
  Polygon_2   P;
  P.push_back(Point_2(-1, -1));  P.push_back(Point_2(1, -1));
  P.push_back(Point_2(0, 1));
  std::cout << "P = " << P << std::endl;
  // Construct the square.
  Polygon_2   Q;
  Q.push_back(Point_2(3, -1));  Q.push_back(Point_2(5, -1));
  Q.push_back(Point_2(5, 1));   Q.push_back(Point_2(3,  1));
  std::cout << "Q = " << Q << std::endl;
  // Compute the Minkowski sum.
  Polygon_with_holes_2  sum = CGAL::minkowski_sum_2(P, Q);
  CGAL_assertion(sum.number_of_holes() == 0);
  std::cout << "P (+) Q = " << sum.outer_boundary() << std::endl;
  print_polygon_with_holes(sum);



  // TRY CGAL CONVEX HULL
  std::vector<Point_2> result;
  std::vector<Point_2> points = { Point_2(10,0),
                                    Point_2(10,0),
                                    Point_2(0,10),
                                    Point_2(1,1),
                                    Point_2(3,4),
                                    Point_2(0,0),
                                    Point_2(10,10),
                                    Point_2(2,6) };
  CGAL::convex_hull_2( points.begin(), points.end(), std::back_inserter(result) );
  std::cout << result.size() << " points on the convex hull" << std::endl;
  
}
  
