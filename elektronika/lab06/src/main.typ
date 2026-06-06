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
  caption: [Schemat układu z zadania 1]
)

== Wstęp teoretyczny
Aby kontrolować napięcie za pomocą potencjometru, wykorzystałem dzielnik napięcia złożony z dwóch rezystorów, których oporność można kontrolować potencjometrami. 

== Praktyka
#figure(
  image("img/1.01_komparator_topview.jpeg"),
  caption: [Układ z komparatorem]
)

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

