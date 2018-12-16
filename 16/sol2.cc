#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

enum class Instruction {
    ADDR, ADDI, MULR, MULI, BANR, BANI, BORR, BORI, SETR, SETI, GTIR, GTRI, GTRR, EQIR, EQRI, EQRR
};

vector<Instruction> count(const vector<int> &before, const vector<int> &after, int opcode, int p1, int p2, int r) {
    vector<Instruction> ret;
    {
        int val1 = before[p1];
        int val2 = before[p2];
        int res = after[r];
        if (val1 + val2 == res) {
            ret.push_back(Instruction::ADDR);
        }
        if (val1 * val2 == res) {
            ret.push_back(Instruction::MULR);
        }
        if ((val1 | val2) == res) {
            ret.push_back(Instruction::BORR);
        }
        if ((val1 & val2) == res) {
            ret.push_back(Instruction::BANR);
        }
        if (val1 == res) {
            ret.push_back(Instruction::SETR);
        }
    }
    {
        int val1 = before[p1];
        int val2 = p2;
        int res = after[r];
        if (val1 + val2 == res) {
            ret.push_back(Instruction::ADDI);
        }
        if (val1 * val2 == res) {
            ret.push_back(Instruction::MULI);
        }
        if ((val1 | val2) == res) {
            ret.push_back(Instruction::BORI);
        }
        if ((val1 & val2) == res) {
            ret.push_back(Instruction::BANI);
        }
        val1 = p1;
        if (val1 == res) {
            ret.push_back(Instruction::SETI);
        }
    }
    // ir
    if (p2 >= 0 && p2 < 4) {
        int val1 = p1;
        int val2 = before[p2];
        int res = after[r];
        if (((val1 > val2) ? 1 : 0) == res) {
            ret.push_back(Instruction::GTIR);
        }
        if (((val1 == val2) ? 1 : 0) == res) {
            ret.push_back(Instruction::EQIR);
        }
    }
    // ri
    if (p1 >= 0 && p1 < 4) {
        int val1 = before[p1];
        int val2 = p2;
        int res = after[r];
        if (((val1 > val2) ? 1 : 0) == res) {
            ret.push_back(Instruction::GTRI);
        }
        if (((val1 == val2) ? 1 : 0) == res) {
            ret.push_back(Instruction::EQRI);
        }
    }
    // rr
    if (p1 >= 0 && p1 < 4 && p2 >= 0 && p2 < 4) {
        int val1 = before[p1];
        int val2 = before[p2];
        int res = after[r];
        if (((val1 > val2) ? 1 : 0) == res) {
            ret.push_back(Instruction::GTRR);
        }
        if (((val1 == val2) ? 1 : 0) == res) {
            ret.push_back(Instruction::EQRR);
        }
    }
    return ret;
}

int main() {
    int a,b,c,d;
    int opcode, p1, p2, r;
    int ap, bp, cp, dp;
    map<int, set<int>> m;
    while (scanf("Before: [%d, %d, %d, %d]\n", &a, &b, &c, &d) == 4) {
        scanf("%d %d %d %d\n", &opcode, &p1, &p2, &r);
        scanf("After: [%d, %d, %d, %d]\n", &ap, &bp, &cp, &dp);
        vector<int> before = {a,b,c,d};
        vector<int> after = {ap,bp,cp,dp};
        auto poss = count(before, after, opcode, p1, p2, r);
        for (auto p : poss) {
            int val = static_cast<std::underlying_type<Instruction>::type>(p);
            m[opcode].insert(val);
        }
    }

    vector<int> ans(16, -1);
    vector<int> instrs(16, -1);
    for (;;) {
        bool ok = false;
        for (auto &p : m) {
            if (p.second.size() == 1) {
                int val = *p.second.begin();
                if (ans[p.first] != -1) assert(ans[p.first] == val);
                ans[p.first] = val;
                instrs[val] = p.first;
                ok = true;
            }
        }
        auto itm = m.begin();
        while (itm != m.end()) {
            if (ans[itm->first] != -1) itm = m.erase(itm);
            else itm++;
        }
        for (auto &p : m) {
            auto &s = p.second;
            auto it = s.begin();
            while (it != s.end()) {
                if (instrs[*it] != -1) {
                    it = s.erase(it);
                } else {
                    ++it;
                }
            }
        }
        if (!ok) break;
    }

    vector<string> names = {"ADDR", "ADDI", "MULR", "MULI", "BANR", "BANI", "BORR", "BORI", "SETR", "SETI", "GTIR", "GTRI", "GTRR", "EQIR", "EQRI", "EQRR"};
    vector<int> registers = {0, 0, 0, 0};

    while (cin >> opcode >> p1 >> p2 >> r) {
        string op = names[ans[opcode]];
        if (op == "ADDR") {
            registers[r] = registers[p1] + registers[p2];
        }
        else if (op == "ADDI") {
            registers[r] = registers[p1] + p2;
        }
        else if (op == "MULR") {
            registers[r] = registers[p1] * registers[p2];
        }
        else if (op == "MULI") {
            registers[r] = registers[p1] * p2;
        }
        else if (op == "BANR") {
            registers[r] = registers[p1] & registers[p2];
        }
        else if (op == "BANI") {
            registers[r] = registers[p1] & p2;
        }
        else if (op == "BORR") {
            registers[r] = registers[p1] | registers[p2];
        }
        else if (op == "BORI") {
            registers[r] = registers[p1] | p2;
        }
        else if (op == "SETR") {
            registers[r] = registers[p1];
        }
        else if (op == "SETI") {
            registers[r] = p1;
        }
        else if (op == "GTIR") {
            registers[r] = (p1 > registers[p2] ? 1 : 0);
        }
        else if (op == "GTRI") {
            registers[r] = (registers[p1] > p2 ? 1 : 0);
        }
        else if (op == "GTRR") {
            registers[r] = (registers[p1] > registers[p2] ? 1 : 0);
        }
        else if (op == "EQIR") {
            registers[r] = (p1 == registers[p2] ? 1 : 0);
        }
        else if (op == "EQRI") {
            registers[r] = (registers[p1] == p2 ? 1 : 0);
        }
        else if (op == "EQRR") {
            registers[r] = (registers[p1] == registers[p2] ? 1 : 0);
        }
        else assert(false);
    }
    cout << registers[0] << endl;
}
