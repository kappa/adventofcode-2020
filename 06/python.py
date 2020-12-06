import sys

#%%
with open(sys.argv[1], 'r') as f:
    data = f.read()

# %%
raw = data.split('\n\n')
answers = list(map(lambda x: [set(i) for i in x.split('\n') if i != ''], raw))

# %%
### part 1
n_unique = map(lambda x: len(set.union(*x)), answers)
print(sum(n_unique))

# %%
### part 2
n_intersect = map(lambda x: len(set.intersection(*x)), answers)
print(sum(n_intersect))
