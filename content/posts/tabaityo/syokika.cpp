#include <iostream>
#include <iomanip>
#include <cmath>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

constexpr int d = std::numeric_limits<double>::digits10;
constexpr int dd = std::numeric_limits<cpp_dec_float_100>::digits10;

cpp_dec_float_100 PI = boost::math::constants::pi<cpp_dec_float_100>();

int main() {

  cpp_dec_float_100 pi = PI;

  std::cout << std::showpoint;

  std::cout << std::setprecision(50)
             << PI << std::endl;

  return 0;
}
