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
#let wywe = $U_"wy"\/U_"we"$
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
  title: "Elektronika cyfrowa - sprawozdanie 3",
  authors: ("Mateusz Wojtyna",),
)

#heading([Dane], numbering: none, level: 3, outlined: false)
- stanowisko nr 02
- miernik uniwersalny nr 09

#outline()
#pagebreak()

= Zadanie 1
== Treść
Zapoznać się ze schematem ideowym układu wzmacniacza operacyjnego.

== Wstęp teoretyczny
Sprzężeniem zwrotnym nazywa się oddziaływanie skutku na przyczynę, za pomocą czego można wpływać na własności urządzeń elektronicznych.

Podstawowym układem elektronicznym, w którym stosuje się sprzężenie zwrotne jest
*wzmacniacz*. Część sygnału wyjściowego, zwana sygnałem zwrotnym, zostaje skierowana
do wejścia układu i zsumowana z sygnałem wejściowym.

#grid(
  columns: (auto, auto),
  [
    #figure(
      image("./img/wzmacniacz.jpg"),
      caption: [Wzmacniacz bez sprzężenia zwrotnego],
    ) <cr_T>
  ],
  [
    #figure(
      image("./img/wzmacniacz_sprzezenie.jpg", width: 95%),
      caption: [Wzmacniacz z sprzężeniem zwrotnym],
    ) <cr_phi>
  ],
) \

*Wzmacniacz operacyjny* jest to wzmacniacz o bardzo dużym wzmocnieniu napięciowym, który posiada dwa wejścia i jedno wyjście. Jedno z wejść jest wejściem odwracającym – sygnał wyjściowy jest przesunięty w fazie o $180 degree$ względem sygnału przyłożonego do tego wejścia. Drugie wejście nazywa się nieodwracającym – sygnał wyjściowy jest zgodny w fazie z sygnałem podanym na to wejście. Zasilane są napięciami stałymi $U_"CC"$, $U_"EE"$.

Wzmacniacz operacyjny realizuje funkcję
$
U_"wy" = K(U_+ - U_-)
$

#figure(
  image("./img/wzmacniacz_operacyjny.jpg", width: 50%),
  caption: [Schemat wzmacniacza operacyjnego]
)

== Praktyka
+ zrób zdjęcie płytki ze wzmacniaczem #figure(
  image("./img/3.1.01_invamp_topview.jpeg", width: 84%),
  caption: [Płytka ze wzmacniaczem operacyjnym]
) \

+ zanotuj wartości napięć na pinach $plus.minus 12 "V"$
Wartość napięcia na pinie $+12 "V"$ wyniosła $11.98 "V"$, a na pinie $-12 "V"$ wyniosła $-11.96 "V"$.

== Podsumowanie
Zapoznano się ze schematem wzmacniacza operacyjnego oraz zmierzono napięcie na pinach $plus.minus 12 "V"$, które niewiele się różniło od wartości oczekiwanej.

#pagebreak()

= Zadanie 2
== Treść
Zmontować wzmacniacz odwracający fazę o wzmocnieniu 10. Zdjąć charakterystykę częstotliwościową i fazową.

== Wstęp teoretyczny
Wzmacniacz odwracający fazę to wzmacniacz operacyjny, gdzie sygnał wejściowy podajemy na wejście odwracające (−) przez rezystor $R_1$, a sprzężenie zwrotne realizujemy rezystorem $R_2$. Wejście nieodwracające (+) podłączamy do masy ($0 "V"$).

#figure(
  image("./img/wzmacniacz_odwracajacy.jpg"),
  caption: [Schemat wzmacniacza odwracającego fazę]
)
