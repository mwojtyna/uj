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
  title: "Elektronika cyfrowa - sprawozdanie 5",
  authors: ("Mateusz Wojtyna, gr 9",),
)

#heading([Dane], numbering: none, level: 3, outlined: false)
- stanowisko nr 02
- miernik uniwersalny nr 06

#outline()
#pagebreak()

= Zadanie 1
== Treść
Zbadaj przerzutnik jednozboczowy D korzystając z układu scalonego 7474. Stan logiczny 1 podaj na wejścia za pomocą opornika 1 kΩ połączonego z +5 V, natomiast stan logicznego zera podaj za pomocą opornika około 400 Ω połączonego z 0 V lub połącz bezpośrednio wejście z 0 V napięcia zasilania. Do taktowania wejścia zegarowego użyj sygnału z impulsatora na płytce montażowej UC-1.

== Wstęp teoretyczny
Przerzutnik typu D jest podstawowym synchronicznym elementem pamiętającym, stosowanym w układach cyfrowych. Jego zadaniem jest zapamiętanie wartości logicznej doprowadzonej do wejścia danych `D` w chwili aktywnego zbocza sygnału zegarowego `CLK`. W przypadku przerzutnika jednozboczowego stan wyjścia nie zmienia się przez cały czas trwania impulsu zegarowego, lecz tylko w krótkim momencie przejścia zegara ze stanu niskiego do wysokiego. Dzięki temu przerzutnik może służyć jako jednobitowy rejestr, element synchronizujący lub część liczników i automatów sekwencyjnych.

#figure(
  image("./img/7474_table.png", width: 70%),
  caption: [Tabela logiczna układu 7474 (jednozboczowego)],
)

Wejścia `PR` oraz `CLR` działają asynchronicznie, więc wymuszają stan wyjść niezależnie od sygnału zegarowego i wejścia `D`. Są one aktywne stanem niskim: podanie zera logicznego na `PR` ustawia wyjście $Q$ w stan wysoki, natomiast podanie zera logicznego na `CLR` zeruje przerzutnik i wymusza $Q = 0$. Jednoczesne uaktywnienie obu wejść asynchronicznych jest stanem niedozwolonym, ponieważ prowadzi do niejednoznacznego działania układu.

== Praktyka
Najpierw zmierzono kilka wielkości:
- napięcie $5 "V"$ wyniosło $5.04 "V"$,
- rezystor $1000 space Omega$ w rzeczywistości miał oporność $990 space Omega$,
- rezystor $400 space Omega$ w rzeczywistości miał oporność $393 space Omega$.
