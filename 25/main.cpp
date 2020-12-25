#include <iostream>
#include <iterator>

int main() {
  auto icin = std::istream_iterator<uint64_t>(std::cin);
  const auto door_pk = *icin++, card_pk = *icin;

  uint64_t key = 1;
  for (uint64_t card_num = 1; card_num != card_pk;) {
    card_num = card_num * 7 % 20201227;
    key = key * door_pk % 20201227;
  }

  std::cout << key << std::endl;

  return 0;
}
