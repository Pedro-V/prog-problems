#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
  int radius;
  double volume, pi = 3.14159;

  std::cin >> radius;
  volume = 4/3.0 * pi * pow(radius, 3);

  std::cout << "VOLUME = " << std::fixed << std::setprecision(3) << volume << std::endl;
}
