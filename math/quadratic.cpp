#include "./quadratic.h"
using std::vector;
vector<double> q_solver(double a, double b, double c){
  vector<double> ret;
  if(b*b - 4 * a * c < 0) return ret;
  ret.push_back((-b + sqrt(b*b - 4 * a * c))/(-2*a));
  ret.push_back((-b - sqrt(b*b - 4 * a * c))/(-2*a));
  return ret;
}
