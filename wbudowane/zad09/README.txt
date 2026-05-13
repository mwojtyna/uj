Program wczytuje graf zadań w formacie używanym w poprzednich zadaniach:
@tasks, @proc, @times, @cost, @comm.

Uruchomienie:

./a.out plik_wejściowy k1 k2 k3 tmax fmax

Program konstruuje system zachłannie. Zadania są rozpatrywane w porządku
topologicznym. Dla aktualnego zadania wybierany jest lokalnie najtańszy procesor,
który może wykonać zadanie i dla którego po tej decyzji spełnione jest F <= fmax.

F(cost, t) = k1 * cost + k2 * t + k3 * kara
kara = max(0, t - tmax)

Koszt obejmuje:
- koszt wykonania przypisanych zadań,
- koszt użytych procesorów PP i HC,
- koszt podpięcia użytych procesorów do szyn, zgodnie z sekcją @comm.

Procesor PP może wykonywać wiele zadań sekwencyjnie. Procesor HC jest traktowany
jako dedykowany i może zostać przypisany tylko do jednego zadania.

Program wypisuje całkowity koszt, całkowity czas, karę, wartość F oraz przydział
zadań do procesorów.
