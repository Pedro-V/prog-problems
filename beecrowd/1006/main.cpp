#include <iostream>
#include <iomanip>

int main() {
  double a, b, c;
  std::cin >> a >> b >> c;
  double result = (2*a + 3*b + 5*c) / 10;
  std::cout << "MEDIA = " << std::fixed << std::setprecision(1) << result << std::endl;
}
