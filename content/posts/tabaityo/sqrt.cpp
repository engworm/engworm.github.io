#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace boost::multiprecision;

constexpr int d = std::numeric_limits<double>::digits10;
constexpr int dd = std::numeric_limits<cpp_dec_float_100>::digits10;

int main() {
  cpp_dec_float_100 x("2");

  cpp_dec_float_100 dx = sqrt(x);
  cpp_dec_float_100 ddx = boost::multiprecision::sqrt(x);

  std::cout << std::setprecision(dd)
            << dx << std::endl;

  std::cout << std::setprecision(dd)
            << ddx << std::endl;
  return 0;
}
