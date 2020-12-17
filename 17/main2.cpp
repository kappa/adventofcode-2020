#include <array>
#include <iostream>
#include <set>

using coords = std::array<int, 4>;

std::array<std::set<coords>, 2> cubes;

int neighbors(const int x, const int y, const int z, const int w,
              const std::set<coords> *cube) {
  int rv = 0;
  for (auto ww = w - 1; ww <= w + 1; ++ww)
    for (auto zz = z - 1; zz <= z + 1; ++zz)
      for (auto yy = y - 1; yy <= y + 1; ++yy)
        for (auto xx = x - 1; xx <= x + 1; ++xx) {
          if (!(zz == z && yy == y && xx == x && ww == w) &&
              (*cube).count(coords{{xx, yy, zz, ww}}))
            ++rv;
        };

  return rv;
}

int main() {
  int max_x = 0, min_x = 0, max_y, min_y = 0, max_z = 0, min_z = 0, max_w = 0,
      min_w = 0;

  int ly = 0;
  for (std::string line; std::getline(std::cin, line); ++ly) {
    int x = 0;
    for (auto c : line) {
      if (c == '#')
        cubes[0].insert(coords{{x, ly, 0, 0}});
      ++x;
    }
    max_x = x;
  }
  max_y = ly;

  int cur_cube = 0, next_cube = 1;

  for (auto gen = 0; gen < 6; ++gen) {
    cubes[next_cube].clear();
    for (auto w = min_w - 1; w <= max_w + 1; ++w)
      for (auto z = min_z - 1; z <= max_z + 1; ++z)
        for (auto y = min_y - 1; y <= max_y + 1; ++y)
          for (auto x = min_x - 1; x <= max_x + 1; ++x) {
            const auto me = coords{{x, y, z, w}};
            const auto n = neighbors(x, y, z, w, &cubes[cur_cube]);

            if (cubes[cur_cube].count(me)) {
              if (n == 2 || n == 3)
                cubes[next_cube].insert(me);
            } else if (n == 3)
              cubes[next_cube].insert(me);
          }
    std::swap(cur_cube, next_cube);

    for (auto c : cubes[cur_cube]) {
      min_x = std::min(min_x, c[0]);
      min_y = std::min(min_y, c[1]);
      min_z = std::min(min_z, c[2]);
      min_w = std::min(min_w, c[2]);
      max_x = std::max(max_x, c[0]);
      max_y = std::max(max_y, c[1]);
      max_z = std::max(max_z, c[2]);
      max_w = std::max(max_w, c[2]);
    }
  }

  std::cout << cubes[cur_cube].size() << std::endl;

  return 0;
}
