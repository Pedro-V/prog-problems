#include <iostream>
#include <iomanip>

int main() {
  double a, b;
  std::cin >> a >> b;
  double result = (a * 3.5 + b * 7.5) / (3.5 + 7.5);
  std::cout << "MEDIA = " << std::fixed << std::setprecision(5) << result << std::endl;
}

