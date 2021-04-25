// #include <Eigen/Dense>
// #include <iostream>

// using namespace Eigen;
// using namespace std;
//#include "SwStXtd.cpp"

//#include "./matplotlib-cpp/matplotlibcpp.h"

#include <cmath>
#include <algorithm>
// #include <math.h>
#include <typeinfo>
// #include <valarray> 
#include "igl/sort.h"
#include "igl/slice_mask.h"
#include "igl/slice.h"
//#include "minkSum.cpp"

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
  /*
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
  */  
  Polygon_2   P;
  Polygon_2   Q;
  std::vector<Point_2> a = {Point_2(0,         0),
                      Point_2(50.9609,  169.8698),
                      Point_2(182.5454,  608.4847),
                      Point_2(169.1422,  628.4398),
                      Point_2(155.7390,  648.3949),
                      Point_2(114.7623,  691.9717),
                      Point_2(73.7856 , 735.5485),
                      Point_2(-0.6973 , 805.3109),
                      Point_2(-36.6585,  835.0555),
                      Point_2(-72.6196,  864.8000),
                      Point_2(-134.8826,  897.6606),
                      Point_2(-191.5651,  915.1954),
                      Point_2(-196.9620 , 916.5494),
                      Point_2(-202.3589,  917.9034),
                      Point_2(-239.3697,  926.0291),
                      Point_2(-276.3805,  934.1549),
                      Point_2(-277.5762,  925.2540)};

  std::vector<Point_2> b = {
      Point_2( 0,         0),
      Point_2(76.6720,  255.5732),
      Point_2( 63.2688,  275.5283),
      Point_2( 22.2921,  319.1051),
      Point_2(  -13.6691,  348.8497),
      Point_2(  -70.3516,  366.3845),
      Point_2(  -75.7485,  367.7385),
      Point_2( -112.7593 , 375.8642)
  };

  for(size_t i=0;i<a.size();i++) {
    P.push_back(a[i]);
  }
  for(size_t i=0;i<b.size();i++) {
    Q.push_back(b[i]);
  } 


  //P.push_back(Point_2(-1, -1));  P.push_back(Point_2(1, -1));
  //P.push_back(Point_2(0, 1));
  //std::cout << "P = " << P << std::endl;
  // Construct the square.
  
  //Q.push_back(Point_2(3, -1));  Q.push_back(Point_2(5, -1));
  //Q.push_back(Point_2(5, 1));   Q.push_back(Point_2(3,  1));
  //std::cout << "Q = " << Q << std::endl;
  // Compute the Minkowski sum.
  Polygon_with_holes_2  sum = CGAL::minkowski_sum_by_full_convolution_2(P, Q);
  //CGAL_assertion(sum.number_of_holes() == 0);
  std::cout << "P (+) Q = " << sum.outer_boundary() << std::endl;
  print_polygon_with_holes(sum);



  // TRY CGAL CONVEX HULL
  std::vector<Point_2> mink_out;
  std::vector<Point_2> rt {
          Point_2(0  ,                       0),
         Point_2( 50.9609450180299 ,         169.869816726766),
          Point_2(182.545395521345 ,         608.484651737817),
          Point_2(169.142218644314 ,         628.439760395462),
          Point_2(155.739041767283 ,         648.394869053106),
          Point_2(114.762319466014 ,         691.971688481704),
          Point_2(73.7855971647449 ,         735.548507910302),
        Point_2(-0.697336906676824 ,         805.310910518877),
         Point_2(-36.6584812809133 ,          835.05545665749),
         Point_2(-72.6196256551499 ,         864.800002796103),
         Point_2(-134.882621398556 ,         897.660570423704),
        Point_2( -191.565090463028 ,         915.195365564992),
         Point_2(-196.962011468277,          916.549385532199),
        Point_2( -202.358932473527,          917.903405499406),
         Point_2(-239.369727221797,         926.029142207332),
        Point_2( -276.380521970067 ,         934.154878915257),
        Point_2( -277.576204357325 ,         925.254014524418),
        Point_2( -81.7878142880261 ,         272.626047626754),
       Point_2(4.2632564145606e-14 ,     1.70530256582424e-13)
  };
  
  for(size_t i=0; i< sum.outer_boundary().size(); i++){
    mink_out.push_back(sum.outer_boundary()[i]);
  }  
  
  std::vector<Point_2> result;
  Polygon_2 po; 
  std::vector<Point_2> points = { Point_2(10,0),
                                    Point_2(10,0),
                                    Point_2(0,10),
                                    Point_2(1,1),
                                    Point_2(3,4),
                                    Point_2(0,0),
                                    Point_2(10,10),
                                    Point_2(2,6) };
  
  
  CGAL::convex_hull_2( mink_out.begin(), mink_out.end(), std::back_inserter(result) );
  std::cout << result.size() << " points on the convex hull" << std::endl;
  for(size_t i=0; i< result.size(); i++){
    std::cout << result[i] << std::endl;
    po.push_back(result[i]);
  }
  std::cout << po.area() << std::endl;
}
  
