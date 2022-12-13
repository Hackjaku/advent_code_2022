#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// #define COMMON_MULTIPLE 96577
#define COMMON_MULTIPLE 9699690

using namespace std;

struct Monkey {
public:
    int divisibility_test;
    vector<unsigned long long> items;
    int operation;

    Monkey* on_success; // throw to monkey if
    Monkey* on_failure;

    int items_inspected = 0;

    void throw_items();
    void receive_item(int);
    virtual void inspect_items() {};

    Monkey(vector<unsigned long long>, int, int, Monkey*, Monkey*);
    Monkey(vector<unsigned long long>, int, int);
};

struct CarelessMonkey : public Monkey {
    using Monkey::Monkey;
    void inspect_items();
};

struct CarefulMonkey : public Monkey {
    using Monkey::Monkey;
    void inspect_items();
};

int main() {

    vector<Monkey*> monkeys;

    // items, divisibility_test, operation, on_success, on_failure

    monkeys.push_back(new CarelessMonkey({ 56, 52, 58, 96, 70, 75, 72 }, 11, 17)); // 0
    monkeys.push_back(new CarefulMonkey({ 75, 58, 86, 80, 55, 81}, 3, 7)); // 1
    monkeys.push_back(new CarelessMonkey({ 73, 68, 73, 90 }, 5, 0)); // 2
    monkeys.push_back(new CarefulMonkey({ 72, 89, 55, 51, 59 }, 7, 1)); // 3
    monkeys.push_back(new CarelessMonkey({ 76, 76, 91 }, 19, 3, monkeys[0], monkeys[3])); // 4
    monkeys.push_back(new CarefulMonkey({ 88 }, 2, 4)); // 5
    monkeys.push_back(new CarefulMonkey({ 64, 63, 56, 50, 77, 55, 55, 86 }, 13, 8, monkeys[4], monkeys[0])); // 6
    monkeys.push_back(new CarefulMonkey({ 79, 58 }, 17, 6, monkeys[1], monkeys[5])); // 7

    monkeys[0]->on_success = monkeys[2];
    monkeys[0]->on_failure = monkeys[3];

    monkeys[1]->on_success = monkeys[6];
    monkeys[1]->on_failure = monkeys[5];

    monkeys[2]->on_success = monkeys[1];
    monkeys[2]->on_failure = monkeys[7];

    monkeys[3]->on_success = monkeys[2];
    monkeys[3]->on_failure = monkeys[7];

    monkeys[5]->on_success = monkeys[6];
    monkeys[5]->on_failure = monkeys[4];

    // monkeys.push_back(new CarelessMonkey({ 79, 98 }, 23, 19)); // 0
    // monkeys.push_back(new CarefulMonkey({ 54, 65, 75, 74 }, 19, 6)); // 1
    // monkeys.push_back(new CarelessMonkey({ 79, 60, 97 }, 13, 0)); // 2
    // monkeys.push_back(new CarefulMonkey({ 74 }, 17, 3)); // 3

    // monkeys[0]->on_success = monkeys[2];
    // monkeys[0]->on_failure = monkeys[3];

    // monkeys[1]->on_success = monkeys[2];
    // monkeys[1]->on_failure = monkeys[0];

    // monkeys[2]->on_success = monkeys[1];
    // monkeys[2]->on_failure = monkeys[3];

    // monkeys[3]->on_success = monkeys[0];
    // monkeys[3]->on_failure = monkeys[1];

    for (int round = 0; round < 10000; ++round) {
        // print round percentage
        cout << "\r" << fixed << setprecision(2) << (round / 10000.0) * 100 << "%";
        for (int i = 0; i < monkeys.size(); i++) {
            monkeys[i]->inspect_items();
            monkeys[i]->throw_items();
        }
    }

    cout << endl;

    for (int i = 0; i < monkeys.size(); i++) {
        cout << "Monkey " << i << " inspected " << monkeys[i]->items_inspected << " items." << endl;
    }

    return 0;
}

void CarelessMonkey::inspect_items() {
    for (int i = 0; i < items.size(); i++) {
        ++items_inspected;
        if (operation != 0) {
            items[i] = (items[i] * operation);
        } else {
            items[i] = (items[i] * items[i]); // extremely careless
        }
        while (items[i] > COMMON_MULTIPLE) {
            items[i] -= COMMON_MULTIPLE;
        }
    }
}

void CarefulMonkey::inspect_items() {
    for (int i = 0; i < items.size(); i++) {
        ++items_inspected;
        items[i] = (items[i] + operation);
        while (items[i] > COMMON_MULTIPLE) {
            items[i] -= COMMON_MULTIPLE;
        }
    }
}

void Monkey::throw_items() {
    for (int i = 0; i < items.size(); i++) {
        if (items[i] % divisibility_test == 0) {
            on_success->receive_item(items[i]);
        } else {
            on_failure->receive_item(items[i]);
        }
    }
    items.clear();
}

Monkey::Monkey(vector<unsigned long long> items, int divisibility_test, int operation, Monkey* on_success, Monkey* on_failure) {
    this->items = items;
    this->divisibility_test = divisibility_test;
    this->operation = operation;
    this->on_success = on_success;
    this->on_failure = on_failure;
}

Monkey::Monkey(vector<unsigned long long> items, int divisibility_test, int operation) {
    this->items = items;
    this->divisibility_test = divisibility_test;
    this->operation = operation;
}

void Monkey::receive_item(int item) {
    this->items.push_back(item);
}