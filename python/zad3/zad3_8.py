# Zadanie 3.8: część wspólna i suma dwóch sekwencji bez powtórzeń.
sequence1 = [1, 2, 2, 3, 5]
sequence2 = [3, 4, 4, 5, 6]

common = set()
for item in sequence1:
    if item in sequence2:
        common.add(item)

all_items = set()
for sequence in [sequence1, sequence2]:
    for item in sequence:
        if item not in all_items:
            all_items.add(item)

common = list(common)
all_items = list(all_items)

assert common == [3, 5]
assert all_items == [1, 2, 3, 4, 5, 6]
print(common)
print(all_items)
