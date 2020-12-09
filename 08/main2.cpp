#include <iostream>
#include <unordered_set>
#include <vector>

struct instruction_t {
  std::string op;
  int arg;
};

std::vector<instruction_t> program{};

int run() {
  unsigned ip = 0;
  int acc = 0;
  std::unordered_set<unsigned> visited{};

  while(visited.count(ip) == 0) {
    const instruction_t cur = program[ip];

    if (cur.op == "acc") {
      acc += cur.arg;
    }
    else if (cur.op == "jmp") {
      ip += cur.arg - 1;
    }

    visited.insert(ip);
    if (++ip >= program.size())
      return acc;
  }

  // infinite loop
  return -1;
}

int main()
{

  std::string line;
  while(std::getline(std::cin, line))
    program.push_back(instruction_t{line.substr(0, 3), std::stoi(line.substr(4))});

  int acc = 0;

  for(auto &inst : program) {
    const std::string prev_op = inst.op;
    if (inst.op == "jmp")
      inst.op = "nop";
    else if (inst.op == "nop")
      inst.op = "jmp";

    if(acc = run(); acc > -1)
      break;

    inst.op = prev_op;
  }

  std::cout << acc << std::endl;

  return 0;
}
