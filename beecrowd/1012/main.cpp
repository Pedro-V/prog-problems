#include <iostream>
#include <iomanip>

int main() {
  double a, b, c, pi = 3.14159;
  std::cin >> a >> b >> c;

  std::cout << std::fixed << std::setprecision(3)
            << "TRIANGULO: " << a * c / 2.0 << '\n'
            << "CIRCULO: " << pi * c * c << '\n'
            << "TRAPEZIO: " << (a + b) * c/2 << '\n'
            << "QUADRADO: " << b * b << '\n'
            << "RETANGULO: " << a * b << std::endl;
}
