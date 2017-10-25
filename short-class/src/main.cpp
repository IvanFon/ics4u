#include <iostream>

#include "Customer.hpp"

int main() {
    Customer a("Bob", 20, 20.0);
    Customer b("Joe", 25, 100.0);
    a.printInfo();
    b.printInfo();

    std::cout << std::endl << "Giving Bob $10" << std::endl;
    a.earnMoney(10.0);
    a.printInfo();

    std::cout << std::endl << "Joe spending $20" << std::endl;
    b.spendMoney(20.0);
    b.printInfo();

    std::cout << std::endl << "Joe stealing Bob's money" << std::endl;
    b.stealMoney(a);
    a.printInfo();
    b.printInfo();

    return 0;
}
