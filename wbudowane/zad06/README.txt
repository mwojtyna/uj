Algorytm rafinacyjny dla problemu kosyntezy systemów wbudowanych.

Program należy uruchomić z 2 argumentami oddzielonymi spacją:

- nazwa pliku wejściowego,
- ograniczenie czasowe.

Program wczytuje graf zadań w formacie używanym w poprzednich zadaniach (`@tasks`,
`@proc`, `@times`, `@cost`, `@comm`). Wagi krawędzi komunikacyjnych są ignorowane.

Algorytm:

1. Dla każdego zadania wybiera najszybszą dostępną implementację.
2. Liczy czas jako długość ścieżki krytycznej grafu zadań.
3. Dopóki można, wybiera najdroższą aktualną implementację zadania i próbuje zamienić ją
   na najszybszą spośród wolniejszych dostępnych implementacji.
4. Zmiana jest zatwierdzana tylko wtedy, gdy nowe rozwiązanie mieści się w ograniczeniu
   czasowym.

Koszt rozwiązania jest sumą kosztów wybranych implementacji z sekcji `@cost`.
