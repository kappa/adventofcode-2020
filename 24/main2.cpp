#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

typedef std::pair<int, int> tile_t;

std::vector<tile_t> neighbors(const tile_t &tile, const bool add_self) {
  std::vector<std::pair<int, int>> rv{};

  if (add_self)
    rv.push_back(tile);

  rv.push_back(std::make_pair(tile.first, tile.second + 1));
  rv.push_back(std::make_pair(tile.first - 1, tile.second - 1));
  rv.push_back(std::make_pair(tile.first + 1, tile.second + 1));
  rv.push_back(std::make_pair(tile.first + 1, tile.second));
  rv.push_back(std::make_pair(tile.first - 1, tile.second));
  rv.push_back(std::make_pair(tile.first, tile.second - 1));

  return rv;
}

int main() {
  std::set<tile_t> grid{};
  std::set<tile_t> prev{};

  for (std::string line; std::getline(std::cin, line);) {
    int x = 0, y = 0;
    for (std::size_t i = 0; i < line.length(); ++i) {
      if (line[i] == 's') {
        if (line[++i] == 'e')
          ++x;
        else
          --y;
      } else if (line[i] == 'n') {
        if (line[++i] == 'e')
          ++y;
        else
          --x;
      } else if (line[i] == 'e') {
        ++x;
        ++y;
      } else {
        --y;
        --x;
      }
    }
    const auto cc = std::make_pair(x, y);
    if (grid.count(cc)) {
      grid.erase(cc);
    } else {
      grid.insert(cc);
    }
  }

  for (auto t = 1; t <= 100; ++t) {
    prev = grid;
    grid.clear();

    for (const auto &black_tile : prev) {
      for (const auto &any_tile : neighbors(black_tile, true)) {
        int count = 0;
        for (const auto &n : neighbors(any_tile, false)) {
          if (prev.count(n))
            ++count;
        }

        if (prev.count(any_tile) && (count == 1 || count == 2))
          grid.insert(any_tile);
        else if (!prev.count(any_tile) && count == 2)
          grid.insert(any_tile);
      }
    }

    std::cout << "Day " << t << ": " << grid.size() << std::endl;
  }

  return 0;
}
