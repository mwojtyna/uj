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
      caption: [Schemat wzmacniacza bez sprzężenia zwrotnego],
    )
  ],
  [
    #figure(
      image("./img/wzmacniacz_sprzezenie.jpg", width: 95%),
      caption: [Schemat wzmacniacza z sprzężeniem zwrotnym],
    )
  ],
) \

*Wzmacniacz operacyjny* jest to wzmacniacz o bardzo dużym wzmocnieniu napięciowym, który posiada dwa wejścia i jedno wyjście. Jedno z wejść jest wejściem odwracającym – sygnał wyjściowy jest przesunięty w fazie o $180 degree$ względem sygnału przyłożonego do tego wejścia. Drugie wejście nazywa się nieodwracającym – sygnał wyjściowy jest zgodny w fazie z sygnałem podanym na to wejście. Zasilane są napięciami stałymi $U_"CC"$, $U_"EE"$.

Wzmacniacz operacyjny realizuje funkcję
$
  U_"wy" = K(U_+ - U_-)
$

#figure(
  image("./img/wzmacniacz_operacyjny.jpg", width: 50%),
  caption: [Schemat wzmacniacza operacyjnego],
)

== Praktyka
+ zrób zdjęcie płytki ze wzmacniaczem #figure(
    image("./img/3.1.01_invamp_topview.jpeg", width: 100%),
    caption: [Płytka ze wzmacniaczem operacyjnym],
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
Wzmacniacz odwracający fazę to wzmacniacz operacyjny, gdzie sygnał wejściowy podajemy na wejście odwracające (−) przez rezystor $R_1$, a sprzężenie zwrotne realizujemy rezystorem $R_2$. Wejście nieodwracające (+) podłączamy do masy ($0 "V"$). Napięcie wyjściowe dane jest wzorem
$
  U_"wy" = - R_2/R_1 U_"we"
$
Znak minus przy ilorazie rezystancji oznacza odwrócenie fazy (przesunięcie o $180 degree$).

#figure(
  image("./img/wzmacniacz_odwracajacy.jpg", width: 60%),
  caption: [Schemat wzmacniacza odwracającego fazę],
)

== Praktyka
Aby uzyskać wzmocnienie $K=10$, wybrano oporniki o teoretycznych wartościach
#math.equation(
  block: true,
  numbering: none,
  $
    R_1 & = 100 "k"Omega \
    R_2 & = 10 "k"Omega"."
  $,
)

Prawdziwe wartości wyniosły
#math.equation(
  block: true,
  numbering: none,
  $
    R_1 & = 99.1 "k"Omega \
    R_2 & = 9.96 "k"Omega
  $,
)
ze wzmocnieniem $K approx 9.95$.

#pagebreak()

Następnie zmontowano wzmacniacz na płytce.
#figure(
  grid(
    columns: (auto, auto),
    column-gutter: 0.5em,
    [ #image("./img/3.2.02_invamp_connected_topview.jpeg") ],
    [ #image("./img/3.2.03_invamp_connected_wideview.jpeg") ],
  ),
  caption: [Zmontowany wzmacniacz odwracający fazę]
)

Podano falę sinusoidalną $f=1 "kHz"$, $U=1 "V"$. Kolor żółty to oryginalny przebieg, kolor niebieski oznacza wyjście ze wzmacniacza.
#figure(
  image("./img/3.2.03_1V_1kHz_sinus.png", width: 100%),
  caption: [Wzmocnienie fali $1 "kHz"$, $1 "V"$]
)
Jak widać, amplituda fali została wzmocniona $9.997/1.020 approx 9.8$ razy, co zgadza się z oczekiwaniami. Zaobserwowano też przesunięcie fazy o $181 degree$.

=== Charakterystyka amplitudowa i fazowa
#figure(
  image("./img/opamp_rev_amp_graph.svg", width: 87%),
  caption: [Wykres $U_"wy"$ w funkcji częstotliwości]
) <opamp_rev_amp>
#figure(
  image("./img/opamp_rev_phase_graph.svg", width: 87%),
  caption: [Wykres różnicy faz w funkcji częstotliwości]
) <opamp_rev_phase>

#grid(
  columns: (1fr, 1fr),
  [
    #figure(
      table(
        columns: 2,
        align: (left, center),
        table.header([Częstotliwość $f$ [Hz]], [$U_"wy"$ [V]]),
        [100], [9.997],
        [200], [9.997],
        [300], [9.997],
        [400], [9.997],
        [500], [9.997],
        [600], [9.997],
        [700], [9.997],
        [800], [9.997],
        [900], [9.997],
        [1000], [9.997],
        [2000], [9.997],
        [3000], [9.997],
        [4000], [9.997],
        [5000], [9.997],
        [6000], [9.840],
        [7000], [9.840],
        [8000], [9.761],
        [9000], [9.604],
        [10 000], [9.289],
        [20 000], [5.277],
        [30 000], [3.518],
        [40 000], [2.780],
        [50 000], [2.259],
        [60 000], [1.882],
        [70 000], [1.620],
        [80 000], [1.419],
        [90 000], [1.240],
        [100 000], [1.100],
        [200 000], [0.5441],
        [300 000], [0.3518],
        [400 000], [0.2559],
        [500 000], [0.2000],
        [600 000], [0.1679],
        [700 000], [0.1359],
        [800 000], [0.1199],
        [900 000], [0.1040],
      ),
      caption: [Dane do wykresu amplitudy wyjściowej (@opamp_rev_amp)],
    )
  ],
  [
    #figure(
      table(
        columns: 2,
        align: (left, center),
        table.header([Częstotliwość $f$ [Hz]], [Faza $phi$ [°]]),
        [100],     [179.9],
        [200],     [179.9],
        [300],     [179.7],
        [400],     [179.6],
        [500],     [179.5],
        [600],     [179.4],
        [700],     [179.3],
        [800],     [179.2],
        [900],     [179.1],
        [1000],    [179.0],
        [2000],    [178.0],
        [3000],    [177.0],
        [4000],    [175.6],
        [5000],    [174.2],
        [6000],    [172.1],
        [7000],    [169.2],
        [8000],    [165.2],
        [9000],    [160.1],
        [10 000],  [154.6],
        [20 000],  [122.3],
        [30 000],  [112.0],
        [40 000],  [106.9],
        [50 000],  [102.8],
        [60 000],  [100.2],
        [70 000],  [97.9],
        [80 000],  [95.9],
        [90 000],  [93.9],
        [100 000], [92.5],
        [200 000], [83.0],
        [300 000], [75.9],
        [400 000], [66.8],
        [500 000], [57.1],
        [600 000], [46.1],
        [700 000], [N/A],
        [800 000], [N/A],
        [900 000], [N/A],
      ),
      caption: [Dane do wykresu przesunięcia fazowego (@opamp_rev_phase)],
    )
  ],
)

== Podsumowanie
Znaleziono górną wartość częstotliwości ($f_g = 900 "kHz"$), dla której $U_"wy" <= 1/10 U_"we"$. \
Jak oczekiwano, układ wzmacnia sygnał o małych częstotliwościach $K$ razy. Im większa częstotliwość, tym słabiej wzmacnia, a po około $100 "kHz"$ układ osłabia sygnał. Można również zaobserwować zmniejszenie przesunięcia fazy. Dla częstotliwości $f>=700 space 000$ nie udało się zmierzyć przesunięcia fazy z powodu ograniczeń oscyloskopu.
