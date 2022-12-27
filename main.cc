#include <iostream>
#include <fstream>
#include <string>

using namespace std;

using ll = long long;

int main()
{
    string line;
    fstream file("../inputs/25.txt", ios::in);
    ll toBeConv = 0;
    while (getline(file, line))
    {
        for (int i = line.size() - 1; i >= 0; i--)
        {
            char c = line.at(i);
            int val;
            if (c == '-')
            {
                val = -1;
            }
            else if (c == '=')
            {
                val = -2;
            }
            else
            {
                val = c - '0';
            }
            ll tmp = 1;
            for (int j = 0; j < line.size() - i - 1; j++)
            {
                tmp *= 5;
            }
            toBeConv += val * tmp;
        }
    }
    char chars[5] = {'=', '-', '0', '1', '2'};
    std::string res;
    while (toBeConv != 0)
    {
        ll pf = toBeConv + 2;
        toBeConv = pf / 5;
        res.insert(0, 1, chars[pf % 5]);
    }
    std::cout << "Part 1: " << res << std::endl;
}