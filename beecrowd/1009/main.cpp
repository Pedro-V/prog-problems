#include <iostream>
#include <string>
#include <iomanip>

int main() {
  std::string name;
  std::getline(std::cin, name);

  double fixed, sales, total;
  std::cin >> fixed >> sales;

  total = fixed + (0.15 * sales);

  std::cout << "TOTAL = R$ " << std::fixed << std::setprecision(2) << total << std::endl;
}
