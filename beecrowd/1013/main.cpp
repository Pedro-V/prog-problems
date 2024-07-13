#include <iostream>
#include <cmath>

#define max(a, b) ((a + b + abs(a - b)) / 2)

int main() {
  int a, b, c;
  std::cin >> a >> b >> c;

  std::cout << max(a, max(b, c)) << " eh o maior" << std::endl;
}
