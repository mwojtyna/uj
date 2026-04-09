#import "@preview/rubber-article:0.5.2": *

#let vv(body) = math.bold(math.upright(body))
#let wywe = $U_"wy"/U_"we"$
#set math.mat(delim: "[", column-gap: 1em)
#set math.vec(delim: "[")

// #set image(width: 80%)
// #show grid: set image(width: 100%)

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
  title: "Elektronika cyfrowa - sprawozdanie 2",
  authors: ("Mateusz Wojtyna",),
  date: "08 kwietnia 2026",
)

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
  image("./img/cr_schemat.png", width: 60%),
  caption: [Schemat układ CR],
) <cr>

Układ różniczkujący (CR) to czwórnik bierny o układzie zilustrowanym w @cr. Kondensator jest podłączony do wejścia, rezystora oraz wyjścia, natomiast rezystor jest podłączony do masy. Układ CR można m.in. stosować do filtrowania sygnałów o małej częstotliwości (@cr_T). Funkcja przejścia dla układu CR wynosi
$
               T(omega) & = frac(j omega/omega_0, 1 + j omega/omega_0) \
  "gdzie" space omega_0 & = 1/(R C) = 1/tau \
$

#figure(
  image("./img/cr_T.png", width: 60%),
  caption: [Wykres transmitancji układu względem częstotliwości],
) <cr_T>

== Praktyka
Zmontowano układ różniczkujący na płytce RLC zgodnie ze schematem w @cr. Pojemność kondensatora wynosi $63 "nF"$. Wykorzystano rezystor R2 z oporem równym $tilde 5.56 "k"Omega$, dzięki czemu stała czasowa $tau=R C=0.3503 "ms" in [0.1, 1] "ms"$.

#figure(
  [
    #grid(
      columns: (1fr, 1fr),
      gutter: 0.5em,
      [
        #image("img/2.1.02_rlc_topdown.jpeg")
      ],
      [
        #image("img/2.1.01_rlc_wideview.jpeg")
      ],
    )
  ],
  caption: [Układ RC zmontowany na płytce RLC],
)

Przed zmierzeniem #wywe dla szerokiego zakresu częstotliwości, zmierzono go dla $U=1 "V"$ oraz $f=1 "kHz"$. We wszystkich wykresach poniżej, oryginalny sygnał jest w kolorze żółtym, zmodyfikowany w kolorze niebieskim.

#figure(
  image("img/2.1.03_1V_1kHz_sinus.png"),
  caption: [$wywe = 0.904$, $phi = 335.9degree$ dla $U=1 "V", f=1 "kHz"$]
)

Następnie wyliczono wartość teoretyczną częstotliwości granicznej $f_g approx 450 "Hz"$, czyli takiej częstotliwości sygnału wejściowego, że $wywe=-3 "dB"$.
Stosunek ampliud można wyrazić w $"dB"$ wzorem $20 * log_10(wywe)$. Teoretyczną częstotliwość graniczną porównamy później z wartością wyznaczoną z wykresów.

#figure(
  image("img/2.1.04_sinus_fg.png"),
  caption: [Przebieg sygnałów z częstotliwością $f_g=450 "Hz"$ sygnału wejściowego]
)

Następnie zmierzono częstotliwość i przesunięcie fazowe dla częstotliwości:
 - od 100 Hz do 1000 Hz z krokiem 100 Hz,
 - od 1 kHz do 10 kHz z krokiem 1 kHz,
 - od 10 kHz do 100 kHz z krokiem 10 kHz,
 - od 100 kHz do 300 kHz z krokiem 100 kHz.

Wszystkie zdjęcia ekranu oscyloskopu z powyższymi pomiarami znajdują się w notatkach.

#figure(
  image("./img/amp_graph.png"),
  caption: [Wykres log-log stosunku amplitud w funkcji częstotliwości]
)
Jak oczekiwano, dla niskich częstotliwości napięcie jest tłumione.

#figure(
  image("./img/phase_graph.png"),
  caption: [Wykres log-log przesunięcia fazowego w funkcji częstotliwości]
)

