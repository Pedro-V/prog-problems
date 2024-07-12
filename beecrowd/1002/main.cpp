#include <iostream>
#include <iomanip>

int main() {
  double r, pi = 3.14159;
  std::cin >> r;
  std::cout << "A=" << std::fixed << std::setprecision(4) << pi * r * r << std::endl;
}
