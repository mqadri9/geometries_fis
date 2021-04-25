#ifndef UTILS_H_
#define UTILS_H_


#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <stdio.h>
#include <numeric>
#include "cnpy.h"
#include <complex>
#include <cstdlib>
#include <iostream>
#include <string>
#include <CGAL/minkowski_sum_2.h>
#include "bops_linear.h"
#include "pgn_print.h"
#include <CGAL/convex_hull_2.h>
#include <CGAL/property_map.h>

using namespace Eigen;
using namespace std;

typedef std::vector<std::vector<double>> FA;
typedef std::vector<std::tuple<FA, double>> FIA;

struct Sw_St_Xtd_out {
	vector<bool> swing_state_flag;
	vector<int> leg_command;
	vector<float> x_td_out;
};

struct getpFIS_at_x_from_pFIS_stack_out {
    double volume;
    FA pFIS;
};


static double mass = 9; // [kg]
static double g = 9.81;
static int MAX_VERTICES = 100;

template <typename T>
bool any(T a){
      for(int i=0; i < a.size(); i++)
            if(a[i]) return true; 
      return false;
}

template <typename T>
void print_vector(T a){
      for(int i=0; i < a.size(); i++)
            cout << a.at(i) << ' '; 
      cout << endl;
}


template <typename T>
bool find(T a){
      vector<int> res;
      for(int i=0; i < a.size(); i++)
            if(a[i] >= 0) return true; 
      return false;
}


vector<float> diff(vector<float> a);

float mean(vector<float> a);

vector<float> linspace(float  a, float b, int num);

getpFIS_at_x_from_pFIS_stack_out getpFIS_at_x_from_pFIS_stack(std::map<std::string, FIA> pFIS_nodes,
                                                            float x,
                                                            vector<float> nodes,
                                                            string WAY);

Polygon_2 FA_to_cgalPolygon(FA pFIS);
Polygon_2 cgalPoint2_to_Polygon(vector<Point_2> v);
#endif