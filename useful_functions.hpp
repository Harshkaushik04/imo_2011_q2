#include <iostream>
#include <random>
#include <cmath>
#include <unordered_map>

using namespace std;

vector<vector<int>> random_points_generator(int,int);
bool colinearity_checker(vector<vector<int>>);

class rotating_line{
public:
    vector<double> middle_point;
    double slope;
    double angular_velocity;

public:
    rotating_line(vector<double>,double,double);

public:
    int closest_point_index(vector<vector<int>>);
};
double find_value(rotating_line,vector<double>);
rotating_line find_optimal_line(vector<vector<int>>,double);
rotating_line change_line_attributes(rotating_line,vector<double>,double,double);