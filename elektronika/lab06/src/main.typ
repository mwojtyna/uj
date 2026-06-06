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
  image("img/1.14_opamp_topview.jpeg"),
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
W przeprowadzonym doświadczeniu porównano działanie dedykowanego komparatora napięcia LM311 oraz wzmacniacza operacyjnego pracującego bez sprzężenia zwrotnego. Pomiary przeprowadzono dla różnych kształtów sygnału wejściowego (sinusoidalny, prostokątny, trójkątny) w szerokim zakresie częstotliwości. Na podstawie uzyskanych wyników sformułowano następujące wnioski:

1. Komparator wykazuje się znacznie większą szybkością działania i krótszym czasem przełączania niż wzmacniacz operacyjny. Dla przebiegu sinusoidalnego i prostokątnego komparator pracował poprawnie do bardzo wysokich częstotliwości (odpowiednio około $850 "kHz"$ oraz $640 "kHz"$), zachowując strome zbocza i stabilną amplitudę wyjściową. Dopiero blisko tych częstotliwości granicznych następowało gwałtowne tłumienie i zanik sygnału.

2. Dla wzmacniacza operacyjnego przy wyższych częstotliwościach sygnał wyjściowy ulegał silnemu zniekształceniu (zbocza stawały się nachylone, a przebieg prostokątny przechodził w trójkątny).

3. Spadek amplitudy wyjściowej we wzmacniaczu operacyjnym rozpoczynał się przy znacznie niższych częstotliwościach niż w komparatorze. Przy sygnale sinusoidalnym o częstotliwości $50 "kHz"$ amplituda wyjściowa spadła już do $4.199 "V"$ (z początkowych $21.21 "V"$), a powyżej $100 "kHz"$ sygnał wyjściowy uległ niemal całkowitemu stłumieniu (amplituda poniżej $1 "V"$). Dla przebiegu prostokątnego i trójkątnego zniekształcenia były wyraźne już powyżej $10 "kHz"$, a dla fali trójkątnej sygnał zanikł przy około $100 "kHz"$.

4. Oba układy działały jako komparatory odwracające – wysoki stan sygnału wejściowego odpowiadał niskiemu stanowi na wyjściu, a niski stan wejściowy odpowiadał wysokiemu stanowi wyjściowemu.

#pagebreak()

= Zadanie 3
== Treść
// TODO

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
