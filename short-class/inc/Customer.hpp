#ifndef INC_CUSTOMER_HPP_
#define INC_CUSTOMER_HPP_

#include <string>

class Customer {
private:
    std::string name;
    int age;
    std::string address;
    double money;
public:
    // Default constructor
    Customer();
    // Other constructor
    Customer(std::string name, int age, double money);

    // Destructor
    ~Customer();

    // Accessors
    std::string getName();
    int getAge();
    double getMoney();

    // Mutators
    void setName(std::string &newName);
    void setAge(int newAge);
    void setMoney(double newMoney);

    // Other
    // Spend money
    void spendMoney(int amount);
    // Earn money
    void earnMoney(int amount);
    // Steal money from another customer
    void stealMoney(Customer &other);
    // Print customer info
    void printInfo();
};

#endif  // INC_CUSTOMER_HPP_
