#include <iostream>
#include <set>
#include <vector>

struct instruction_t {
  std::string op;
  int arg;
};

int main() {
  std::vector<instruction_t> program{};

  for (std::string line; std::getline(std::cin, line);)
    program.push_back(
        instruction_t{line.substr(0, 3), std::stoi(line.substr(4))});

  unsigned ip = 0;
  int acc = 0;
  std::set<unsigned> visited{};

  while (visited.count(ip) == 0) {
    const instruction_t cur = program[ip];

    if (cur.op == "acc")
      acc += cur.arg;
    else if (cur.op == "jmp")
      ip += cur.arg - 1;

    visited.insert(ip);
    ++ip;
  }

  std::cout << acc << std::endl;

  return 0;
}
