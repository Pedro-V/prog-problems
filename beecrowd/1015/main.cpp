#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
  double x1, x2, y1, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;

  std::cout << std::fixed << std::setprecision(4) <<
               std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)) << std::endl;
}
