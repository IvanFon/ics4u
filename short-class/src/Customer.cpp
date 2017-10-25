#include "Customer.hpp"

#include <iostream>
#include <string>

Customer::Customer(): name(""), age(0), money(0.0) { }
Customer::Customer(std::string name, int age, double money):
    name(name), age(age), money(money) { }

Customer::~Customer() {
    std::cout << "customer destructed" << std::endl;
}

std::string Customer::getName() {
    return name;
}
int Customer::getAge() {
    return age;
}
double Customer::getMoney() {
    return money;
}

void Customer::setName(std::string &newName) {
    name = newName;
}
void Customer::setAge(int newAge) {
    age = newAge;
}
void Customer::setMoney(double newMoney) {
    money = newMoney;
}

void Customer::spendMoney(int amount) {
    money -= amount;
}
void Customer::earnMoney(int amount) {
    money += amount;
}
void Customer::stealMoney(Customer &other) {
    money += other.money;
    other.money = 0;
}
void Customer::printInfo() {
    std::cout << "Name: " << name << " Age: " << age
        << " Money: " << money << std::endl;
}
