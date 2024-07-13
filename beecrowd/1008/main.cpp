#include <iostream>
#include <iomanip>

int main() {
  int number, hours;
  double amount;
  std::cin >> number >> hours >> amount;
  double salary = hours * amount;
  std::cout << "NUMBER = " << number << '\n'
            << "SALARY = U$ " << std::fixed << std::setprecision(2) << salary << std::endl;
}
