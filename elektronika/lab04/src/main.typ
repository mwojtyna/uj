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

#set image(width: 80%)
#show grid: set image(width: 100%)

#set figure(supplement: [Obraz])
#show figure.caption: set text(hyphenate: false)
#show figure.where(kind: table): set figure(supplement: [Tabela])
#show table: set table(stroke: 0.5pt)
#set enum(numbering: "a)")

#maketitle(
  title: "Elektronika cyfrowa - sprawozdanie 4",
  authors: ("Mateusz Wojtyna, gr 9",),
)

#heading([Dane], numbering: none, level: 3, outlined: false)
- stanowisko nr 02
- miernik uniwersalny nr 15

#outline()
#pagebreak()

= Zadanie 1
== Treść
Zapoznać się z płytką UC-1 do badania układów scalonych TTL.

== Wstęp teoretyczny
#grid(
  columns: (auto, auto),
  column-gutter: 1em,
  [
    #figure(
      image("./img/uc-1.jpg"),
      caption: [Schemat płytki UC-1],
    )
  ],
  [
    #figure(
      image("./img/1a.01_plytka_topdown.jpeg"),
      caption: [Płytka UC-1],
    )
  ],
)

#v(1em)
Płytka UC-1 służy do testowania układów scalonych. Zbudowana jest z kilku części:
+ *zasilanie 5V* - zasila płytkę i wpięte układy scalone,
+ *impulsator* - przyciski wysyłające impuls napięcia na piny $Q$ oraz $overline(Q)$ (negacja),
+ *próbnik/wskaźnik* - pokazuje jaki impuls logiczny jest podany na piny za pomocą diod LED,
+ *wejście na układ scalony* - po przełożeniu dźwigni, piny z układu scalonego zostają połączone z pinami na płytce, dzięki czemu można te układy na niej testować.

== Praktyka
Zgodnie z kartą pracy, wykonano co poniżej:
+ napięcie na pinach zasilania 5V wyniosło $5.02 "V"$ na lewym wejściu i $5.01 "V"$ na prawym,
+ impulsatory działają poprawnie, co sprawdzono na oscyloskopie (@impuls_oscy), wyraźnie widać falę prostokątną,
+ gdy impulsator jest włączony, wszystkie jego wyjścia mają napięcie $5 "V"$, gdy jest wyłączony, mają $0 "V"$,
+ sprawdzono działanie próbnika, tabela logiczna wszystkich wyjść impulsatora przedstawiona w (@impuls_table),
+ sprawdzono, że wszystkie diody wskaźnika działają poprawnie.

#figure(
  table(
    columns: 3,
    table.header([], [*$Q$*], [*$overline(Q)$*]),
    [*OFF*], [0], [1],
    [*ON*], [1], [0],
  ),
  caption: [Tabela logiczna impulsatora],
) <impuls_table>

#figure(
  image("./img/1c.03_impulsator_test_oscy.png"),
  caption: [Włączony impulsator],
) <impuls_oscy>

== Podsumowanie
Zapoznano się z budową i przeznaczeniem płytki UC-1. Sprawdzono, czy płytka działa poprawnie. Przedstawiono impuls logiczny na oscyloskopie.

#pagebreak()

= Zadanie 2
== Treść
Zbadać tablicę logiczną dla następujących bramek logicznych NAND (7400), NOR (7402), Ex-OR (7486) mierząc poziomy odpowiednich napięć, a następnie sprawdzając je próbnikiem stanów logicznych.

== Wstęp teoretyczny
=== NAND
Bramka NAND to bramka logiczna przedstawiona za pomocą następującej tabeli prawdy:
#figure(
  table(
    columns: 3,
    table.header([*$A$*], [*$B$*], [*$A dot B$*]),
    [0], [0], [1],
    [0], [1], [1],
    [1], [0], [1],
    [1], [1], [0],
  ),
  caption: [Tabela logiczna NAND],
) <nand_truth>

Układ scalony NAND (7400) realizujący funkcję logiczną NAND przedstawiony jest na następującym schemacie:
#figure(
  image("./img/nand.jpg", width: 25%),
  caption: [Schemat układu NAND (7400)],
)
Piny `xA` oraz `xB` to wejścia, piny `xY` to wyjścia. Napięcie stałe wprowadzamy do pinu `Vcc`, uziemienie do `GND`.

#pagebreak()

=== NOR
Bramka NOR to bramka logiczna przedstawiona za pomocą następującej tabeli prawdy:
#figure(
  table(
    columns: 3,
    table.header([*$A$*], [*$B$*], [*$A + B$*]),
    [0], [0], [1],
    [0], [1], [0],
    [1], [0], [0],
    [1], [1], [0],
  ),
  caption: [Tabela logiczna NOR],
) <nor_truth>

Układ scalony NOR (7402) realizujący funkcję logiczną NOR przedstawiony jest na następującym schemacie:
#figure(
  image("./img/nor.jpg", width: 25%),
  caption: [Schemat układu NOR (7402)],
)
Piny `xA` oraz `xB` to wejścia, piny `xY` to wyjścia. Napięcie stałe wprowadzamy do pinu `Vcc`, uziemienie do `GND`.

=== XOR
Bramka XOR to bramka logiczna przedstawiona za pomocą następującej tabeli prawdy:
#figure(
  table(
    columns: 3,
    table.header([*$A$*], [*$B$*], [*$A xor B$*]),
    [0], [0], [0],
    [0], [1], [1],
    [1], [0], [1],
    [1], [1], [0],
  ),
  caption: [Tabela logiczna XOR],
) <xor_truth>

Układ scalony XOR (7486) realizujący funkcję logiczną XOR przedstawiony jest na następującym schemacie:
#figure(
  image("./img/xor.jpg", width: 25%),
  caption: [Schemat układu XOR (7486)],
)
Piny `xA` oraz `xB` to wejścia, piny `xY` to wyjścia. Napięcie stałe wprowadzamy do pinu `Vcc`, uziemienie do `GND`.

== Praktyka
=== NAND
Podłączono bramkę NAND do płytki UC-1. Na wejścia do bramki podano wyjścia $Q$ z obu impulsatorów (dalej nazwane $Q_1$ oraz $Q_2$).

#v(1em)
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/2.01_nand.jpeg"),
      caption: [NAND na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_2$], [`1B`],
        [Próbnik], [`1Y`],
        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń wejść/wyjść bramki NAND],
    )
  ],
)

#v(1em)
Napięcia stanów logicznych wyniosły: $V_"high" = 3.61 "V"$, $V_"low" = 65.4 "mV"$.\
Po zmierzeniu napięć dla każdej kombinacji stanów $Q_1$, $Q_2$, tablica logiczna tej bramki jest zgodna z teorią (@nand_truth).

=== NOR
Podłączono bramkę NOR do płytki UC-1. Na wejścia do bramki podano wyjścia $Q$ z obu impulsatorów (dalej nazwane $Q_1$ oraz $Q_2$).

#v(1em)
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/2.02_nor.jpeg"),
      caption: [NOR na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_2$], [`1B`],
        [Próbnik], [`1Y`],
        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń wejść/wyjść bramki NOR],
    )
  ],
)

#v(1em)
Napięcia stanów logicznych wyniosły: $V_"high" = 3.62 "V"$, $V_"low" = 48.8 "mV"$.\
Po zmierzeniu napięć dla każdej kombinacji stanów $Q_1$, $Q_2$, tablica logiczna tej bramki jest zgodna z teorią (@nor_truth).

=== XOR
Podłączono bramkę XOR do płytki UC-1. Na wejścia do bramki podano wyjścia $Q$ z obu impulsatorów (dalej nazwane $Q_1$ oraz $Q_2$).

#v(1em)
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/2.03_xor.jpeg"),
      caption: [XOR na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_2$], [`1B`],
        [Próbnik], [`1Y`],
        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń wejść/wyjść bramki XOR],
    )
  ],
)

#v(1em)
Napięcia stanów logicznych wyniosły: $V_"high" = 3.62 "V"$, $V_"low" = 48.8 "mV"$.\
Po zmierzeniu napięć dla każdej kombinacji stanów $Q_1$, $Q_2$, tablica logiczna tej bramki jest zgodna z teorią (@xor_truth).

== Podsumowanie
Zbadano działanie bramek logicznych NAND, NOR oraz XOR z użyciem płytki UC-1. Dla każdej bramki sprawdzono wszystkie kombinacje stanów wejściowych, zmierzono napięcia odpowiadające stanom logicznym wysokim i niskim oraz potwierdzono wyniki próbnikiem stanów logicznych. Otrzymane tablice logiczne były zgodne z tabelami prawdy badanych bramek, co potwierdza poprawne działanie układów scalonych 7400, 7402 oraz 7486.

#pagebreak()

= Zadanie 3
== Treść
Używając funktorów NAND (7400), NOR (7402) zbudować układ realizujący iloczyn logiczny, sumę logiczną, funkcję negacji. Sprawdzić tablicę logiczną funktorów używając próbnika stanów logicznych.

== Wstęp teoretyczny
Za pomocą funktora NAND albo NOR można stworzyć dowolny układ logiczny. Poniżej przedstawiam jak zrealizować układy NOT, AND, NOR za pomocą tych funktorów.

=== Bramka NOT
Za pomocą NAND:
$ "NOT"(A) = overline(A) = overline(A) + overline(A) = overline(A dot A) = "NAND"(A,A) $
#figure(
  image("./img/not_with_nand.png", width: 40%),
  caption: [NOT za pomocą NAND],
)

Za pomocą NOR:
$ "NOT"(A) = overline(A) = overline(A) dot overline(A) = overline(A + A) = "NOR"(A,A) $
#figure(
  image("./img/not_with_nor.png", width: 40%),
  caption: [NOT za pomocą NOR],
)

=== Bramka AND
Za pomocą NAND:
$
  "AND"(A,B) = A dot B = overline(overline(A dot B)) = overline("NAND"(A,B))\
  = "NAND"("NAND"(A,B),space"NAND"(A,B))
$
#figure(
  image("./img/and_with_nand.png", width: 70%),
  caption: [AND za pomocą NAND],
)

Za pomocą NOR:
$
  "AND"(A,B) = A dot B = overline(overline(A)) dot overline(overline(B)) = overline(overline(A) + overline(B)) = "NOR"(overline(A), overline(B))\ =
  "NOR"("NOR"(A,A),space"NOR"(B,B))
$
#figure(
  image("./img/and_with_nor.png", width: 70%),
  caption: [AND za pomocą NOR],
)

=== Bramka OR
Za pomocą NAND:
$
  "OR"(A,B) = A + B = overline(overline(A)) + overline(overline(B)) = overline(overline(A) dot overline(B)) = "NAND"(overline(A), overline(B))\
  = "NAND"("NAND"(A,A),space"NAND"(B,B))
$
#figure(
  image("./img/or_with_nand.png", width: 70%),
  caption: [OR za pomocą NAND],
)

Za pomocą NOR:
$
  "OR"(A,B) = A + B = overline(overline(A + B)) = overline("NOR"(A,B))\
  = "NOR"("NOR"(A,B),space"NOR"(A,B))
$
#figure(
  image("./img/or_with_nor.png", width: 70%),
  caption: [OR za pomocą NOR],
)

== Praktyka
=== NOT
Za pomocą NAND:
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/3.01_nand_not.jpeg"),
      caption: [NOT za pomocą NAND na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_2$], [`1B`],
        [`1Y`], [Próbnik],
        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń bramki NAND],
    )
  ],
)

#v(1em)
Za pomocą NOR:
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/3.04_nor_not.jpeg"),
      caption: [NOT za pomocą NOR na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_2$], [`1B`],
        [`1Y`], [Próbnik],
        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń  bramki NOR],
    )
  ],
)

#pagebreak()

=== AND
Za pomocą NAND:
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/3.02_nand_and.jpeg"),
      caption: [AND za pomocą NAND na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_2$], [`1B`],

        [`1Y`], [`2A`],
        [`1Y`], [`2B`],
        [`2Y`], [Próbnik],

        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń  bramki NAND],
    )
  ],
)

#v(1em)
Za pomocą NOR:
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/3.05_nor_and.jpeg"),
      caption: [AND za pomocą NOR na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_1$], [`1B`],
        [$Q_2$], [`2A`],
        [$Q_2$], [`2B`],

        [`1Y`], [`4B`],
        [`2Y`], [`4A`],
        [`4Y`], [Próbnik],

        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń bramki NOR],
    )
  ],
)

#pagebreak()

=== OR
Za pomocą NAND:
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/3.03_nand_or.jpeg"),
      caption: [OR za pomocą NAND na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_1$], [`1B`],
        [$Q_2$], [`2A`],
        [$Q_2$], [`2B`],

        [`1Y`], [`4A`],
        [`2Y`], [`4B`],
        [`4Y`], [Próbnik],

        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń  bramki NAND],
    )
  ],
)

#v(1em)
Za pomocą NOR:
#grid(
  columns: 2,
  column-gutter: -1em,
  [
    #figure(
      image("./img/3.06_nor_or.jpeg"),
      caption: [OR za pomocą NOR na płytce UC-1],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        table.header([*Od*], [*Do*]),
        [$Q_1$], [`1A`],
        [$Q_2$], [`1B`],

        [`1Y`], [`4B`],
        [`1Y`], [`4A`],
        [`4Y`], [Próbnik],

        [+5 V], [`Vcc`],
        [0 V], [`GND`],
      ),
      caption: [Schemat połączeń bramki NOR],
    )
  ],
)

== Podsumowanie
Zbudowano układy realizujące funkcje NOT, AND oraz OR wyłącznie z funktorów NAND i NOR. Dla każdej funkcji sprawdzono dwie realizacje: na układzie NAND (7400) oraz na układzie NOR (7402). Wyniki obserwowane na próbniku stanów logicznych były zgodne z oczekiwanymi tabelami prawdy, co potwierdza, że bramki NAND i NOR są funktorami pełnymi i mogą być użyte do realizacji podstawowych operacji logicznych.

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
