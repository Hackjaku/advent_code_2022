#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <iomanip>


using namespace std;

enum Operation {
    NOP = -1,
    ADD = 0,
    SUB = 1,
    MUL = 2,
    DIV = 3
};

class Monkey {
private:
    double number;
    string name;
    Monkey* first_operand;
    Monkey* second_operand;
    Operation operation;
    double should_be;
    bool calculated;
public:
    Monkey(string, double);
    Monkey(string, Monkey*, Monkey*, Operation);
    Monkey(string);

    void set_number(double);
    void set_operation(Operation);
    void set_operands(Monkey*, Monkey*);
    double get_number();
    string get_name();
    Operation get_operation();
    double get_first_operand_value();
    double get_second_operand_value();
    bool branch_contains(Monkey*);
    void exec(double, Monkey*);
    Monkey* get_first_operand();
    Monkey* get_second_operand();
};

Monkey* get_monkey(vector<Monkey*> monkeys, string name) {
    for (int i = 0; i < monkeys.size(); i++) {
        if (monkeys[i]->get_name() == name) {
            return monkeys[i];
        }
    }
    return NULL;
}

int main() {
    // fstream data("../inputs/21.txt", ios::in);
    fstream data("../inputs/21_true.txt", ios::in);
    
    string line;

    vector<Monkey*> monkeys;

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        vector<string> sectors;
        boost::split(sectors, line, boost::is_any_of(": "), boost::token_compress_on);

        if (sectors.size() == 2) {
            Monkey* monkey = new Monkey(sectors[0], stod(sectors[1]));
            monkeys.push_back(monkey);
        } else if (sectors.size() == 4) {
            Monkey* monkey = new Monkey(sectors[0]);
            monkeys.push_back(monkey);
        }
    }

    // read input again
    data.clear();
    data.seekg(0, ios::beg);

    while(getline(data, line)) {
        std::istringstream iss(line);
        string s;

        if (!(iss >> s)) { 
            break;
        }

        vector<string> sectors;
        boost::split(sectors, line, boost::is_any_of(": "), boost::token_compress_on);

        if (sectors.size() == 2) {
            continue;
        } else if (sectors.size() == 4) {
            Operation op;
            if (sectors[2] == "+") {
                op = ADD;
            } else if (sectors[2] == "-") {
                op = SUB;
            } else if (sectors[2] == "*") {
                op = MUL;
            } else if (sectors[2] == "/") {
                op = DIV;
            }
            get_monkey(monkeys, sectors[0])->set_operation(op);
            get_monkey(monkeys, sectors[0])->set_operands(get_monkey(monkeys, sectors[1]), get_monkey(monkeys, sectors[3]));
        }
    }

    Monkey* root = get_monkey(monkeys, "root");
    Monkey* me = get_monkey(monkeys, "humn");
    me->set_number(0);
    double target = root->get_second_operand_value(); // i checked manually that the second branch was the one with the target
    // just change the humn to something random and see which one changes value
    Monkey* branch = root->get_first_operand();
    branch->exec(target, me);

    cout << setprecision(2) << fixed;

    cout << root->get_first_operand_value() << endl;
    cout << root->get_second_operand_value() << endl;

    cout << "ME: ";

    cout << me->get_number() << endl;
    

    return 0;
}

Monkey::Monkey(string name, double number) {
    this->name = name;
    this->number = number;
    this->first_operand = NULL;
    this->second_operand = NULL;
    this->operation = NOP;
    this->calculated = true;
}

Monkey::Monkey(string name, Monkey* first_operand, Monkey* second_operand, Operation operation) {
    this->name = name;
    this->number = 0;
    this->first_operand = first_operand;
    this->second_operand = second_operand;
    this->operation = operation;
    this->calculated = false;
}

Monkey::Monkey(string name) {
    this->name = name;
    this->number = 0;
    this->first_operand = NULL;
    this->second_operand = NULL;
    this->operation = NOP;
    this->calculated = false;
}

void Monkey::set_number(double number) {
    this->number = number;
}

void Monkey::set_operation(Operation operation) {
    this->operation = operation;
}

void Monkey::set_operands(Monkey* first_operand, Monkey* second_operand) {
    this->first_operand = first_operand;
    this->second_operand = second_operand;
}

string Monkey::get_name() {
    return this->name;
}

double Monkey::get_number() {
    if (this->operation == NOP || this->calculated) {
        return this->number;
    } else {
        double first = this->first_operand->get_number();
        double second = this->second_operand->get_number();
        switch (this->operation) {
            case ADD:
                this->number = first + second;
                this->calculated = true;
                return this->number;
            case SUB:
                this->number = first - second;
                this->calculated = true;
                return this->number;
            case MUL:
                this->number = first * second;
                this->calculated = true;
                return this->number;
            case DIV:
                this->number = first / second;
                this->calculated = true;
                return this->number;
        }
    }
    cout << "ERROR: " << this->name << endl;
    return this->number; // Should never get here
}

Operation Monkey::get_operation() {
    return this->operation;
}

double Monkey::get_first_operand_value() {
    return this->first_operand->get_number();
}

double Monkey::get_second_operand_value() {
    return this->second_operand->get_number();
}

bool Monkey::branch_contains(Monkey* monkey) {
    if (this == monkey || this->first_operand == monkey || this->second_operand == monkey) {
        return true;
    } else {
        if (this->first_operand != NULL) {
            if (this->first_operand->branch_contains(monkey)) {
                return true;
            }
        }
        if (this->second_operand != NULL) {
            if (this->second_operand->branch_contains(monkey)) {
                return true;
            }
        }
    }
    return false;
}

void Monkey::exec(double expected_value, Monkey* me) {
    if (this == me) {
        this->number = expected_value;
        return;
    }
    if (this->first_operand == nullptr || this->second_operand == nullptr) {
        cout << "ERROR: " << this->name << endl;
        return;
    }
    bool first_contains_me = this->first_operand->branch_contains(me);
    Monkey* to_be_set;
    Monkey* to_be_used;
    if (first_contains_me) {
        to_be_set = this->first_operand;
        to_be_used = this->second_operand;
    } else {
        to_be_set = this->second_operand;
        to_be_used = this->first_operand;
    }
    switch (this->operation) {
        case ADD:
            to_be_set->exec(expected_value - to_be_used->get_number(), me);
            break;
        case SUB:
            if (first_contains_me)
                to_be_set->exec(expected_value + to_be_used->get_number(), me);
            else
                to_be_set->exec(to_be_used->get_number() - expected_value, me);
            break;
        case MUL:
            to_be_set->exec(expected_value / to_be_used->get_number(), me);
            break;
        case DIV:
            if (first_contains_me)
                to_be_set->exec(expected_value * to_be_used->get_number(), me);
            else
                to_be_set->exec(to_be_used->get_number() / expected_value, me);
            break;
        case NOP:
            this->number = expected_value;
            break;
    }
}

Monkey* Monkey::get_first_operand() {
    return this->first_operand;
}

Monkey* Monkey::get_second_operand() {
    return this->second_operand;
}