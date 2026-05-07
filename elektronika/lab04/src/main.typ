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
Zapoznano się z budową i przeznaczeniem płytki UC-1. Sprawdzono, czy płytka działa popranie.

#pagebreak()

= Notatki
#raw(read("./notatki.txt"))
