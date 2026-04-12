#import "@preview/rubber-article:0.5.2": *

#let vv(body) = math.bold(math.upright(body))
#let wywe = $U_"wy"\/U_"we"$
#set math.mat(delim: "[", column-gap: 1em)
#set math.vec(delim: "[")

#set image(width: 80%)
#show grid: set image(width: 100%)

#set figure(supplement: [Obraz])
#show figure.caption: set text(hyphenate: false)
#show figure.where(kind: table): set figure(supplement: [Tabela])
#show table: set table(stroke: 0.5pt)

#show: article.with(
  cols: none,
  heading-numbering: "1.",
  lang: "pl",
  page-margins: 2.5cm,
  page-paper: "a4",
  text-size: 12pt,
)

#maketitle(
  title: "Elektronika cyfrowa - sprawozdanie 2",
  authors: ("Mateusz Wojtyna",),
  date: "08 kwietnia 2026",
)

#heading([Dane], numbering: none, level: 3, outlined: false)
- stanowisko nr 02
- płytka RLC nr 12
- miernik uniwersalny nr 15

#outline()
#pagebreak()

= Zadanie 1
== Treść
Zmontować układ różniczkujący (CR) o stałej czasowej $tau$ = RC z przedziału $[0.1, 1] "ms"$.
Podając na wejście tego układu napięcie sinusoidalne zmierzyć stosunek amplitudy sygnału
wyjściowego do amplitudy sygnału wejściowego oraz przesunięcie fazy pomiędzy tymi sygnałami
w szerokim przedziale częstotliwości (charakterystyki częstotliwościowe amplitudy i fazy).
Sporządzić wykresy stosunku amplitud #wywe oraz kąta przesunięcia fazowego
w funkcji częstotliwości $f$. Na ich podstawie wyznaczyć dolną częstotliwość graniczną
i porównać ją z wartością teoretyczną.

== Wstęp teoretyczny
#figure(
  image("./img/cr_schemat.png", width: 59%),
  caption: [Schemat układ CR],
) <cr>

Układ różniczkujący (CR) to czwórnik bierny o układzie zilustrowanym w @cr. Kondensator jest podłączony do wejścia, rezystora oraz wyjścia, natomiast rezystor jest podłączony do uziemienia. Układ CR można stosować m.in. do filtrowania sygnałów o małej częstotliwości (@cr_T), oraz do różniczkowania sygnałów.

Funkcja przejścia dla układu CR wynosi
$
               T(omega) & = frac(j omega/omega_0, 1 + j omega/omega_0) \
  "gdzie" space omega_0 & = 1/(R C) = 1/tau \
$


#grid(
  columns: (auto, auto),
  [
    #figure(
      image("./img/cr_T.png", width: 88.5%),
      caption: [Wykres transmitancji układu względem częstości],
    ) <cr_T>
  ],
  [
    #figure(
      image("./img/cr_phi.png"),
      caption: [Wykres przesunięcia fazy układu względem częstości],
    ) <cr_phi>
  ],
)

== Praktyka
Zmontowano układ różniczkujący na płytce RLC zgodnie ze schematem w @cr. Pojemność kondensatora wynosi $63 "nF"$. Wykorzystano rezystor R2 z oporem równym $tilde 5.56 "k"Omega$, dzięki czemu stała czasowa $tau=R C=0.3503 "ms" in [0.1, 1] "ms"$.

#figure(
  [
    #grid(
      columns: (1fr, 1fr),
      gutter: 0.5em,
      [
        #image("./img/2.1.02_rlc_topdown.jpeg")
      ],
      [
        #image("./img/2.1.01_rlc_wideview.jpeg")
      ],
    )
  ],
  caption: [Układ RC zmontowany na płytce RLC],
)

Przed zmierzeniem #wywe dla szerokiego zakresu częstotliwości, zmierzono go dla $U=1 "V"$ oraz $f=1 "kHz"$. We wszystkich wykresach poniżej, oryginalny sygnał jest w kolorze żółtym, zmodyfikowany w kolorze niebieskim.

#figure(
  image("./img/2.1.03_1V_1kHz_sinus.png"),
  caption: [$wywe = 0.904$, $phi = 335.9degree$ dla $U=1 "V", f=1 "kHz"$],
)

Następnie wyliczono wartość teoretyczną dolnej częstotliwości granicznej $f_g$, czyli takiej częstotliwości sygnału wejściowego, że $wywe=-3 "dB"$. Stosunek amplitud można wyrazić w $"dB"$ wzorem $20log_10(wywe)$.

Skoro wiemy, że $U_"we"=1 "V"$, to $20log_10(U_"wy"\/1 "V") = -3 "dB"$, a więc $U_"wy" approx 0.707 "V"$.
Żeby $U_"wy" = 0.707 "V"$, częstotliwość musi być $tilde 450 "Hz"$, czyli teoretyczna $f_g approx 450 "Hz"$.
Teoretyczną częstotliwość graniczną porównamy później z wartością wyznaczoną z pomiarów.

#figure(
  image("./img/2.1.04_sinus_fg.png"),
  caption: [Przebieg sygnałów z częstotliwością równą częstotliwości granicznej $f_g=450 "Hz"$],
)

Następnie zmierzono częstotliwość i przesunięcie fazowe dla częstotliwości:
- od 100 Hz do 1000 Hz z krokiem 100 Hz,
- od 1 kHz do 10 kHz z krokiem 1 kHz,
- od 10 kHz do 100 kHz z krokiem 10 kHz,
- od 100 kHz do 300 kHz z krokiem 100 kHz.

// TODO: Link do notatek
Zdjęcia ekranu oscyloskopu z pomiarami znajdują się w notatkach.

=== Charakterystyka amplitudowa i fazowa
#figure(
  image("./img/cr_amp_graph.svg", width: 86.5%),
  caption: [Wykres stosunku amplitud #wywe w funkcji częstotliwości],
) <cr_amp_graph>

#figure(
  image("./img/cr_phase_graph.svg", width: 86.5%),
  caption: [Wykres przesunięcia fazowego w funkcji częstotliwości],
) <cr_phase_graph>

#grid(
  columns: (1fr, 1fr),
  [
    #figure(
      table(
        columns: 2,
        align: (left, center),
        table.header([Częstotliwość $f$ [Hz]], [$U_"wy" \/ U_"we"$]),
        [100], [0.2078],
        [200], [0.4000],
        [300], [0.5437],
        [400], [0.6637],
        [500], [0.7357],
        [600], [0.7997],
        [700], [0.8329],
        [800], [0.8640],
        [900], [0.8874],
        [1000], [0.9038],
        [2000], [0.9682],
        [3000], [0.9757],
        [4000], [0.9838],
        [5000], [0.9838],
        [6000], [0.9838],
        [7000], [0.9838],
        [8000], [0.9838],
        [9000], [0.9838],
        [10 000], [0.9838],
        [20 000], [0.9919],
        [30 000], [0.9919],
        [40 000], [0.9919],
        [50 000], [0.9916],
        [60 000], [0.9997],
        [70 000], [0.9997],
        [80 000], [0.9997],
        [90 000], [0.9997],
        [100 000], [0.9997],
        [200 000], [0.9997],
        [300 000], [0.9994],
      ),
      caption: [Dane do wykresu stosunku amplitud (@cr_amp_graph)],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        align: (left, center),
        table.header([Częstotliwość $f$ [Hz]], [Faza $phi$ [°]]),
        [100], [77.2],
        [200], [65.5],
        [300], [56.1],
        [400], [48.1],
        [500], [41.8],
        [600], [36.6],
        [700], [32.3],
        [800], [29.0],
        [900], [26.4],
        [1000], [24.1],
        [2000], [12.7],
        [3000], [8.5],
        [4000], [6.4],
        [5000], [5.2],
        [6000], [4.3],
        [7000], [3.7],
        [8000], [3.3],
        [9000], [2.9],
        [10 000], [2.6],
        [20 000], [1.2],
        [30 000], [120.9],
        [40 000], [1.2],
        [50 000], [0.5],
        [60 000], [0.5],
        [70 000], [0.5],
        [80 000], [0.5],
        [90 000], [0.5],
        [100 000], [0.3],
        [200 000], [0.4],
        [300 000], [65.7],
      ),
      caption: [Dane do wykresu przesunięcia fazy (@cr_phase_graph)],
    )
  ],
)

\
Jak oczekiwano, dla niskich częstotliwości napięcie jest tłumione oraz następuje przesunięcie fazy o około $90 degree$. Dodatkowo można zauważyć 2 punkty na @cr_phase_graph, które nie pasują do wykresu. Prawdopodobnie wynika to z błędu algorytmu mierzącego przesunięcie fazy.

#pagebreak()

Dolną częstotliwość graniczną wyznaczono z charakterystyki amplitudowej jako częstotliwość, dla której $20 log_10(wywe) = -3 "dB"$, co odpowiada $wywe approx 0.707$. Z tabeli oraz wykresu @cr_amp_graph widać, że wartość ta leży pomiędzy punktami $f=400 "Hz"$, dla którego $wywe = 0.6637$, oraz $f=500 "Hz"$, dla którego $wywe = 0.7357$. Stosując interpolację liniową:
$
  f_g approx 400 "Hz" + (500 "Hz" - 400 "Hz") dot frac(0.707 - 0.6637, 0.7357 - 0.6637) approx 460 "Hz"
$
Na podstawie pomiarów otrzymano dolną częstotliwość graniczną równą około $460 "Hz"$. Jest to wartość bardzo zbliżona do wartości teoretycznej $450 "Hz"$, a względna różnica wynosi około $2.2%$.

Kąt przesunięcia fazy dla zmierzonej częstotliwości granicznej można wyznaczyć z charakterystyki fazowej. Ponieważ $f_g approx 460 "Hz"$ leży pomiędzy punktami $400 "Hz"$ i $500 "Hz"$, zastosowano interpolację liniową na podstawie wartości $phi = 311.9 degree$ dla $400 "Hz"$ oraz $phi = 318.2 degree$ dla $500 "Hz"$:
$
  theta(f_g) approx 311.9 degree + (318.2 degree - 311.9 degree) dot frac(460 "Hz" - 400 "Hz", 500 "Hz" - 400 "Hz") = 315.68 degree
$

== Podsumowanie
Przeprowadzone pomiary potwierdziły, że badany układ CR działa jak filtr górnoprzepustowy. Dla małych częstotliwości stosunek amplitud #wywe był wyraźnie mniejszy od 1, natomiast wraz ze wzrostem częstotliwości dążył do 1, co zgadza się z przewidywaniami teoretycznymi.

Charakterystyka fazowa również była zgodna z teorią: dla niskich częstotliwości obserwowano przesunięcie fazowe bliskie $90 degree$, a dla wysokich częstotliwości różnica faz malała. Na wykresie fazowym pojawiły się pojedyncze punkty odstające, co najprawdopodobniej wynika z niedokładności pomiaru lub błędu algorytmu wyznaczającego fazę.

Wyznaczona z pomiarów dolna częstotliwość graniczna wyniosła około $460 "Hz"$ i była bardzo bliska wartości teoretycznej $450 "Hz"$, a kąt przesunięcia fazy dla częstotliwości granicznej wyniósł $315.68 degree$.

#pagebreak()

= Zadanie 2
== Treść
Sprawdzić odpowiedź układu różniczkującego na podawaną na wejście falę prostokątną o okresie $"T"$ mniejszym, porównywalnym i większym od stałej czasowej $tau$. Zaobserwować odpowiedź układu na impuls trójkątny. Sprawdź czy układ różniczkuje sygnał i zanotuj dla jakiego okresu wykonuje to poprawnie.

== Wstęp teoretyczny
Przypominając, $tau=0.3503 "ms"$ w naszym układzie CR. Ustalmy:
$
      T_"mniejszy" & = 0.1tau = 0.03503 "ms" = 35.03 space mu"s" \
  T_"porównywalny" & = tau = 0.3503 "ms" \
       T_"większy" & = 10tau = 3.503 "ms"
$

== Praktyka
=== Impuls prostokątny
Podano następujące impulsy prostokątne:

#align(center)[
  #grid(
    columns: (auto, auto),
    gutter: 0.5em,
    [
      #figure(
        image("./img/2.2.01_1V_Tmnieszy_square.png"),
        caption: [Fala prostokątna $U_"we"=1 "V"$, $T=T_"mniejszy"$],
      )
    ],
    [
      #figure(
        image("./img/2.2.02_1V_Tporownywanly_square.png"),
        caption: [Fala prostokątna $U_"we"=1 "V"$, $T=T_"porównywalny"$],
      )
    ],
  )
]
#align(center)[
  #figure(
    image("./img/2.2.03_1V_Twiekszy_square.png", width: 58%),
    caption: [Fala prostokątna $U_"we"=1 "V"$, $T=T_"większy"$],
  )
]

=== Impuls trójkątny
Podano następujące impulsy trójkątne:

#align(center)[
  #grid(
    columns: (auto, auto),
    gutter: 0.5em,
    [
      #figure(
        image("./img/2.2.04_1V_Tmnieszy_trojkat.png"),
        caption: [Fala trójkątna $U_"we"=1 "V"$, $T=T_"mniejszy"$],
      )
    ],
    [
      #figure(
        image("./img/2.2.05_1V_Tporownywanly_triangle.png"),
        caption: [Fala trójkątna $U_"we"=1 "V"$, $T=T_"porównywalny"$],
      )
    ],
  )
]
#align(center)[
  #figure(
    image("./img/2.2.06_1V_Twiekszy_trojkat.png", width: 60%),
    caption: [Fala trójkątna $U_"we"=1 "V"$, $T=T_"większy"$],
  )
]

=== Różniczkowanie sygnału
Możliwość różniczkowania sygnału najlepiej testować sygnałem prostokątnym, gdyż wtedy pochodna sygnału jest równa zeru poza chwilami gwałtownych zmian i przyjmuje duże wartości jedynie na zboczach. W idealnym układzie różniczkującym odpowiedź powinna więc mieć postać krótkich impulsów pojawiających się w momentach narastania i opadania sygnału wejściowego.

#figure(
  image("./img/2.2.07_test_rozniczkowania_100ms.png"),
  caption: [Test różniczkowania dla $U_"we"=1 "V", T=100 "ms"$],
)
#figure(
  image("./img/2.2.08_test_rozniczkowania_10ms.png"),
  caption: [Test różniczkowania dla $U_"we"=1 "V", T=10 "ms"$],
)

Jak widać, układ jest bliski idealnego układu różniczkującego dla $T >> tau$, co dobrze widać już dla $T=10 "ms"$, a jeszcze wyraźniej dla $T=100 "ms"$.

== Podsumowanie
Przeprowadzone obserwacje potwierdziły, że odpowiedź układu CR zależy od relacji pomiędzy okresem sygnału wejściowego a stałą czasową $tau$. Dla sygnału o $T << tau$ układ nie różniczkuje przebiegu w sposób wyraźny. Dla $T approx tau$ efekt różniczkowania jest zauważalny, lecz nadal daleki od idealnego.
Najlepsze różniczkowanie zaobserwowano dla $T >> tau$, gdy odpowiedź układu przyjmuje postać krótkich impulsów w chwilach zmian sygnału wejściowego.

= Zadanie 3
== Treść
Przekonstruować badany układ różniczkujący na układ całkujący. Zmierzyć charakterystykę
amplitudową i fazową. Wyznaczyć z nich górną częstotliwość graniczną i porównać z wartością
teoretyczną. Podając na wejście falę prostokątną o $T in [0tau,10tau]$ zaobserwować
przebiegi impulsów wyjściowych.

== Wstęp teoretyczny
#figure(
  image("./img/rc_schemat.png", width: 59%),
  caption: [Schemat układu RC],
) <rc>

Układ całkujący (RC) to czwórnik bierny o układzie zilustrowanym w @rc. Rezystor jest podłączony do wejścia, kondensatora oraz wyjścia, natomiast kondensator jest podłączony do uziemienia. Układ RC można stosować m.in. do filtrowania sygnałów o wysokiej częstotliwości (@rc_T), oraz do całkowania sygnałów.

Funkcja przejścia dla układu RC wynosi
$
               T(omega) & = frac(1, 1 + j omega/omega_0) \
  "gdzie" space omega_0 & = 1/(R C) = 1/tau \
$

#grid(
  columns: (auto, auto),
  gutter: 0.5em,
  [
    #figure(
      image("./img/rc_T.png"),
      caption: [\ Wykres transmitancji układu względem częstości],
    ) <rc_T>
  ],
  [
    #figure(
      image("./img/rc_phi.png"),
      caption: [\ Wykres przesunięcia fazy układu względem częstości],
    ) <rc_phi>
  ],
)

== Praktyka
Zmontowano układ całkujący na płytce RLC zgodnie ze schematem w @rc. Wykorzystano rezystor R2 z oporem równym $tilde 5.56 "k"Omega$, dzięki czemu stała czasowa $tau=R C=0.3503 "ms"$.

#figure(
  image("./img/2.3.01_rlc_topdown.jpeg"),
  caption: [Układ CR zmontowany na płytce RLC],
)

Przed zmierzeniem #wywe dla szerokiego zakresu częstotliwości, zmierzono go dla \ $U=1 "V"$ oraz $f=1 "kHz"$.

#figure(
  image("./img/2.3.02_1V_1kHz_sinus.png"),
  caption: [$wywe approx 2.5$, $phi = 65.47degree$ dla $U=1 "V", f=1 "kHz"$],
)

Następnie wyliczono wartość teoretyczną górnej częstotliwości granicznej $f_g$, czyli takiej częstotliwości sygnału wejściowego, że $wywe=-3 "dB"$.

Skoro wiemy, że $U_"we"=1 "V"$, to $20log_10(U_"wy"\/1 "V") = -3 "dB"$, a więc $U_"wy" approx 0.707 "V"$.
Żeby $U_"wy" = 0.707 "V"$, częstotliwość musi być $tilde 440 "Hz"$, czyli teoretyczna $f_g approx 440 "Hz"$.
Teoretyczną częstotliwość graniczną porównamy później z wartością wyznaczoną z pomiarów.

#figure(
  image("./img/2.3.03_sinus_fg.png"),
  caption: [Przebieg sygnałów z częstotliwością równą częstotliwości granicznej $f_g=440 "Hz"$],
)

Następnie zmierzono częstotliwość i przesunięcie fazowe dla częstotliwości:
- od 100 Hz do 1000 Hz z krokiem 100 Hz,
- od 1 kHz do 10 kHz z krokiem 1 kHz,
- od 10 kHz do 30 kHz z krokiem 10 kHz,
Dla większych częstotliwości zmiany sygnału były zaniedbywalne. Zdjęcia ekranu oscyloskopu z pomiarami znajdują się w notatkach.
// TODO: Link do notatek

=== Charakterystka amplitudowa i fazowa
#figure(
  image("./img/rc_amp_graph.svg", width: 86.5%),
  caption: [Wykres stosunku amplitud #wywe w funkcji częstotliwości],
) <rc_amp_graph>

#figure(
  image("./img/rc_phase_graph.svg", width: 86.5%),
  caption: [Wykres przesunięcia fazowego w funkcji częstotliwości],
) <rc_phase_graph>


#grid(
  columns: (1fr, 1fr),
  [
    #figure(
      table(
        columns: 2,
        align: (left, center),
        table.header([Częstotliwość $f$ [Hz]], [$U_"wy" \/ U_"we"$]),
        [100], [0.9682],
        [200], [0.9038],
        [300], [0.8242],
        [400], [0.7357],
        [500], [0.6555],
        [600], [0.5922],
        [700], [0.5282],
        [800], [0.4798],
        [900], [0.4396],
        [1000], [0.3998],
        [2000], [0.2162],
        [3000], [0.1360],
        [4000], [0.1040],
        [5000], [0.0880],
        [6000], [0.0720],
        [7000], [0.0559],
        [8000], [0.0560],
        [9000], [0.0400],
        [10 000], [0.0400],
        [20 000], [0.0160],
        [30 000], [0.0080],
      ),
      caption: [Dane do wykresu stosunku amplitud (@rc_amp_graph)],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        align: (left, center),
        table.header([Częstotliwość $f$ [Hz]], [Faza $phi$ [°]]),
        [100], [-12.6],
        [200], [-24.06],
        [300], [-33.7],
        [400], [-40.61],
        [500], [-47.93],
        [600], [-53.42],
        [700], [-57.12],
        [800], [-60.37],
        [900], [-63.16],
        [1000], [-65.47],
        [2000], [-76.63],
        [3000], [N/A],
        [4000], [N/A],
        [5000], [N/A],
        [6000], [N/A],
        [7000], [N/A],
        [8000], [N/A],
        [9000], [N/A],
        [10 000], [N/A],
        [20 000], [N/A],
        [30 000], [N/A],
      ),
      caption: [Dane do wykresu przesunięcia fazy (@rc_phase_graph)],
    )
  ],
)

\
Jak oczekiwano, dla wysokich częstotliwości napięcie jest tłumione oraz następuje przesunięcie fazy o około $-90 degree$.

Niestety podczas pomiarów nie zauważyłem, że skala amplitudy sygnału wyjściowego była zbyt niska, przez co algorytm obliczania fazy zawiódł. Stąd wynikają wpisy "N/A" dla fazy częstotliwości $>=3000 "Hz"$.

Górną częstotliwość graniczną  wyznaczono z charakterystyki amplitudowej jako częstotliwość, dla której $20 log_10(wywe) = -3 "dB"$, co odpowiada $wywe approx 0.707$. Z tabeli oraz wykresu @rc_amp_graph widać, że wartość ta leży pomiędzy punktami $f=400 "Hz"$, dla którego $wywe = 0.7357$, oraz $f=500 "Hz"$, dla którego $wywe = 0.6555$. Stosując interpolację liniową:
$
  f_g approx 400 "Hz" + (500 "Hz" - 400 "Hz") dot frac(0.707 - 0.7357, 0.6555 - 0.7357) approx 436 "Hz"
$
Na podstawie pomiarów otrzymano górną częstotliwość graniczną równą około $436 "Hz"$. Jest to wartość bardzo zbliżona do wartości teoretycznej $440 "Hz"$, a względna różnica wynosi około $0.9%$.

Kąt przesunięcia fazy dla zmierzonej częstotliwości granicznej można wyznaczyć z charakterystyki fazowej. Ponieważ $f_g approx 436 "Hz"$ leży pomiędzy punktami $400 "Hz"$ i $500 "Hz"$, zastosowano interpolację liniową na podstawie wartości $phi = -40.61 degree$ dla $400 "Hz"$ oraz $phi = -47.93 degree$ dla $500 "Hz"$:
$
  phi(f_g) approx -40.61 degree + (-47.93 degree - (-40.61 degree)) dot frac(436 "Hz" - 400 "Hz", 500 "Hz" - 400 "Hz") approx -43.25 degree
$

=== Fala prostokątna w układzie całkującym
Podano na wejście falę prostokątną o okresach z zakresu $0.5tau "-" 10tau$ z krokiem $1tau$:

#grid(
  columns: 2,
  column-gutter: .5em,
  row-gutter: 1em,
  [ #figure(image("./img/2.3.23_0.5t.png"), caption: [$T=0.5tau$]) ],
  [ #figure(image("./img/2.3.24_1.5t.png"), caption: [$T=1.5tau$]) ],

  [ #figure(image("./img/2.3.25_2.5t.png"), caption: [$T=2.5tau$]) ],
  [ #figure(image("./img/2.3.26_3.5t.png"), caption: [$T=3.5tau$]) ],

  [ #figure(image("./img/2.3.27_4.5t.png"), caption: [$T=4.5tau$]) ],
  [ #figure(image("./img/2.3.28_5.5t.png"), caption: [$T=5.5tau$]) ],

  [ #figure(image("./img/2.3.29_6.5t.png"), caption: [$T=6.5tau$]) ],
  [ #figure(image("./img/2.3.30_7.5t.png"), caption: [$T=7.5tau$]) ],

  [ #figure(image("./img/2.3.31_8.5t.png"), caption: [$T=8.5tau$]) ],
  [ #figure(image("./img/2.3.32_9.5t.png"), caption: [$T=9.5tau$]) ],
)
#figure(
  image("./img/2.3.33_5t_czas_narastania.png"),
  caption: [$T=5tau$]
)
Z powyższych obrazków można zaobserwować, że układ całkujący zmienia impuls wejściowy z prostokątnego na trójkątny dla $T <= tau$, a dla $T > tau$ krawędź trójkąta zmienia się w parabolę o różnej wypukłości.

Dla $T=5tau$ czas narastania impulsu był równy $1/2T=2.5tau$, ponieważ sygnał wyjściowy narastał cały czas gdy sygnał wejściowy był wysoki.

== Podsumowanie
Przeprowadzone pomiary potwierdziły, że badany układ RC działa jak filtr dolnoprzepustowy. Dla małych częstotliwości stosunek amplitud #wywe był bliski 1, natomiast wraz ze wzrostem częstotliwości malał, co zgadza się z przewidywaniami teoretycznymi.

Charakterystyka fazowa również była zgodna z teorią: dla niskich częstotliwości przesunięcie fazowe było bliskie $0 degree$, natomiast dla wysokich częstotliwości dążyło do $-90 degree$. W wyższych zakresach częstotliwości nie udało się wyznaczyć fazy, co wynikało z zawodności algorytmu pomiaru fazy przy bardzo małych amplitudach sygnału wyjściowego.

Wyznaczona z pomiarów górna częstotliwość graniczna wyniosła około $436 "Hz"$ i była bardzo bliska wartości teoretycznej $440 "Hz"$, a kąt przesunięcia fazy dla częstotliwości granicznej wyniósł około $-43.25 degree$.

Zaobserwowano również jak zachowuje się układ całkujący gdy podano falę prostokątną.
