#include <iostream>
#include <iomanip>

int main() {
  int code_1, amount_1, code_2, amount_2;
  double price_1, price_2;

  std::cin >> code_1 >> amount_1 >> price_1;
  std::cin >> code_2 >> amount_2 >> price_2;

  double result = price_1 * amount_1 + price_2 * amount_2;
  std::cout << "VALOR A PAGAR: R$ " << std::fixed << std::setprecision(2) << result << std::endl;
}
