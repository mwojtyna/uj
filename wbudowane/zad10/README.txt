Program wczytuje graf zadań w formacie używanym w poprzednich zadaniach:
@tasks, @proc, @times, @cost, @comm.

Uruchomienie:

./program plik_wejściowy

Algorytm konstrukcyjny:
1. Zadania są rozpatrywane w porządku topologicznym.
2. Zwykłe zadania T wybierają lokalnie najtańszy dopuszczalny procesor.
3. Nieprzewidziane zadania UT mogą trafić tylko na procesor PP. Spośród PP brane
   są pod uwagę wyłącznie procesory z najmniejszą liczbą wcześniej przydzielonych
   zadań.
4. Procesor PP wykonuje przydzielone zadania sekwencyjnie. Procesor HC jest
   dedykowany i może zostać użyty tylko dla jednego zadania.
5. Czas zależności uwzględnia przesył danych: dla krawędzi z wagą d i szyny
   o przepustowości b doliczane jest ceil(d / b), jeżeli rodzic i dziecko są
   na różnych procesorach. Przy wielu wspólnych szynach wybierany jest
   najmniejszy czas przesyłu.

Koszt obejmuje koszt wykonania zadań, koszt użytych procesorów oraz koszt
podpięcia użytych procesorów do szyn zgodnie z sekcją @comm.

Program wypisuje całkowity koszt, całkowity czas oraz przydział zadań do
procesorów.
