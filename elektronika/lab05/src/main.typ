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

#grid(
  columns: 2,
  gutter: 1em,
  inset: (top: 1em, bottom: 1em),
  [
    #figure(image("./img/7474.png"), caption: [Schemat układu 7474])
  ],
  [
    #figure(image("./img/7474_table.png"), caption: [Tabela logiczna układu 7474])
  ],
)


Wejścia `PR` oraz `CLR` działają asynchronicznie, więc wymuszają stan wyjść niezależnie od sygnału zegarowego i wejścia `D`. Są one aktywne stanem niskim: podanie zera logicznego na `PR` ustawia wyjście `Q` w stan wysoki, natomiast podanie zera logicznego na `CLR` zeruje przerzutnik i wymusza `Q` = 0. Jednoczesne uaktywnienie obu wejść asynchronicznych jest stanem niedozwolonym, ponieważ prowadzi do niejednoznacznego działania układu.

#pagebreak()
== Praktyka
Najpierw zmierzono kilka wielkości:
- napięcie $5 "V"$ wyniosło $5.04 "V"$,
- rezystor $1000 space Omega$ w rzeczywistości miał oporność $990 space Omega$,
- rezystor $400 space Omega$ w rzeczywistości miał oporność $393 space Omega$.

\
Następnie złożono układ realizujący przerzutnik jednozboczowy D. Przetestowano działanie wejść `PR` oraz `CLR`. Poniższy schemat połączeń jest identyczny dla wszystkich zdjęć.

#figure(
  table(
    columns: 2,
    table.header([*Od*], [*Do*]),
    [Impulsator górny], [`CLK1`],
    [Impulsator dolny], [`D1`],
    [`Q1`], [Próbnik],
    [+5 V], [`Vcc`],
    [0 V], [`GND`],
  ),
  caption: [Schemat połączeń 7474],
)

=== PR=1, CLR=1
W tej konfiguracji przerzutnik zapamiętuje podany stan.
Nagranie przedstawiające testowanie przerzutnika znajduje się #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQDatjfgIwZ5QofoZ1x_eXK4AdmNmsgBKPtfzJJnMCcmS80?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=VpN9Vh")[#underline("tutaj")].

#v(-1em)
#figure(
  image("./img/1.01_PR=H_CLR=H.jpeg", width: 98%),
  caption: [Przerzutnik jednozboczowy D: `PR`=`1`, `CLR`=`1`],
)

=== PR=L, CLR=H
W tej konfiguracji przerzutnik zawsze podaje stan wysoki.
Nagranie przedstawiające testowanie przerzutnika (próba przełączenia na stan niski) znajduje się #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQB-sUV5GQp0Rb4skTAqQAqzATgSHPA0ojAFTfSHEKWoX6M?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=RnRfFj")[#underline("tutaj")].

#v(-1em)
#figure(
  image("./img/1.03_PR=L_CLR=H.jpeg", width: 78%),
  caption: [Przerzutnik jednozboczowy D: `PR`=`0`, `CLR`=`1`],
)

=== PR=H, CLR=L
W tej konfiguracji przerzutnik zawsze podaje stan niski.
Nagranie przedstawiające testowanie przerzutnika (próba przełączenia na stan wysoki) znajduje się #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQDCXZo-NJ-kRrs3oFJCcP87AbZ7h5WvekGL7d9hygM5F7I?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=w3c06H")[#underline("tutaj")].

#v(-1em)
#figure(
  image("./img/1.05_PR=H_CLR=L.jpeg", width: 78%),
  caption: [Przerzutnik jednozboczowy D: `PR`=`1`, `CLR`=`0`],
)

== Podsumowanie
Badany układ 7474 działał zgodnie z tabelą logiczną przerzutnika D. Przy
nieaktywnych wejściach asynchronicznych, czyli dla `PR`=`1` i `CLR`=`1`,
przerzutnik zapamiętywał stan podany na wejście `D` w chwili zbocza sygnału
zegarowego. Potwierdza to, że w normalnym trybie pracy układ może być traktowany
jako jednobitowy element pamiętający sterowany zegarem.

Sprawdzono również działanie wejść asynchronicznych. Podanie stanu niskiego na
wejście `PR` powodowało wymuszenie stanu wysokiego na wyjściu, niezależnie od
sygnałów `D` i `CLK`. Analogicznie podanie stanu niskiego na wejście `CLR`
zerowało przerzutnik i wymuszało stan niski na wyjściu. Otrzymane wyniki
potwierdzają, że wejścia `PR` i `CLR` są aktywne stanem niskim oraz mają
priorytet względem pracy synchronicznej przerzutnika.

Zmierzona wartość napięcia zasilania wynosiła $5.04 "V"$, a wartości użytych
rezystorów były bliskie wartościom nominalnym, dlatego zastosowane poziomy
logiczne były poprawne dla układu TTL.

#pagebreak()

= Zadanie 2
== Treść
Wybierz jeden z czterech przerzutników D Latch (wyzwalanych poziomem) w układzie scalonym 7475 i zbadaj jego działanie. Podaj na wejście zegarowe sygnał taktujący z impulsatora płytki UC-1. Na wejście informacyjne podaj sygnał z drugiego impulsatora przed, w czasie trwania oraz po sygnale taktującym. Opisz działanie tego przerzutnika.

== Wstęp teoretyczny
Przerzutnik D Latch, to przerzutnik D, który pozwala na zmianę stanu gdy impuls zegara jest w stanie wysokim, a w stanie niskim zapamiętuje obecny stan.

#grid(
  columns: 2,
  gutter: 1em,
  inset: (top: 1em, bottom: 1em),
  [
    #figure(image("./img/7475.png", width: 90%), caption: [Schemat układu 7475])
  ],
  [
    #figure(image("./img/7475_table.png", width: 80%), caption: [Tabela logiczna układu 7475])
  ],
)

Układ 7575 nie posiada wejść `PR` oraz `CLR`.

== Praktyka
Złożono układ realizujący przerzutnik D Latch. Przetestowano działanie układu.

#figure(
  table(
    columns: 2,
    table.header([*Od*], [*Do*]),
    [Impulsator górny], [`1C, 2C`],
    [Impulsator dolny], [`1D`],
    [`Q1`], [Próbnik],
    [+5 V], [`Vcc`],
    [0 V], [`GND`],
  ),
  caption: [Schemat połączeń 7475],
)

Nagranie przedstawiające testowanie przerzutnika znajduje się #link("https://ujchmura-my.sharepoint.com/:v:/g/personal/mateusz_wojtyna_student_uj_edu_pl/IQAEl6wo__FXSYrylW993rXEAcE3MiXsPzsh1Uf6NrOBGNk?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=Pmz3KN")[#underline("tutaj")]. Jak oczekiwano, stan można zmienić tylko wtedy, jeśli sygnał zegara jest w stanie wysokim.

#figure(
  image("./img/2.01_topview.jpeg"),
  caption: [Przerzutnik D Latch na płytce UC-1]
)

== Podsumowanie
Badany układ 7475 działał zgodnie z zasadą pracy przerzutnika D Latch. Gdy wejście zegarowe znajdowało się w stanie wysokim, zmiana stanu na wejściu `D` była bezpośrednio przenoszona na wyjście `Q`.

Po przejściu sygnału zegarowego do stanu niskiego wyjście zachowywało ostatnią
wartość zapamiętaną przed zakończeniem impulsu zegarowego. Zmiany podawane na
wejście `D` przy niskim stanie zegara nie wpływały już na stan wyjścia.
Potwierdza to, że układ 7475 jest przerzutnikiem wyzwalanym poziomem, a nie
zboczem, jak układ 7474 badany w poprzednim zadaniu.

Wyniki doświadczenia potwierdziły poprawne działanie zatrzasku D oraz zgodność
obserwacji z tabelą logiczną układu 7475.

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
