#import "@preview/rubber-article:0.5.0": *

#let vv(body) = math.bold(math.upright(body))
#set math.mat(delim: "[", column-gap: 1em)
#set math.vec(delim: "[")
#set image(width: 80%)

#set figure(supplement: [Obraz])
#show figure.caption: set text(hyphenate: false)
#show figure.where(kind: table): set figure(supplement: [Tabela])

#show: article.with(
  cols: none,
  heading-numbering: "1.",
  lang: "pl",
  page-margins: 2.5cm,
  page-paper: "a4",
  text-size: 12pt,
)

#maketitle(
  title: "Elektronika cyfrowa - sprawozdanie 1",
  authors: ("Mateusz Wojtyna",),
  date: "22 marca 2026",
)

#outline()
#pagebreak()

= Zadanie 1
== Treść
Zapoznać się z działaniem generatora funkcyjnego i oscyloskopu. Wykonać kilka pomiarów
amplitudy i częstotliwości sygnałów sinusoidalnych oraz przesunięcia fazy pomiędzy dwoma
sygnałami o tej samej częstotliwości z wykorzystaniem kursorów oscyloskopu, a także funkcji
automatycznego pomiaru. Porównać zmierzone wartości z wartościami ustawień generatora.

== Wstęp teoretyczny
=== Oscyloskop
Jest to urządzenie, którego zadaniem jest mierzenie i badanie przebiegów napięcia elektrycznego w czasie. Umożliwia pomiar m.in. amplitudy, częstotliwości oraz przesunięcia fazy badanych przebiegów.

=== Generator funkcyjny
Urządzenie, które służy do generowanie napięć o danym kształcie (sinusoida, prostokąt, trójkąt) oraz amplitudzie, częstotliwości i przesunięciu fazowym.

// \
// #align(center)[
//   #grid(
//     columns: (50%, 50%),
//     gutter: 1em,
//     [
//       #figure(
//         image("img/oscyloskop_schemat.png", width: 100%),
//         caption: [Schemat oscyloskopu Tektronix MSO22]
//       ) <oscy>
//     ],
//     [
//       #figure(
//         image("img/generator_schemat.png", width: 100%),
//         caption: [Schemat generatora Tektronix AFG3000]
//       ) <gen>
//     ]
//   )
// ]

#figure(
  image("img/oscyloskop_schemat.png", width: 55%),
  caption: [Schemat oscyloskopu Tektronix MSO22],
) <oscy>
#figure(
  image("img/generator_schemat.png", width: 55%),
  caption: [Schemat generatora Tektronix AFG3000],
) <gen>

== Praktyka

=== Zapoznanie się z działaniem oscyloskopu (zob. @oscy)

*Polecenie*: Włączyć kanały 1 i 2.
Ustawić skalę pionową na kanale 1 na
500 mV, na kanale 2 na 100 mV.
Skalę poziomą ustawić na 10 ns.
Przesunąć sygnał z 1 kanału na 2/8
wysokości ekranu, od góry, sygnał z 2
kanału na środku ekranu.

\
*Kroki*:
+ Włączamy kanały wciskając odpowiednie przyciski (5).
+ Ustawiamy skale pionowe i poziome wybierając kanał przyciskami (5) i kręcąc odpowiednimi pokrętłami _Scale_.
+ Zmieniamy położenie kręcąc pokrętłami _Position_ lub korzystając z myszki.
+ Zapisujemy obraz interfejsu w formacie PNG za pomocą programu _TekScope Utility_.

#figure(
  image("img/1.1.01_skala_polozenie.png"),
  caption: [Widok sygnałów po konfiguracji],
)

#pagebreak()

=== Zapoznanie się z działaniem generatora funkcyjnego (zob. @gen)
*Polecenie*: Na 2 drugie wejście oscyloskopu podać
sygnał trójkątny o amplitudzie 1.55 Vpp
i częstotliwości 15 kHz.
Powiększyć sygnał na oscyloskopie na
pełen ekran.
Po potwierdzeniu przez prowadzącego
poprawności wykonania zadania,
zapisać obraz w formie PNG i ASCII.

\
*Kroki*:
+ Podłączamy przewód BNC do kanału Ch1 generatora i wejścia Ch1 oscyloskopu. Naciskamy przycisk _On_ nad odpowiednim wyjściem z generatora.
+ Ustawiamy kształt sygnału odpowiednim przyciskiem wyboru funkcji.
+ Naciskamy przycisk generatora _Amplitude/High_ oraz wpisujemy napięcie.
+ Naciskamy przycisk generatora _Frequency/Period_ oraz wpisujemy częstotliwość.

#figure(
  image("img/1.1.02_generator_load1.jpeg", width: 60%),
  caption: [
    Ustawienie generatora ($66.overline(6) space mu s = 15$ kHz)\ (niestety wkradł się błąd, powinno być 1.550 Vpp)
  ],
)

#align(center)[
  #grid(
    columns: (50%, 50%),
    gutter: 1em,
    [
      #figure(image("img/1.1.03_trojkat_10x.png", width: 100%), caption: [Skala 10x])
    ],
    [
      #figure(image("img/1.1.04_trojkat_1x.png", width: 100%), caption: [Skala 1x]) <1x>
    ],
  )
]

\
Dodatkowo należało zmienić skalowanie sondy na 1x zamiast domyślnego 10x w celu poprawnego wyświetlania napięcia. Można to zrobić otwierając menu kanału (lewy dolny róg) $arrow$ _Probe Setup_ $arrow$ _Attenuation_.

\
Jednakże dalej widać (@1x), że amplituda jest nadal niepoprawna (2x większa). Wynika to z niepoprawnego ustawienia oczekiwanej impedancji oscyloskopu. Należy zmienić ustawienie _Output menu_ $arrow$ _Load Impedance_ $arrow$ _High Z_ w generatorze dla odpowiedniego kanału.

\
#align(center)[
  #grid(
    columns: (48%, 52%),
    gutter: 1em,
    [
      #figure(image("img/1.1.06_generator_load3.jpeg", width: 100%), caption: [Ustawienie _High Z_])
    ],
    [
      #figure(image("img/1.1.07_trojkat_1x_dobry_opor.png", width: 100%), caption: [Poprawna amplituda])
    ],
  )
]

=== Zapoznanie się z mierzeniem wielkości za pomocą oscyloskopu
*Polecenie*: Sporządzić tabelę porównującą wyniki pomiarów amplitudy i
częstotliwości metodami “na oko”, za pomocą kursorów i
wbudowanych funkcji oscyloskopu, dla sygnałów z generatora
o podanych parametrach.

\
*Opis metod*:
- *Metoda "na oko"*: liczenie kratek oraz szybka i nieprecyzyjna interpolacja wyników. Używana żeby szybko sprawdzić czy pomiary mają sens.
- *Użycie kursorów*: dopasowanie linii do punktów charakterystycznych sygnału. Pozwala na dość precyzyjne odczytanie właściwości sygnału, jednakże dalej jest kontrolowane przez człowieka co może skutkować błędami pomiarowymi.
- *Użycie wbudowanych funkcji*: automatyczne odczytywanie właściwości sygnału używające wbudowanych algorytmów. Najbardziej precyzyjne, jednak czasami zawodne dla niektórych sygnałów.


#pagebreak()

#figure(
  image("img/1.1.09_tabelka_sinus_cursor_amp.png"),
  caption: [Sinusoida (1 V, 3 kHz) - amplituda mierzona \ kursorem oraz wbudowaną funkcją],
)
#figure(
  image("img/1.1.08_tabelka_sinus_cursor_freq.png"),
  caption: [Sinusoida (1 V, 3 kHz) - częstotliwość mierzona metodą kursorów oraz wbudowaną funkcją],
)

#figure(
  image("img/1.1.10_tabelka_trojkat_cursor_amp.png", width: 60%),
  caption: [Trójkąt (2.5 V, 10 kHz, 10$degree$) - amplituda mierzona \ kursorem oraz wbudowaną funkcją],
)
#figure(
  image("img/1.1.11_tabelka_trojkat_cursor_freq.png", width: 60%),
  caption: [Trójkąt (2.5 V, 10 kHz, 10$degree$) - częstotliwość \ mierzona metodą kursorów oraz wbudowaną funkcją],
)
#figure(
  image("img/1.1.12_tabelka_trojkat_faza.jpeg", width: 60%),
  caption: [Trójkąt (2.5 V, 10 kHz, 10$degree$) - generator],
)

#figure(
  image("img/1.1.13_tabelka_square_cursor_amp.png", width: 60%),
  caption: [Prostokąt (0.5 V, 50 kHz, 180$degree$) - amplituda \ mierzona kursorem oraz wbudowaną funkcją],
)
#figure(
  image("img/1.1.14_tabelka_square_cursor_freq.png", width: 60%),
  caption: [Prostokąt (0.5 V, 50 kHz, 180$degree$) - częstotliwość \ mierzona metodą kursorów oraz wbudowaną funkcją],
)
#figure(
  image("img/1.1.15_tabelka_square_faza.jpeg", width: 60%),
  caption: [Prostokąt (0.5 V, 50 kHz, 180$degree$) - generator],
)

#[
  #set table(
    stroke: 1pt + black,
    // fill: (x, y) => if y == 0 { luma(40) } else if y > 4 and y < 9 { luma(235) },
    inset: 7pt,
  )

  #figure(
    kind: table,
    table(
      columns: (1fr, 1fr, 1fr, 1fr),
      align: center + horizon,

      [*Sygnał*], [*Metoda*], [*Amplituda [V]*], [*Częstotliwość [kHz]*],

      table.cell(rowspan: 3)[Sinus\ 0 V, 3 kHz, $0degree$],
      [Na oko], [1.000], [3.07],
      [Kursory], [1.016], [3.03],
      [Measure], [1.016], [3.00],

      table.cell(rowspan: 3)[Trójkąt\ 2.5 V, 10 kHz, $10degree$],
      [Na oko], [2.500], [9.80],
      [Kursory], [2.457], [10.02],
      [Measure], [2.500], [10.00],

      table.cell(rowspan: 3)[Prostokąt\ 0.5 V, 50 kHz, $180degree$],
      [Na oko], [0.500], [50.00],
      [Kursory], [0.500], [50.05],
      [Measure], [0.528], [50.00],
    ),
    caption: [Porównanie wartości otrzymanych różnymi metodami],
  )
]

== Wnioski
W przypadku liczb będących wielokrotnością obecnej precyzji wykresu, metoda "na oko" daje wyniki bardzo zbliżone do faktycznych parametrów sygnału. Jednakże aby gwarantować precyzję pomiaru należy stosować kursory i wbudowane funkcje pomiarowe.

#pagebreak()

= Zadanie 2
== Treść
Wykorzystując tryb X–Y oscyloskopu
zaobserwować efekt złożenia dwóch
drgań harmonicznych (krzywe
Lissajous) dla jednakowych i różnych
częstotliwości sygnałów w szerokim
zakresie przesunięcia fazy.

== Wstęp teoretyczny
Krzywa Lissajous to krzywa parametryczna dana równaniem
$
  cases(
    x(t) = A_1 sin(omega_1 t + phi),
    y(t) = A_2 sin(omega_2 t)
  )
$
Kształt krzywych zależy głównie od stosunku $omega_1/omega_2$ oraz $phi$.

#figure(
  image("img/lissajous.jpg"),
  caption: [Kształt krzywej Lissajous w zależności od parametrów],
)

#pagebreak()

== Praktyka
Aby zaobserwować krzywe Lissajous, należy uruchomić tryb X-Y oscyloskopu w menu _Horizontal_ $arrow$ X-Y Plot. Przedstawia on wartość kanału Ch2 jako funkcję kanału Ch1.

#figure(
  image("img/1.2.01_xy.png"),
  caption: [Ustawienie trybu X-Y],
)

Przetestowano wygląd krzywych Lissajous dla ustawień:
- 1:1, $0degree$
- 1:1, $45degree$
- 1:1, $90degree$
- 1:2, $0degree$
- 1:3, $90degree$

#figure(
  image("img/1.2.02_lissajous_1to1_0deg.png"),
  caption: [Poprawna krzywa Lissajous (1:1, $0degree$)],
)
#figure(
  image("img/1.2.03_lissajous_1to1_45deg.png"),
  caption: [Poprawna krzywa Lissajous (1:1, $45degree$)],
)
#figure(
  image("img/1.2.04_lissajous_1to1_90deg.png"),
  caption: [Poprawna krzywa Lissajous (1:1, $90degree$)],
)
#figure(
  image("img/1.2.05_lissajous_1to2_0deg.png"),
  caption: [#underline[Niepoprawna] krzywa Lissajous (1:2, $0degree$)],
) <wrong_curve>
#figure(
  image("img/1.2.06_lissajous_1to3_90deg.png"),
  caption: [Poprawna krzywa Lissajous (1:3, $90degree$)],
)

== Wnioski
Zaobserwowane krzywe w większości zgadzały się z przewidywaniami teoretycznymi. Jedynie krzywa o parametrach 1:2, $0degree$ (@wrong_curve) nie zgadza się z oczekiwaniami. Może to wynikać ze zużycia generatora.

#pagebreak()

= Zadanie 3
== Treść
Wykonać sumowanie dwóch sygnałów sinusoidalnych o jednakowych amplitudach i zbliżonych
częstotliwościach (np. 1000 i 1050 Hz). Zaobserwować zjawisko dudnień, wykonać pomiar
częstotliwości wypadkowej oraz częstotliwości dudnień. Wyniki pomiarów porównać
z wartościami teoretycznymi.

== Wstęp teoretyczny
Możemy zaobserwować efekt dudnienia gdy sumujemy dwa przebiegi sinusoidalne o różnych częstotliwościach (ale których różnica jest mała w stosunku do ich modułów) i jednakowych amplitudach.

#figure(
  image("img/dudnienie.png", width: 68%),
  caption: [Przykład dudnienia],
) <dudnienie>

Zjawisko dudnień charakteryzuje się dwoma częstotliwościami:
- *częstotliwością wypadkową ($f_w$)*: częstotliwość sygnału sumarycznego \ (czerwonego na @dudnienie), będąca średnią arytmetyczną częstotliwości sygnałów dodawanych,
- *częstotliwością dudnień ($f_d$)*: odwrotność okresu czasu pomiędzy dwoma sąsiednimi maksimami lub zerami obwiedni (czarnego obwodu na @dudnienie).

=== Wartości teoretyczne
Dla częstotliwości sygnałów $f_1 = 1000" Hz"$, $f_2 = 1050" Hz"$:
$
  f_w & = (f_1 + f_2) / 2 = (1000 + 1050) / 2 = 1025 "Hz"
$
$
  f_d & = |f_1 - f_2| = |1000 - 1050| = 50 "Hz"
$

#pagebreak()

== Praktyka
Nadajemy dwa przebiegi na generatorze: o częstotliwości 1000 Hz i 1050 Hz. W tym celu należy nacisnąć przycisk _On_ nad wyjściem kanału 2 z generatora (zob. @gen). Następnie ustawiamy odpowiednie parametry na generatorze.

#align(center)[
  #grid(
    columns: (50%, 50%),
    gutter: 1em,
    [
      #figure(image("img/1.3.01_sum_generator1.jpeg", width: 100%), caption: [Kanał 1 - 1000 Hz])
    ],
    [
      #figure(image("img/1.3.02_sum_generator2.jpeg", width: 100%), caption: [Kanał 2 - 1050 Hz])
    ],
  )
]
\
Następnie należy ustawić tryb sumowania przebiegów w oscyloskopie. Można to zrobić przez naciśnięcie przycisku _Math_ w segmencie (5) (zob. @oscy) lub wybraniu tej opcji na ekranie. Pojawi się wtedy sygnał koloru pomarańczowego będącego sumą sygnałów z wybranych kanałów.

#figure(
  image("img/1.3.03_sum_setup.png"),
  caption: [Tryb sumowania],
)

Po wyłączeniu wyświetlania kanału Ch1 oraz Ch2 i zwiększeniu skali poziomej, można wyraźnie zaobserwować efekt dudnień.

#figure(
  image("img/1.3.04_sum.png"),
  caption: [Dudnienie],
)

Następnie dokonujemy pomiaru częstotliwości wypadkowej oraz częstotliwości dudnień za pomocą kursorów.


#align(center)[
  #grid(
    columns: (50%, 50%),
    gutter: 1em,
    [
      #figure(
        image("img/1.3.05_freq_wypadkowa.png", width: 100%),
        caption: [Częstotliwość \ wypadkowa],
      )
    ],
    [
      #figure(
        image("img/1.3.06_freq_dudnien.png", width: 100%),
        caption: [Częstotliwość \ dudnień],
      )
    ],
  )
]

#align(center)[
  #figure(
    kind: table,
    table(
      columns: (auto, auto, auto),
      inset: 10pt,
      align: horizon + center,
      stroke: 1pt + black,

      [*Wielkość*], [*Wartość teoretyczna*], [*Wartość zmierzona*],

      [Częstotliwość wypadkowa $f_w$], [1025 Hz], [1030 Hz],

      [Częstotliwość dudnień $f_d$], [50 Hz], [50.05 Hz],
    ),
    caption: [Porównanie wyników pomiarów częstotliwości dudnień z wartościami oczekiwanymi],
  )
]

== Wnioski
Wyniki są zgodne z wartościami teoretycznymi. Błąd pomiarowy jest bardzo mały.

#pagebreak()

= Zadanie 4
== Treść
Zbudować dzielnik napięcia składający się z dwóch rezystorów (wykorzystać oporniki R1 i R2
na płytce montażowej z elementami RLC). Zbadać działanie dzielnika podając na wejście
napięcia zmienne sinusoidalne z generatora przy ustalonej częstotliwości \ ($f < 10 "kHz"$).
Pomiary napięć (amplitud) $U_"we"$, $U_"wy"$ wykonać dla pięciu różnych wartości $U_"we"$ z zakresu 0 do 10 V.
W opracowaniu wyników przedstawić punkty pomiarowe na wykresie $U_"wy"$ = $U_"wy"$ ($U_"we"$).
Metodą regresji liniowej wyznaczyć współczynnik proporcjonalności pomiędzy $U_"wy"$ a $U_"we"$ oraz porównać go z wartością teoretyczną wynikającą z prawa Ohma.

== Wstęp teoretyczny
Dzielnik napięcia to pasywny obwód elektroniczny, który dostarcza na wyjściu napięcie będące ułamkiem napięcia wejściowego.

#figure(
  image("img/rlc.png"),
  caption: [Schemat układu dzielnika napięcia],
)

Napięcie wyjściowe dzielnika przedstawionego powyżej jest zależne od napięcia wejściowego następującym wzorem:

$
  U_"wy" = R_2I = R_2 U_"we"/(R_1+R_2) = R_2/(R_1+R_2)U_"we"
$

#pagebreak()

== Praktyka
Na zajęciach nie wystarczyło czasu na skończenie ćwiczenia, więc wykonano jedynie układ, który kopiuje sygnał.

#figure(
  image("img/1.4.01_plytka.jpeg"),
  caption: [Układ zrealizowany na płytce RLC. W tle widać dwa sygnały na oscyloskopie, oryginalny i skopiowany.],
)

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
