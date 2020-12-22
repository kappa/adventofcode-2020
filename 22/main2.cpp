#include <deque>
#include <iostream>
#include <unordered_set>

using deck_t = std::deque<int>;

namespace std {
template <> struct hash<pair<deck_t, deck_t>> {
  std::size_t operator()(pair<deck_t, deck_t> const &dp) const noexcept {
    const deck_t &d1 = dp.first;
    const deck_t &d2 = dp.second;

    size_t seed = d1.size() + d2.size();
    for (int i : d1) {
      seed ^= hash<int>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    for (int i : d2) {
      seed ^= hash<int>()(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};
} // namespace std

// 1 or 2
int game(deck_t p1, deck_t p2, bool top) {
  std::unordered_set<std::pair<deck_t, deck_t>> states{};

  while (!p1.empty() && !p2.empty()) {
    int round_winner = 0;

    if (auto pair = std::make_pair(p1, p2); states.count(pair))
      return 1;
    else
      states.insert(pair);

    const int c1 = p1.front();
    p1.pop_front();
    const int c2 = p2.front();
    p2.pop_front();

    if (c1 > (int)p1.size() || c2 > (int)p2.size())
      round_winner = c1 > c2 ? 1 : 2;

    if (!round_winner) {
      deck_t sub_p1(p1.cbegin(), p1.cbegin() + c1);
      deck_t sub_p2(p2.cbegin(), p2.cbegin() + c2);
      round_winner = game(std::move(sub_p1), std::move(sub_p2), false);
    }

    if (round_winner == 1) {
      p1.push_back(c1);
      p1.push_back(c2);
    } else {
      p2.push_back(c2);
      p2.push_back(c1);
    }
  }

  int winner = p1.empty() ? 2 : 1;
  if (top) {
    const std::deque<int> &won = winner == 1 ? p1 : p2;

    int sum = 0;
    int coef = 1;
    for (auto al = won.crbegin(); al < won.crend(); ++al)
      sum += *al * coef++;

    std::cout << sum << std::endl;
  }

  return winner;
}

int main() {
  deck_t p1{};
  deck_t p2{};

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (std::string line; std::getline(std::cin, line) && !line.empty();)
    p1.push_back(std::stoi(line));

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (std::string line; std::getline(std::cin, line) && !line.empty();)
    p2.push_back(std::stoi(line));

  game(p1, p2, true);

  return 0;
}
