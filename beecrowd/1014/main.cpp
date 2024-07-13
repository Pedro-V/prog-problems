#include <iostream>
#include <iomanip>

int main() {
  int dist;
  double fuel;

  std::cin >> dist >> fuel;
  std::cout << std::fixed << std::setprecision(3) << dist / fuel << " km/l" << std::endl;
}
