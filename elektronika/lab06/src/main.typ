#import "@preview/rubber-article:0.5.2": *

#show: article.with(
  cols: none,
  heading-numbering: "1.",
  lang: "pl",
  page-margins: 2.5cm,
  page-paper: "a4",
  text-size: 12pt,
)

#let vv(body) = math.bold(math.upright(body))
#set math.mat(delim: "[", column-gap: 1em)
#set math.vec(delim: "[")
#set math.equation(numbering: "(1)")

#set figure(supplement: [Obraz])
#show figure.caption: set text(hyphenate: false)
#show figure.where(kind: table): set figure(supplement: [Tabela])
#show table: set table(stroke: 0.5pt)
#set enum(numbering: "a)")

#maketitle(
  title: "Elektronika cyfrowa - sprawozdanie 6",
  authors: ("Mateusz Wojtyna, gr 9",),
  date: "27 maja 2026",
)

#heading([Dane], numbering: none, level: 3, outlined: false)
- stanowisko nr 02
- miernik uniwersalny nr 14

#outline()
#pagebreak()

= Zadanie 1
== Treść
Wykorzystując płytkę UA-1, połącz układ komparatora napięcia LM 311 według poniżej
przedstawionego schematu. Wybierz amplitudę sygnałów z generatora (np. 5V) wiedząc że jego
wyjściowe napięcie chwilowe nie może wykraczać poza zakres napięcia zasilającego komparator.
Potencjometrem P nastaw napięcie z zakresu międzyszczytowego generatora, tak aby uzyskać na
wyjściu fale prostokątną. Zbadaj przebieg napięcia wyjściowego komparatora dla różnych
kształtów napięć i częstotliwości generatora. Wykonaj to samo ćwiczenie używając wzmacniacza
operacyjnego zamiast komparatora napięcia.

#figure(
  image("img/1.00_schemat.png", width: 50%),
  caption: [Schemat układu z zadania 1],
)

== Wstęp teoretyczny
*Komparator napięcia* jest układem porównującym dwa napięcia wejściowe. Jeżeli napięcie na wejściu nieodwracającym jest większe od napięcia na wejściu odwracającym, wyjście przyjmuje jeden ze stanów logicznych, a po odwróceniu tej zależności przełącza się w drugi stan. W praktyce komparator działa więc jak bardzo czuły detektor progu: zamienia informację o tym, czy sygnał wejściowy znajduje się powyżej lub poniżej napięcia odniesienia, na sygnał dwustanowy. W badanym układzie napięcie odniesienia ustawiano potencjometrem, a komparator LM311 przekształcał przebiegi z generatora, na przykład sinusoidalne lub trójkątne, w przebieg prostokątny.

*Wzmacniacz operacyjny* jest układem analogowym o bardzo dużym wzmocnieniu różnicowym. Posiada dwa wejścia: odwracające i nieodwracające, a jego napięcie wyjściowe zależy od różnicy napięć między tymi wejściami. W typowych zastosowaniach wzmacniacz operacyjny pracuje ze sprzężeniem zwrotnym. W tym ćwiczeniu wykorzystano go jednak podobnie do komparatora: po przekroczeniu napięcia odniesienia wyjście przechodziło w stan nasycenia. Taki układ może generować przebieg prostokątny, ale zwykle przełącza się wolniej i mniej jednoznacznie niż komparator.

Aby kontrolować napięcie za pomocą potencjometru, wykorzystałem dzielnik napięcia złożony z dwóch rezystorów z płytki UA-1, których oporność można kontrolować potencjometrami. W generatorze podano amplitudę $5 "V"$.

== Praktyka
Na początku sprawdzono, czy płytka działa poprawnie. Zmierzono miernikiem następujące miejsca:
- wyjście $+12 "V"$: $11.98 "V"$,
- rezystor żółty: od $22.5 space Omega$ do $126 space Omega$,
- rezystor czerwony: od $27.6 space Omega$ do $10.83 "k"Omega$.

=== Układ z komparatorem
#v(-1em)
#figure(
  image("img/1.01_komparator_topview.jpeg"),
  caption: [Układ z komparatorem na płycte UA-1],
)

Po ustawieniu odpowiednich oporów, podano przebiegi sinusoidalne, prostokątne i trójkątne. Zrobiono zdjęcia przebiegów dla coraz większej częstotliwości sygnału wejściowego. Sygnał wejściowy jest w kolorze #text(fill: yellow)[żółtym], sygnał wyjściowy w kolorze #text(fill: blue)[niebieskim].

==== Przebieg sinusoidalny
#v(-1em)
#figure(
  image("img/komparator_sinus_amplituda.svg", width: 86.5%),
  caption: [Wykres amplitudy sygnału wyjściowego komparatora w funkcji częstotliwości sygnału wejściowego dla przebiegu sinusoidalnego],
) <komparator_sinus_amplituda>

#figure(
  table(
    columns: 2,
    align: (left, center),
    table.header([Częstotliwość sygnału \ wejściowego $f$ [Hz]], [Amplituda sygnału \ wyjściowego $U_"wy"$ [V]]),
    [500], [4.882],
    [1 000], [4.878],
    [10 000], [4.797],
    [100 000], [4.879],
    [500 100], [4.958],
    [600 100], [4.963],
    [700 200], [4.958],
    [799 900], [4.958],
    [849 700], [0.080],
  ),
  caption: [Dane do wykresu amplitudy sygnału wyjściowego komparatora (@komparator_sinus_amplituda)],
)

Jak widać, używając komparatora, amplituda sygnału wyjściowego prawie się nie zmienia, dopóki częstotliwość nie osiągnie wartości $~850 "kHz"$.

#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/1.02_komparator_oscy_sinus_5V_500Hz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 500 "Hz"$]
    ]),
    align(center, [
      #image("img/1.03_komparator_oscy_sinus_5V_1kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 1 "kHz"$]
    ]),

    align(center, [
      #image("img/1.04_komparator_oscy_sinus_5V_10kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 10 "kHz"$]
    ]),
    align(center, [
      #image("img/1.05_komparator_oscy_sinus_5V_100kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 100 "kHz"$]
    ]),

    align(center, [
      #image("img/1.05_komparator_oscy_sinus_5V_500kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 500 "kHz"$]
    ]),
    align(center, [
      #image("img/1.05_komparator_oscy_sinus_5V_600kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 600 "kHz"$]
    ]),

    align(center, [
      #image("img/1.05_komparator_oscy_sinus_5V_700kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 700 "kHz"$]
    ]),
    align(center, [
      #image("img/1.05_komparator_oscy_sinus_5V_800kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 800 "kHz"$]
    ]),
  ),
)
#figure(
  align(
    center,
    [#image("img/1.07_komparator_oscy_sinus_5V_850kHz.png", width: 80%) #v(-1em) #text(size: 9pt)[$f = 850 "kHz"$] ],
  ),
  caption: [Przebiegi wyjściowe komparatora dla sygnału sinusoidalnego z generatora, $5 "V"$],
)

Gdy sygnał wejściowy ma dodatnie napięcie, sygnał wyjściowy jest w stanie niskim, a gdy sygnał wejściowy ma napięcie ujemne, sygnał wyjściowy jest w stanie wysokim. Sygnał coraz bardziej się zniekształca wraz ze wzrostem częstotliwości. Sygnał zanika dla częstotliwości $~850 "kHz"$.

==== Przebieg prostokątny
#v(-1em)
#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/1.08_komparator_oscy_square_5V_1kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 1 "kHz"$]
    ]),
    align(center, [
      #image("img/1.09_komparator_oscy_square_5V_10kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 10 "kHz"$]
    ]),

    align(center, [
      #image("img/1.10_komparator_oscy_square_5V_100kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 100 "kHz"$]
    ]),
    align(center, [
      #image("img/1.11_komparator_oscy_square_5V_500kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 500 "kHz"$]
    ]),

    align(center, [
      #image("img/1.12_komparator_oscy_square_5V_640kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 640 "kHz"$]
    ]),
  ),
  caption: [Przebiegi wyjściowe komparatora dla sygnału prostokątnego z generatora, $5 "V"$],
)

Sygnał wyjściowy jest lustrzanym odbiciem sygnału wejściowego. Dla coraz większych częstotliwości, sygnał wyjściowy staje się coraz bardziej zniekształcony, a dla $~640 "kHz"$ całkowicie zanika.

==== Przebieg trójkątny
#v(-1em)
#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/1.13_komparator_oscy_ramp_5V_1kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 1 "kHz"$]
    ]),
    align(center, [
      #image("img/1.13_komparator_oscy_ramp_5V_100kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 100 "kHz"$]
    ]),

    align(center, [
      #image("img/1.13_komparator_oscy_ramp_5V_200kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 200 "kHz"$]
    ]),
  ),
  caption: [Przebiegi wyjściowe komparatora dla rampy z generatora, $5 "V"$],
)

Gdy sygnał wejściowy ma dodatnie napięcie, sygnał wyjściowy jest w stanie niskim, a gdy sygnał wejściowy ma napięcie ujemne, sygnał wyjściowy jest w stanie wysokim. Tak jak poprzednio, sygnał coraz bardziej się zniekształca wraz ze wzrostem częstotliwości. Maksymalna częstotliwość jaką obsługuje generator dla fali trójkątnej to $200 "kHz"$, więc nie było możliwości przetestowania zachowania fali trójkątnej dla większych częstotliwości.

=== Układ ze wzmacniaczem operacyjnym
#v(-1em)
#figure(
  image("img/1.14_opamp_topview.jpeg", width: 80%),
  caption: [Układ ze wzmacniaczem operacyjnym na płytce UA-1],
)

==== Przebieg sinusoidalny
#v(-1em)
#figure(
  image("img/opamp_sinus_amplituda.svg", width: 86.5%),
  caption: [Wykres amplitudy sygnału wyjściowego wzmacniacza operacyjnego w funkcji częstotliwości sygnału wejściowego dla przebiegu sinusoidalnego],
) <opamp_sinus_amplituda>

#figure(
  table(
    columns: 2,
    align: (left, center),
    table.header([Częstotliwość sygnału \ wejściowego $f$ [Hz]], [Amplituda sygnału \ wyjściowego $U_"wy"$ [V]]),
    [1 000], [21.210],
    [10 000], [21.010],
    [49 990], [4.199],
    [100 000], [0.600],
    [200 000], [1.199],
    [300 000], [0.799],
    [400 200], [0.600],
    [500 000], [0.400],
    [599 900], [0.200],
  ),
  caption: [Dane do wykresu amplitudy sygnału wyjściowego wzmacniacza operacyjnego (@opamp_sinus_amplituda)],
)

Używając wzmacniacza operacyjnego, amplituda sygnału wyjściowego spada razem ze wzrostem częstotliwości i zanika całkowicie dla $~600 "kHz"$.

#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/1.15.1_opamp_oscy_sinus_5V_1kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 1 "kHz"$]
    ]),
    align(center, [
      #image("img/1.15.2_opamp_oscy_sinus_5V_10kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 10 "kHz"$]
    ]),

    align(center, [
      #image("img/1.15.3_opamp_oscy_sinus_5V_50kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 50 "kHz"$]
    ]),
    align(center, [
      #image("img/1.15.4_opamp_oscy_sinus_5V_100kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 100 "kHz"$]
    ]),

    align(center, [
      #image("img/1.15.5_opamp_oscy_sinus_5V_200kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 200 "kHz"$]
    ]),
    align(center, [
      #image("img/1.15.6_opamp_oscy_sinus_5V_300kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 300 "kHz"$]
    ]),

    align(center, [
      #image("img/1.15.7_opamp_oscy_sinus_5V_400kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 400 "kHz"$]
    ]),
    align(center, [
      #image("img/1.15.8_opamp_oscy_sinus_5V_500kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 500 "kHz"$]
    ]),
  ),
)
#figure(
  align(
    center,
    [#image("img/1.15.9_opamp_oscy_sinus_5V_600kHz.png", width: 80%) #v(-1em) #text(size: 9pt)[$f = 600 "kHz"$] ],
  ),
  caption: [Przebiegi wyjściowe wzmacniacza operacyjnego dla sygnału sinusoidalnego z generatora, $5 "V"$],
)

Gdy sygnał wejściowy ma dodatnie napięcie, sygnał wyjściowy jest w stanie niskim, a gdy sygnał wejściowy ma napięcie ujemne, sygnał wyjściowy jest w stanie wysokim. Im większa częstotliwość, tym bardziej sygnał się zniekształca w falę trójkątną. Sygnał zanika dla częstotliwości $~500 "kHz"$.

==== Przebieg prostokątny
#v(-1em)
#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/1.16_opamp_oscy_square_5V_1kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 1 "kHz"$]
    ]),
    align(center, [
      #image("img/1.16_opamp_oscy_square_5V_10kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 10 "kHz"$]
    ]),

    align(center, [
      #image("img/1.16_opamp_oscy_square_5V_50kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 50 "kHz"$]
    ]),
    align(center, [
      #image("img/1.16_opamp_oscy_square_5V_100kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 100 "kHz"$]
    ]),
  ),
  caption: [Przebiegi wyjściowe wzmacniacza operacyjnego dla sygnału prostokątnego z generatora, $5 "V"$],
)

Przebieg wyjściowy jest lustrzanym odbiciem przebiegu wejściowego. Im większa częstotliwość, tym bardziej sygnał się zniekształca w falę trójkątną. Sygnał zanika dla częstotliwości $> 100 "kHz"$.

==== Przebieg trójkątny
#v(-1em)
#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/1.17_opamp_oscy_ramp_5V_1kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 1 "kHz"$]
    ]),
    align(center, [
      #image("img/1.18_opamp_oscy_ramp_5V_10kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 10 "kHz"$]
    ]),

    align(center, [
      #image("img/1.18_opamp_oscy_ramp_5V_30kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 30 "kHz"$]
    ]),
    align(center, [
      #image("img/1.18_opamp_oscy_ramp_5V_50kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 50 "kHz"$]
    ]),

    align(center, [
      #image("img/1.18_opamp_oscy_ramp_5V_100kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 100 "kHz"$]
    ]),
  ),
  caption: [Przebiegi wyjściowe wzmacniacza operacyjnego dla rampy z generatora, $5 "V"$],
)

Gdy sygnał wejściowy ma dodatnie napięcie, sygnał wyjściowy jest w stanie niskim, a gdy sygnał wejściowy ma napięcie ujemne, sygnał wyjściowy jest w stanie wysokim. Tak jak poprzednio, sygnał coraz bardziej się zniekształca w falę trójkątną wraz ze wzrostem częstotliwości i zanika dla częstotliwości $>100 "kHz"$.

#pagebreak()

== Podsumowanie
W przeprowadzonym doświadczeniu porównano działanie komparatora napięcia oraz wzmacniacza operacyjnego pracującego bez sprzężenia zwrotnego. Pomiary przeprowadzono dla różnych kształtów sygnału wejściowego (sinusoidalny, prostokątny, trójkątny) w szerokim zakresie częstotliwości. Na podstawie uzyskanych wyników sformułowano następujące wnioski:

1. Komparator wykazuje się znacznie większą szybkością działania i krótszym czasem przełączania niż wzmacniacz operacyjny. Dla przebiegu sinusoidalnego i prostokątnego komparator pracował poprawnie do bardzo wysokich częstotliwości (odpowiednio około $850 "kHz"$ oraz $640 "kHz"$), zachowując strome zbocza i stabilną amplitudę wyjściową. Dopiero blisko tych częstotliwości granicznych następowało gwałtowne tłumienie i zanik sygnału.

2. Dla wzmacniacza operacyjnego przy wyższych częstotliwościach sygnał wyjściowy ulegał silnemu zniekształceniu (zbocza stawały się nachylone, a przebieg prostokątny przechodził w trójkątny).

3. Spadek amplitudy wyjściowej we wzmacniaczu operacyjnym rozpoczynał się przy znacznie niższych częstotliwościach niż w komparatorze. Przy sygnale sinusoidalnym o częstotliwości $50 "kHz"$ amplituda wyjściowa spadła już do $4.199 "V"$ (z początkowych $21.21 "V"$), a powyżej $100 "kHz"$ sygnał wyjściowy uległ niemal całkowitemu stłumieniu (amplituda poniżej $1 "V"$). Dla przebiegu prostokątnego i trójkątnego zniekształcenia były wyraźne już powyżej $10 "kHz"$, a dla fali trójkątnej sygnał zanikł przy około $100 "kHz"$.

4. Oba układy działały jako komparatory odwracające – wysoki stan sygnału wejściowego odpowiadał niskiemu stanowi na wyjściu, a niski stan wejściowy odpowiadał wysokiemu stanowi wyjściowemu.

#pagebreak()

= Zadanie 3
== Treść
3.1 Zapoznać się z budową i działaniem modułów przetwornika A/C typu FLASH:
- modułu komparatorów,
- transkodera RPP-S (Ręcznie Programowana Pamięć Stała),
- transkodera RPP-SRAM (Ręcznie Programowana Pamięć SRAM).
\
3.2 *Programowanie transkodera RPP-S.* \ Połączyć moduł komparatorów z transkoderem RPP-S. Na wejście modułu komparatora podać regulowane napięcie stałe. Zmieniając poziom napięcia wejściowego zaprogramować transkoder w ten sposób, aby wartość binarna na wyjściu transkodera odpowiadała ilości zapalonych diod na module komparatorów (czyli była proporcjonalna do napięcia wejściowego). Zwrócić uwagę iż diody na wyjściu RPP-S reprezentują stany zanegowane.
\ \
3.3 *Badanie działania przetwornika.* \ Po zaprogramowaniu pamięci stałej dołączyć do układu płytkę konwertera C/A a na wejście modułu komparatorów podać sinusoidalne napięcie zmienne. Pamiętać, ze konwerter pracuje prawidłowo tylko w zakresie napięcia powyżej 0 V. Używając oscyloskopu porównać przebieg napięcia wejściowego i napięcia po kolejnych konwersjach w układach A/C i C/A. Jaka jest rozdzielczość napięciowa konwertera typy FLASH. Porównać ją z odpowiednią wartością otrzymaną dla przetwornika badanego w punkcie 2.
\ \
3.4 *Użycie modułu z pamięcią SRAM.* \ Zmodyfikować konfigurację układu przetwornika zastępując transkoder RPP-S transkoderem z pamięcią SRAM. Postępując analogicznie jak opisano w punktach 3.2 i 3.3 zaprogramować pamięć SRAM i sprawdzić działanie przetwornika. Układ można zaprojektować w ten sposób aby amplituda sygnału po konwersji ulegała odwróceniu.
\ \
3.5 Dla przebiegu sinusoidalnego określić zakres częstotliwości, w którym przetwornik działa prawidłowo.

== Wstęp teoretyczny
Układ przetwornika analogowo-cyfrowego umożliwia zamianę informacji o podanej
wielkości fizycznej, z postaci analogowej (ciągłej) na postać cyfrową (skwantowaną).

Przetwornik analogowo-cyfrowy (A/C) typu FLASH charakteryzuje się bardzo krótkim czasem konwersji, ponieważ porównanie napięcia wejściowego z napięciami odniesienia odbywa się jednocześnie na wszystkich komparatorach. Układ składa się z dzielnika napięciowego, zestawu komparatorów oraz transkodera kodującego stan komparatorów na postać binarną. Dla przetwornika $n$-bitowego wymagane jest użycie $2^n - 1$ komparatorów. Komparatory dają na wyjściu kod termometryczny (liczba aktywnych komparatorów jest proporcjonalna do napięcia wejściowego). Zadaniem transkodera jest konwersja kodu termometrycznego na wyjściowy kod dwójkowy (np. NKB). W ćwiczeniu rolę transkodera pełniła pamięć stała RPP-S oraz pamięć SRAM, programowane ręcznie za pomocą przełączników.

== Praktyka

=== Budowa modułów (Punkt 3.1)
Zapoznano się z modułami wchodzącymi w skład przetwornika FLASH na płytce UA-1. Zidentyfikowano moduł komparatorów, moduł transkodera z pamięcią stałą RPP-S oraz moduł transkodera z pamięcią SRAM.

=== Programowanie transkodera RPP-S (Punkt 3.2)
#v(-1em)
#figure(
  image("img/3.2.1_topview.jpeg", width: 80%),
  caption: [Układ połączeń z transkoderem RPP-S na płytce UA-1],
)

Połączono moduł komparatorów z transkoderem RPP-S. Jako zasilanie pomocnicze podano napięcie $10 "V"$ z ograniczeniem prądowym $0.45 "A"$. Na wejście układu podano regulowane napięcie stałe z zasilacza. Zmieniając poziom napięcia wejściowego i obserwując zapalone diody na module komparatorów, zaprogramowano pamięć transkodera RPP-S tak, aby binarny stan wyjściowy odpowiadał liczbie aktywnych komparatorów (czyli był proporcjonalny do napięcia wejściowego). Zwrócono uwagę na to, że diody na wyjściu RPP-S reprezentują stany zanegowane, co uwzględniono przy programowaniu (zob. #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQA3M8Tmj3rSRoCIf2OsKTDAAWEw7rhdp--LAPNNO2jLx0s?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=PmRAcW")[#underline("nagranie wideo z testowania programowania transkodera RPP-S")]).

Ręcznie wyznaczona rozdzielczość napięciowa (amplitudy) na tym etapie wynosiła $0.7 "V"$.

=== Badanie działania przetwornika (Punkt 3.3)
Do układu dołączono konwerter cyfrowo-analogowy (C/A). Na wejście modułu komparatorów podano sinusoidalne napięcie zmienne z generatora. Sygnał wejściowy został odpowiednio przesunięty w składową stałą, tak aby jego wartości były zawsze większe od $0 "V"$, ponieważ konwerter C/A pracuje prawidłowo wyłącznie dla napięć dodatnich (zob. #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQD5LCx3Gpj2TLPNeOA8CUssAWweQX8Iloxtr28mv38jm_s?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=3s4h1i")[#underline("nagranie wideo z działania przetwornika z transkoderem RPP-S")]).

#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/3.3.3_sinus_oscy.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Przebieg sinusoidalny]
    ]),
    align(center, [
      #image("img/3.3.4_ramp_oscy.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Przebieg trójkątny]
    ]),
  ),
  caption: [Przebiegi wejściowe (żółte) oraz po konwersji A/C i C/A (niebieskie) dla transkodera RPP-S],
)

Na oscyloskopie zaobserwowano charakterystyczne schodki kwantyzacji sygnału wyjściowego.

#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/3.3.5_rozdzielczosc_amplituda.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Pomiar rozdzielczości amplitudy]
    ]),
    align(center, [
      #image("img/3.3.5_rozdzielczosc_freq.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Pomiar kroku czasowego (próbkowania)]
    ]),
  ),
  caption: [Pomiary rozdzielczości sygnału wyjściowego na oscyloskopie dla transkodera RPP-S],
)

Na podstawie pomiarów oscyloskopowych określono parametry przetwornika:
- *Rozdzielczość napięciowa (amplitudy)*: wyniosła $0.7 "V"$, co jest zgodne z wartością wyznaczoną ręcznie. W porównaniu do przetwornika z zadania 4 (gdzie rozdzielczość napięciowa wynosiła $13.4 "mV"$), rozdzielczość przetwornika FLASH jest znacznie gorsza (krok kwantyzacji jest większy). Wynika to bezpośrednio z małej rozdzielczości bitowej przetwornika FLASH na płycie UA-1 (tylko 3 bity, co daje 7 poziomów kwantyzacji, w porównaniu do 8-bitowego przetwornika z zadania 4).
- *Rozdzielczość czasowa (krok próbkowania)*: szerokość pojedynczego schodka próbkowania zmierzona na oscyloskopie wyniosła $43 space mu"s"$.

=== Użycie modułu z pamięcią SRAM (Punkt 3.4)
#v(-1em)
#figure(
  image("img/3.4.1_topview.jpeg", width: 80%),
  caption: [Układ połączeń z transkoderem SRAM na płytce UA-1],
)

Zastąpiono transkoder RPP-S modułem z pamięcią SRAM. Należy pamiętać, że pamięć SRAM traci dane po odłączeniu zasilania.

Następnie zaprogramowano pamięć SRAM (zob. #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQD8f5HHtnyJRY-kYmhf3dz3AY45llFOb_sbAISn4_9G8zY?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=wCUV7Z")[#underline("nagranie wideo z testowania programowania pamięci SRAM")] oraz #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQCeVObX_s36TqKeM6wn0imVAdJvW9jiZWNJcQO1ME9k6-Q?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=7z1WHm")[#underline("nagranie wideo z działania przetwornika z pamięcią SRAM")]).

#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/3.4.3_sinus_oscy.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Przebieg sinusoidalny]
    ]),
    align(center, [
      #image("img/3.4.4_ramp_oscy.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Przebieg trójkątny]
    ]),
  ),
  caption: [Przebiegi wejściowe (żółte) oraz po konwersji (niebieskie) dla transkodera SRAM],
)

Na zarejestrowanych przebiegach wyraźnie znowu widać schodki kwantyzacji sygnału wyjściowego.

#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/3.4.5_rozdzielczosc_amplituda.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Pomiar rozdzielczości amplitudy]
    ]),
    align(center, [
      #image("img/3.4.5_rozdzielczosc_freq.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[Pomiar kroku czasowego (próbkowania)]
    ]),
  ),
  caption: [Pomiary rozdzielczości sygnału wyjściowego dla transkodera SRAM],
)

Zmierzone parametry były identyczne jak w przypadku pamięci RPP-S: rozdzielczość napięciowa wyniosła $0.7 "V"$, a krok czasowy próbkowania $41 space mu"s"$.

Żeby odwrócić amplitudę sygnału po konwersji, wystarczyłoby zaprogramować negację dla każdej liczby.

=== Zakres prawidłowego działania przetwornika (Punkt 3.5)
#v(-1em)
#figure(
  grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    align(center, [
      #image("img/3.5.1_10kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 10 "kHz"$]
    ]),
    align(center, [
      #image("img/3.5.1_20kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 20 "kHz"$]
    ]),

    align(center, [
      #image("img/3.5.1_40kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 40 "kHz"$]
    ]),
    align(center, [
      #image("img/3.5.1_50kHz.png", width: 100%)
      #v(-1em)
      #text(size: 9pt)[$f = 50 "kHz"$]
    ]),
  ),
  caption: [Przebiegi przy wyższych częstotliwościach dla badania pasma przenoszenia],
)

Zbadano poprawność działania przetwornika w funkcji częstotliwości sygnału wejściowego sinusoidalnego.
Na podstawie pomiarów oscyloskopowych określono zakres prawidłowego działania przetwornika:
- Układ pracuje w pełni poprawnie od częstotliwości poniżej $1 "Hz"$ do około $10 "kHz"$.
- Powyżej częstotliwości $10 "kHz"$ (co pokazano na przebiegach dla $20 "kHz"$, $40 "kHz"$ i $50 "kHz"$) sygnał wyjściowy zaczyna ulegać coraz silniejszym zniekształceniom (opóźnienie fazowe względem wejścia, zniekształcenia kształtu schodków oraz gubienie niektórych poziomów kwantyzacji).

== Podsumowanie
W ramach zadania 3 zrealizowano i przetestowano przetwornik analogowo-cyfrowy typu FLASH z dwoma modułami transkodera (pamięć stała RPP-S oraz pamięć SRAM) współpracujący z przetwornikiem cyfrowo-analogowym (C/A). Na podstawie przeprowadzonych badań sformułowano następujące wnioski:

+ *Praca z transkoderem RPP-S*: Ręcznie zaprogramowano pamięć stałą tak, aby kodowała stany wyjściowe komparatorów (kod termometryczny) na postać binarną. W przebiegach wyjściowych (sinusoidalnym i trójkątnym) zaobserwowano charakterystyczne schodki kwantyzacji. Rozdzielczość napięciowa (amplitudy) wyniosła $0.7 "V"$, a krok próbkowania w dziedzinie czasu wyniósł $43 space mu"s"$.
+ *Praca z transkoderem SRAM*: Po zaprogramowaniu pamięci SRAM, należało uważać, żeby nie odłączyć zasilania, gdyż wtedy pamięć straciłaby dane. Rozdzielczość napięciowa i czasowa była prawie taka sama jak w RPP-S.
+ *Pasmo przenoszenia*: Przetwornik FLASH pracuje w pełni prawidłowo w pasmie częstotliwości od poniżej $1 "Hz"$ do około $10 "kHz"$. Powyżej $10 "kHz"$ (co zaobserwowano przy $20 "kHz"$, $40 "kHz"$ i $50 "kHz"$) w przebiegach wyjściowych pojawiają się zniekształcenia, opóźnienia fazowe oraz gubienie schodków kwantyzacji.

#pagebreak()

= Zadanie 4
== Treść
4.1 Zapoznać się ze schematem przetwornika A/C działającego w oparciu o przetwornik C/A. Zwrócić uwagę na następujące elementy: przetwornik C/A, komparator, generator sygnału zegarowego, licznik, rejestr SAR, wyjście na wyświetlacz. \ \
4.2 *Zbadać poprawność działania przetwornika.* \ Zworkę regulacji częstotliwości ustawić w pozycji Z2, za pomocą zworki przełącznik ustawić w pozycję „KOMPENS.”. Przy pomocy potencjometru ustawić napięcie wejściowe na wybranym poziomie (około 3 V). Zresetować licznik przyciskiem RESET, zaobserwować uzyskaną wartość cyfrową. Zmierzyć napięcie na wyjściu przetwornika C/A przy pomocy oscyloskopu i sprawdzić czy jest ono takie samo jak napięcie podawane przez potencjometr.\ \
4.3 *Określić rozdzielczość napięciową przetwornika.* \ Zworkę regulacji częstotliwości ustawić w pozycji Z2. Zresetować licznik przyciskiem RESET. Zwiększać napięcie na potencjometrze aż do uzyskania skoku napięcia na wyjściu C/A. Następnie powoli zwiększać napięcie wejściowe by uzyskać skok napięcia. Wykonując pomiar napięcia przed i po skoku można wyznaczyć rozdzielczość napięciową.

\
Dalszej części zadaniu już nie zdążyłem zrobić.

== Wstęp teoretyczny
Przetwornik analogowo-cyfrowy (A/C) działający w oparciu o przetwornik cyfrowo-analogowy (C/A) w działa w pętli sprzężenia zwrotnego. Kluczowymi elementami układu są:
- *Komparator*, porównujący mierzone napięcie wejściowe $U_"we"$ z napięciem wyjściowym z przetwornika C/A ($U_"DAC"$).
- *Licznik*, zliczający impulsy z generatora zegarowego.
- *Przetwornik C/A*, konwertujący wartość cyfrową licznika z powrotem na napięcie analogowe.

Po zresetowaniu licznika, zlicza on impulsy w górę od zera. Napięcie $U_"DAC"$ rośnie schodkowo. W momencie, gdy napięcie $U_"DAC"$ zrówna się lub nieznacznie przekroczy $U_"we"$, komparator zmienia swój stan wyjściowy, blokując dalsze dopływanie impulsów zegarowych do licznika. Stan licznika w chwili zatrzymania odpowiada cyfrowej reprezentacji napięcia wejściowego.

== Praktyka

=== Zapoznanie ze schematem (Punkt 4.1)
Układ połączono zgodnie ze schematem blokowym przetwornika. 

#v(-1em)
#figure(
  image("img/4.1.1_topview.jpeg", width: 80%),
  caption: [Układ pomiarowy przetwornika A/C opartego na C/A na płycie UA-1 (początkowy stan)],
)

Zidentyfikowano elementy składowe na płycie: generator sygnału zegarowego (zworka ustawiona w pozycji Z2), licznik cyfrowy, rejestr SAR oraz przetwornik C/A. Wyjście cyfrowe podłączono do modułu wyświetlacza wyświetlającego wartość w postaci binarnej (diody LED), dziesiętnej oraz napięcia wyjściowego C/A.

=== Badanie poprawności działania (Punkt 4.2)
Zworkę wyboru częstotliwości ustawiono w pozycji Z2, a przełącznik wyboru trybu w pozycję „KOMPENS.”. Za pomocą potencjometru „NAP. WEJŚCIOWE” zadano napięcie wejściowe bliskie $3 "V"$.

#v(-1em)
#figure(
  image("img/4.2.1_topview.jpeg", width: 80%),
  caption: [Układ pomiarowy w trakcie pomiaru],
)

Po wciśnięciu przycisku RESET licznik zliczył impulsy i zatrzymał się w punkcie równowagi. Odczytano następujące wartości:
- Napięcie DAC: $2.98 "V"$
- Wartość dziesiętna: $152$
- Wartość binarna: $10011000$ ($128 + 16 + 8 = 152$)

W celu weryfikacji poprawności pomiaru, do wyjścia przetwornika C/A podłączono oscyloskop.

#v(-1em)
#figure(
  image("img/4.2.3_voltage.png"),
  caption: [Rzeczywiste napięcie na wyjściu przetwornika C/A mierzone oscyloskopem],
)

Napięcie wyjściowe C/A zmierzone na oscyloskopie wyniosło około $3 "V"$, co w granicach tolerancji i błędów pomiarowych odpowiada wartości wskazywanej przez wyświetlacz oraz napięciu zadanemu potencjometrem. Cały proces kompensacji po resecie zarejestrowano na nagraniu wideo (zob. #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQD7iZwEl3dcSrsJazyTWic7AR-QBNe30hpcip2wr8U2O8s?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=qf9vGI")[#underline("nagranie wideo - badanie działania przetwornika")]).

=== Określenie rozdzielczości napięciowej (Punkt 4.3)
W celu określenia rozdzielczości napięciowej przetwornika, zresetowano licznik przyciskiem RESET, a następnie powoli i precyzyjnie zwiększano napięcie wejściowe za pomocą potencjometru, aż do zaobserwowania skoku napięcia wyjściowego o jeden najmniej znaczący bit. Przebieg wyjściowy obserwowano na oscyloskopie przy odpowiednio małej czułości pionowej ($50 "mV/div"$).

#v(-1em)
#figure(
  image("img/4.3.1_rozdzielczość_amplitudy.png"),
  caption: [Pomiar kroku kwantyzacji (rozdzielczości) za pomocą kursorów oscyloskopu],
)

Korzystając z kursorów oscyloskopu, zmierzono różnicę poziomów napięć przed i po skoku:
- Poziom dolny: $381.591 "mV"$
- Poziom górny: $394.991 "mV"$
- Różnica ($Delta v$): $13.399 "mV"$
  
Eksperymentalnie wyznaczona *rozdzielczość napięciowa* badanego przetwornika wynosi zatem około $13.4 "mV"$.

Rozdzielczość ta jest niemal 50-krotnie lepsza od rozdzielczości przetwornika typu FLASH z zadania 3 (która wynosiła $0.7 "V"$). Wynika to z faktu, że badany przetwornik jest przetwornikiem 8-bitowym (256 poziomów kwantyzacji), podczas gdy przetwornik FLASH dysponował jedynie rozdzielczością 3-bitową (7 poziomów kwantyzacji). 

== Podsumowanie zadania 4
W ramach zadania zbadano działanie oraz określono parametry przetwornika analogowo-cyfrowego działającego w oparciu o przetwornik C/A. Sformułowano następujące wnioski:
+ Układ działa w pełni poprawnie. Po zresetowaniu układu napięcie wyjściowe C/A zbliża się schodkowo do poziomu napięcia wejściowego, a po osiągnięciu stanu równowagi wartość cyfrowa zostaje przestaje wzrastać i zaprezentowana na wyświetlaczach.
+ Zmierzona eksperymentalnie rozdzielczość napięciowa wynosi $13.4 "mV"$.

#pagebreak()

= Podsumowanie końcowe
Celem ćwiczenia było zapoznanie się z działaniem wybranych układów elektroniki cyfrowej i analogowej wykorzystywanych do przetwarzania sygnałów. W trakcie zajęć zbadano właściwości komparatora napięcia oraz wzmacniacza operacyjnego pracującego jako komparator, a także działanie dwóch typów przetworników analogowo-cyfrowych: przetwornika FLASH oraz przetwornika opartego na przetworniku C/A.

W pierwszej części ćwiczenia wykazano, że komparator napięcia charakteryzuje się znacznie lepszymi właściwościami dynamicznymi niż wzmacniacz operacyjny pracujący bez sprzężenia zwrotnego. Komparator zachowywał prawidłowy kształt sygnału wyjściowego przy częstotliwościach sięgających setek kiloherców, podczas gdy wzmacniacz operacyjny ulegał wyraźnym zniekształceniom już przy znacznie niższych częstotliwościach.

W drugiej części zrealizowano przetwornik A/C typu FLASH wykorzystujący moduł komparatorów oraz programowalne transkodery RPP-S i SRAM. Zaobserwowano proces kwantyzacji sygnału analogowego oraz wyznaczono rozdzielczość napięciową wynoszącą około $0.7 "V"$. Stwierdzono również, że zastosowanie pamięci SRAM nie wpływa na parametry przetwarzania, a jedynie na sposób przechowywania informacji. Badany przetwornik działał poprawnie dla częstotliwości do około $10 "kHz"$.

W ostatniej części przebadano przetwornik wykorzystujący przetwornik C/A i komparator. Potwierdzono poprawność działania układu oraz wyznaczono jego rozdzielczość napięciową równą około $13.4 "mV"$. Oznacza to rozdzielczość około 50 razy lepszą od uzyskanej dla badanego wcześniej przetwornika FLASH, co wynika z większej liczby poziomów kwantyzacji dostępnych w 8-bitowym układzie.

Przeprowadzone doświadczenia pozwoliły w praktyce zaobserwować wpływ parametrów elementów elektronicznych na jakość przetwarzania sygnałów. 

#pagebreak()

= Notatki
#raw(read("./notatki.txt"))

#pagebreak()
#outline(
  title: [Spis obrazów],
  target: figure.where(kind: image),
)

#pagebreak()
#outline(
  title: [Spis tabeli],
  target: figure.where(kind: table),
)
