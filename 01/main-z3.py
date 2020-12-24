import sys
from z3 import *

nums = [int(line) for line in sys.stdin.readlines()]
nums_c = len(nums)

s = Solver()

var = [Int(f"var_{i}") for i in range(nums_c)]

for_sum = []
for i in range(nums_c):
    for_sum.append(var[i] * nums[i])
    s.add(Or(var[i] == 0, var[i] == 1))

s.add(sum(for_sum) == 2020)
s.add(sum(var) == sys.argv[1])

if s.check() == unsat:
    print("unsat")
    exit(1)

m = s.model()

for i in range(nums_c):
    if m[var[i]] == 1:
        print(nums[i], end=" ")

print("")
