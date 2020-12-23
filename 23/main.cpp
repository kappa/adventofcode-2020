#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <iterator>

std::size_t inc(const std::size_t cur, std::deque<int> &ring,
                const std::size_t delta = 1) {
  return (cur + delta) % ring.size();
}

constexpr int dec_v(const int v, const int delta = 1) {
  return (v - 1 + 9 - delta) % 9 + 1;
}

std::size_t erase3(std::deque<int> &ring, const std::size_t pos) {
  const std::size_t size = ring.size();
  if (size - pos > 3) {
    ring.erase(ring.begin() + pos, ring.begin() + pos + 3);
    return pos;
  } else {
    ring.erase(ring.begin() + pos, ring.end());
    ring.erase(ring.begin(), ring.begin() + 3 - (size - ring.size()));
    return 0;
  }
}

int main() {
  std::deque<int> ring = {7, 9, 2, 8, 4, 5, 1, 3, 6};

  std::size_t cur = 0;
  for (auto t = 0; t < 100; ++t) {
    const std::array<int, 3> three = {{ring[inc(cur, ring)], ring[inc(cur, ring, 2)],
                                 ring[inc(cur, ring, 3)]}};

    int dest_v = dec_v(ring[cur]);
    std::size_t dest = inc(cur, ring);
    while (ring[dest] != dest_v ||
           (ring.size() + dest - cur) % ring.size() <= 3) {
      if (ring[dest] == dest_v)
        dest_v = dec_v(dest_v);
      dest = inc(dest, ring);
    }
    dest = inc(dest, ring);

    ring.insert(ring.begin() + dest, three.cbegin(), three.cend());

    if (dest <= cur)
      cur = inc(cur, ring, 3);

    cur = erase3(ring, inc(cur, ring));
  }

  auto it = std::find(ring.cbegin(), ring.cend(), 1);
  std::advance(it, 1);
  if (it == ring.cend())
    it = ring.cbegin();
  while (*it != 1) {
    std::cout << *it;

    std::advance(it, 1);
    if (it == ring.cend())
      it = ring.cbegin();
  }
  std::cout << std::endl;

  return 0;
}
