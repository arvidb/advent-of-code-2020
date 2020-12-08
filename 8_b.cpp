#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <functional>

using namespace std;

struct Instruction {
    string op;
    int arg;
    bool exec = false;
};

struct Cpu {
    int ip = 0;
    int ack = 0;
    bool halt = false;
};

const unordered_map<string, function<void(Cpu&, Instruction&)>> operations = {
    {"nop", [](auto& cpu, auto& ins) { cpu.ip++; }},
    {"acc", [](auto& cpu, auto& ins) { cpu.ack += ins.arg; cpu.ip++; }},
    {"jmp", [](auto& cpu, auto& ins) { cpu.ip += ins.arg; }},
};

bool exec(Cpu& cpu, vector<Instruction> instructions, int jmp) {
    for (;;) {
        auto& ins = instructions[cpu.ip];
        if (cpu.ip == jmp) {
            ins.op = "nop";
        }

        if (!ins.exec) {
            ins.exec = true;
            operations.at(ins.op)(cpu, ins);
        } else {
            cpu.halt = true;
        }

        if (cpu.ip >= instructions.size() || cpu.ip < 0) {
            cout << cpu.ack << endl;
            return true;
        }

        if (cpu.halt) {
            return false;
        }
    }
}

Instruction getInstruction(const string& s) {
    int pos = s.find_first_of(' ');
    return {s.substr(0, pos), stoi(s.substr(pos+1))};
}

int main() {

    vector<Instruction> instructions;
    vector<int> jmps;
    for (string line; getline(cin, line);) {
        instructions.push_back(getInstruction(line));

        const auto& ins = instructions.back();
        if (ins.op == "jmp")
            jmps.push_back(instructions.size()-1);
    }

    bool exited = false;
    auto it = begin(jmps);
    while (!exited) {
        Cpu cpu;
        exited = exec(cpu, instructions, *it);
        it = next(it);
    }
}