# Zadanie 3.1

## Fragment 1

```python
x = 2; y = 3;
if (x > y):
    result = x;
else:
    result = y;
```

Kod jest poprawny. Średniki i nawiasy w warunku są dozwolone,
ale nie są potrzebne.

## Fragment 2

```python
for i in "axby": if ord(i) < 100: print (i)
```

Kod jest niepoprawny składniowo: po dwukropku pętli w tej samej
linii nie można umieścić `if`. Potrzebne jest wcięcie.

## Fragment 3

```python
for i in "axby": print (ord(i) if ord(i) < 100 else i)
```

Kod jest poprawny: można wywołać funkcję w tej samej lini co `if`.
