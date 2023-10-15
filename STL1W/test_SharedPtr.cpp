#include <cstdio>
#include <vector>
#include <iostream>
#include "SharedPtr1st.h"

struct MyClass {
    int a, b, c;
};

struct Animal {
    virtual void speak() = 0;
    virtual ~Animal() = default;
};

struct Dog : Animal {
    int age;

    Dog(int age_) : age(age_) {
    }

    virtual void speak() {
        printf("Bark! I'm %d Year Old!\n", age);
    }
};

struct Cat : Animal {
    int &age;

    Cat(int &age_) : age(age_) {
    }

    virtual void speak() {
        printf("Meow! I'm %d Year Old!\n", age);
    }
};

int main() {
    std::vector<SharedPtr1st<Animal>> zoo;
    int age = 3;
    zoo.push_back(makeShared<Cat>(age));
    zoo.push_back(makeShared<Dog>(age));
    for (auto const &a: zoo) {
        a->speak();
    }
    age++;
    for (auto const &a: zoo) {
        a->speak();
    }
    return 0;
}