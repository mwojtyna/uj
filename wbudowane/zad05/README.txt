Program rozwiązuje problem kosyntezy systemów wbudowanych losowym algorytmem
konstrukcyjnym.

Uruchomienie:

./program plik_wejściowy ograniczenie_czasowe [ziarno] [liczba_prób]

Format wejścia jest taki jak w poprzednich zadaniach:
@tasks, @proc, @times, @cost, @comm.

Algorytm:
1. Zadania są rozpatrywane w porządku topologicznym.
2. Dla aktualnego zadania budowana jest lista dopuszczalnych zasobów:
   - nowo alokowany procesor HC lub PP,
   - wcześniej alokowany procesor PP jako zasób uniwersalny.
3. Z listy zostają tylko procesory, dla których po tym przydziale całkowity czas
   harmonogramu nie przekracza ograniczenia czasowego.
4. Jeden procesor z listy jest wybierany losowo.
5. Jeśli lista jest pusta, konstrukcja jest przerywana i rozpoczynana od nowa.

Procesor HC jest dedykowany i może zostać użyty tylko dla jednego zadania.
Procesor PP może wykonywać wiele zadań sekwencyjnie. Etykiety krawędzi są
traktowane jako zerowe, więc komunikacja nie zwiększa czasu harmonogramu.

Koszt obejmuje koszt wykonania zadań, koszt użytych procesorów oraz koszt
podpięcia użytych procesorów do szyn z sekcji @comm.

Program wypisuje koszt, czas, liczbę prób, przydział zadań do procesorów oraz
szyny komunikacyjne z procesorami, które łączą.
