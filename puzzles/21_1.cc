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
    fstream data("../inputs/21.txt", ios::in);
    
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
    cout << fixed << std::setprecision(0) << root->get_number() << endl;

    return 0;
}

Monkey::Monkey(string name, double number) {
    this->name = name;
    this->number = number;
    this->first_operand = NULL;
    this->second_operand = NULL;
    this->operation = NOP;
}

Monkey::Monkey(string name, Monkey* first_operand, Monkey* second_operand, Operation operation) {
    this->name = name;
    this->number = 0;
    this->first_operand = first_operand;
    this->second_operand = second_operand;
    this->operation = operation;
}

Monkey::Monkey(string name) {
    this->name = name;
    this->number = 0;
    this->first_operand = NULL;
    this->second_operand = NULL;
    this->operation = NOP;
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
    if (this->operation == NOP) {
        return this->number;
    } else {
        double first = this->first_operand->get_number();
        double second = this->second_operand->get_number();
        switch (this->operation) {
            case ADD:
                return first + second;
            case SUB:
                return first - second;
            case MUL:
                return first * second;
            case DIV:
                return first / second;
        }
    }
    cout << "ERROR: " << this->name << endl;
    return this->number; // Should never get here
}

Operation Monkey::get_operation() {
    return this->operation;
}