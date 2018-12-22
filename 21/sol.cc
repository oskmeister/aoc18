#include <iostream>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;

struct Instr {
    string op;
    int p1, p2, r;
};

const bool print = false;

int main() {
    set<int> seen;
    int bind_ip;
    scanf("#ip %d\n", &bind_ip);
    vector<int> registers = {0,0,0,0,0,0};
    vector<Instr> instrs;
    {
        string op;
        int p1, p2, r;
        while (cin >> op >> p1 >> p2 >> r) {
            Instr i;
            i.op = op;
            i.p1 = p1;
            i.p2 = p2;
            i.r = r;
            instrs.push_back(i);
        }
    }
    int ip = 0;
    int lastval;
    for (;;) {
        if (print) {
            cout << "ip = " << ip << endl;
            for (int i = 0; i < 6; ++i) {
                cout << registers[i] << " ";
            }
            cout << endl;
        }
        if (ip < 0 || ip >= instrs.size()) break;
        registers[bind_ip] = ip;
        if (ip == 28) {
            int val = registers[3];
            if (seen.find(val) != seen.end()) {
                cout << lastval << endl;
                return 0;
            }
            seen.insert(val);
            lastval = val;
        }
        Instr &i = instrs[ip];
        string op = i.op;
        int p1 = i.p1;
        int p2 = i.p2;
        int r = i.r;
        if (op == "addr") {
            registers[r] = registers[p1] + registers[p2];
        }
        else if (op == "addi") {
            registers[r] = registers[p1] + p2;
        }
        else if (op == "mulr") {
            registers[r] = registers[p1] * registers[p2];
        }
        else if (op == "muli") {
            registers[r] = registers[p1] * p2;
        }
        else if (op == "banr") {
            registers[r] = registers[p1] & registers[p2];
        }
        else if (op == "bani") {
            registers[r] = registers[p1] & p2;
        }
        else if (op == "borr") {
            registers[r] = registers[p1] | registers[p2];
        }
        else if (op == "bori") {
            registers[r] = registers[p1] | p2;
        }
        else if (op == "setr") {
            registers[r] = registers[p1];
        }
        else if (op == "seti") {
            registers[r] = p1;
        }
        else if (op == "gtir") {
            registers[r] = (p1 > registers[p2] ? 1 : 0);
        }
        else if (op == "gtri") {
            registers[r] = (registers[p1] > p2 ? 1 : 0);
        }
        else if (op == "gtrr") {
            registers[r] = (registers[p1] > registers[p2] ? 1 : 0);
        }
        else if (op == "eqir") {
            registers[r] = (p1 == registers[p2] ? 1 : 0);
        }
        else if (op == "eqri") {
            registers[r] = (registers[p1] == p2 ? 1 : 0);
        }
        else if (op == "eqrr") {
            registers[r] = (registers[p1] == registers[p2] ? 1 : 0);
        }
        else assert(false);
        ip = registers[bind_ip];
        ++ip;

    }
    cout << endl;
    cout << registers[0] << endl;
}
