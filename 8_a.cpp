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

void exec(Cpu& cpu, vector<Instruction>& instructions) {
    for (;;) {
        auto& ins = instructions[cpu.ip];

        if (!ins.exec) {
            ins.exec = true;
            operations.at(ins.op)(cpu, ins);
        } else {
            cpu.halt = true;
        }

        if (cpu.halt) {
            cout << cpu.ack << endl;
            return;
        }
    }
}

Instruction getInstruction(const string& s) {
    int pos = s.find_first_of(' ');
    return {s.substr(0, pos), stoi(s.substr(pos+1))};
}
int main() {

    vector<Instruction> instructions;
    for (string line; getline(cin, line);) {
        instructions.push_back(getInstruction(line));
    }

    Cpu cpu;
    exec(cpu, instructions);
}