# Zadanie 3.2

## Fragment 1

```python
L = [3, 5, 4]; L = L.sort()
```

`sort()` zmienia listę w miejscu i zwraca `None`, więc przypisanie usuwa
z `L` odwołanie do listy.

## Fragment 2

```python
x, y = 1, 2, 3
```

`ValueError`: trzy wartości nie pasują do dwóch zmiennych.

Poprawiony przykład:

```python
x, y, z = 1, 2, 3
assert (x, y, z) == (1, 2, 3)
print(x, y, z)
```

## Fragment 3

```python
X = 1, 2, 3; X[1] = 4
```

`TypeError`: `tuple` jest niezmienne. Do modyfikacji można użyć listy.

Poprawiony przykład:

```python
X = [1, 2, 3]
X[1] = 4
```

## Fragment 4

```python
X = [1, 2, 3]; X[3] = 4
```

`IndexError`: lista ma indeksy 0, 1, 2. Nowy element dodajemy przez `append()`.

## Fragment 5

```python
X = "abc"; X.append("d")
```

`AttributeError`: napis nie ma metody `append()` i jest niezmienny.

Poprawiony przykład:

```python
X = "abc"
X += "d"
```

## Fragment 6

```python
L = list(map(pow, range(8)))
```

`TypeError`: `pow()` wymaga podstawy i wykładnika, a `map()` przekazuje tu
tylko podstawę.
