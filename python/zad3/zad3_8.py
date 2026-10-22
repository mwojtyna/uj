# Zadanie 3.8: część wspólna i suma dwóch sekwencji bez powtórzeń.
sequence1 = [1, 2, 2, 3, 5]
sequence2 = [3, 4, 4, 5, 6]

# Zachowujemy kolejność pierwszego wystąpienia elementów.
common = set()
for item in sequence1:
    if item in sequence2:
        common.add(item)

all_items = set()
for sequence in [sequence1, sequence2]:
    for item in sequence:
        if item not in all_items:
            all_items.add(item)

assert common == set([3, 5])
assert all_items == set([1, 2, 3, 5, 4, 6])
print(common)
print(all_items)
