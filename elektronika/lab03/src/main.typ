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
      caption: [Schemat wzmacniacza ze sprzężeniem zwrotnym],
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
  )

#v(1em)

+ zanotuj wartości napięć na pinach $plus.minus 12 "V"$
Wartość napięcia na pinie $+12 "V"$ wyniosła $11.98 "V"$, a na pinie $-12 "V"$ wyniosła $-11.96 "V"$.

== Podsumowanie
Zapoznano się ze schematem wzmacniacza operacyjnego oraz zmierzono napięcie na pinach $plus.minus 12 "V"$, które niewiele się różniło od wartości oczekiwanej.

#pagebreak()

= Zadanie 2
== Treść
Zmontować wzmacniacz odwracający fazę o wzmocnieniu 10. Zdjąć charakterystykę częstotliwościową i fazową.

== Wstęp teoretyczny
Wzmacniacz odwracający fazę to wzmacniacz operacyjny, gdzie sygnał wejściowy podajemy na wejście odwracające (−) przez rezystor $R_1$, a sprzężenie zwrotne realizujemy rezystorem $R_2$. Wejście nieodwracające (+) podłączamy do masy ($0 "V"$). Napięcie wyjściowe dane jest wzorem:
$
  U_"wy" = - R_2/R_1 U_"we"
$
Znak minus przy ilorazie rezystancji oznacza odwrócenie fazy (przesunięcie o $180 degree$).

#figure(
  image("./img/wzmacniacz_odwracajacy.jpg", width: 60%),
  caption: [Schemat wzmacniacza odwracającego fazę],
)

== Praktyka
Aby uzyskać wzmocnienie $K=10$, wybrano oporniki o wartościach
#math.equation(
  block: true,
  numbering: none,
  $
    R_1 & = 9.96 "k"Omega approx 10 "k"Omega \
    R_2 & = 99.1 "k"Omega approx 100 "k"Omega"."
  $,
)
z rzeczywistym wzmocnieniem $K approx 9.95$.

#pagebreak()

Następnie zmontowano wzmacniacz na płytce.
#v(-1em)
#figure(
  grid(
    columns: (auto, auto),
    column-gutter: 0.5em,
    [ #image("./img/3.2.02_invamp_connected_topview.jpeg") ], [ #image("./img/3.2.03_invamp_connected_wideview.jpeg") ],
  ),
  caption: [Zmontowany wzmacniacz odwracający fazę],
)

Podano falę sinusoidalną $f=1 "kHz"$, $U=1 "V"$. Kolor #text("żółty", fill: yellow) to oryginalny przebieg, kolor #text("niebieski", fill: blue) oznacza wyjście ze wzmacniacza.
#figure(
  image("./img/3.2.03_1V_1kHz_sinus.png", width: 100%),
  caption: [Wzmocnienie fali $1 "kHz"$, $1 "V"$],
)
Jak widać, amplituda fali została wzmocniona $9.997/1.020 approx 9.8$ razy, co zgadza się z oczekiwaniami. Zaobserwowano też przesunięcie fazy o $181 degree$.

=== Charakterystyka amplitudowa i fazowa
#figure(
  image("./img/opamp_rev_amp_graph.svg", width: 87%),
  caption: [Wykres $U_"wy"$ w funkcji częstotliwości],
) <opamp_rev_amp>
#figure(
  image("./img/opamp_rev_phase_graph.svg", width: 87%),
  caption: [Wykres różnicy faz w funkcji częstotliwości],
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
        [100], [179.9],
        [200], [179.9],
        [300], [179.7],
        [400], [179.6],
        [500], [179.5],
        [600], [179.4],
        [700], [179.3],
        [800], [179.2],
        [900], [179.1],
        [1000], [179.0],
        [2000], [178.0],
        [3000], [177.0],
        [4000], [175.6],
        [5000], [174.2],
        [6000], [172.1],
        [7000], [169.2],
        [8000], [165.2],
        [9000], [160.1],
        [10 000], [154.6],
        [20 000], [122.3],
        [30 000], [112.0],
        [40 000], [106.9],
        [50 000], [102.8],
        [60 000], [100.2],
        [70 000], [97.9],
        [80 000], [95.9],
        [90 000], [93.9],
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

#pagebreak()

= Zadanie 3
== Treść
Zmontować sumator o dwóch wejściach. Zsumować drgania sinusoidalne z dwóch generatorów, obserwować zdudnienia przebiegów.

== Wstęp teoretyczny
=== Sumator
Sumator to wzmacniacz operacyjny odwracający fazę z dodatkowymi napięciami i rezystorami podłączonymi równolegle do wejścia odwracającego. Można go wykorzystać do sumowania napięć. Napięcie wyjściowe dane jest wzorem:
$
  U_"wy" = -R sum_(i=1)^n U_i/R_i
$
#figure(
  image("./img/wzmacniacz_sumator.png"),
  caption: [Schemat wzmacniacza sumującego],
)

=== Dudnienia
Dudnienie charakteryzuje się dwiema częstotliwościami ($f_1$, $f_2$ to częstotliwości sygnałów wejściowych):
- częstotliwością sygnału zsumowanego: $1/2(f_1+f_2)$,
- częstotliwością obwiedni: $|f_1-f_2|$.
Dudnienia można zaobserwować, jeśli $|f_1-f_2|$ jest wystarczająco małe.

#pagebreak()

== Praktyka
=== Sumowanie

Wybrano oporniki o wartościach:
#math.equation(
  block: true,
  numbering: none,
  $
      R & = 99.1 "k"Omega approx 100 "k"Omega \
    R_1 & = 9.96 "k"Omega approx 10 "k"Omega \
    R_2 & = 9.97 "k"Omega approx 10 "k"Omega"."
  $,
)
Wybrano napięcia $U_1=U_2=1 "V"$ z częstotliwościami $1 "kHz"$.

Teoretyczna wartość napięcia wyjściowego to (minus oznacza odwrócenie fazy):
$
  U_"wy" & = -99.1 "k"Omega ((1 "V")/(9.96 "k"Omega) + (1 "V")/(9.97 "k"Omega)) approx -19.89 "V".
$

#figure(
  grid(
    columns: (auto, auto),
    column-gutter: 0.5em,
    [ #image("./img/3.3.01_sumamp_topdown.jpeg") ], [ #image("./img/3.3.02_sumamp_wideview.jpeg") ],
  ),
  caption: [Zmontowany wzmacniacz sumujący],
)

#figure(
  image("./img/3.3.04_1V_1kHz_sum.png"),
  caption: [Zsumowane przebiegi $U_1=U_2=1 "V"$],
)

Faktyczne napięcie wyjściowe wyniosło $19.99 "V"$ oraz faza została odwrócona, zgodnie z oczekiwaniami.

=== Dudnienia
Po zmianie częstotliwości drugiego przebiegu na $1.1 "kHz"$ zaobserwowano dudnienia.

#figure(
  image("./img/3.3.05_1V_1kHz_1.1kHz_dudnienie.png"),
  caption: [Dudnienie na wyjściu wzmacniacza sumującego],
)
#figure(
  image("./img/3.3.06_1V_1kHz_1.1kHz_dudnienie_f_sumy.png", width: 100%),
  caption: [Pomiar częstotliwości sygnału zsumowanego],
)
#figure(
  image("./img/3.3.07_1V_1kHz_1.1kHz_dudnienie_f_obwiedni.png", width: 100%),
  caption: [Pomiar częstotliwości obwiedni],
)

Częstotliwość sygnału zsumowanego wyniosła $1.06 "kHz"$, a częstotliwość dudnień $100.57 "Hz"$.

== Podsumowanie
Zmontowany wzmacniacz sumujący działał zgodnie z teorią. Dla dwóch sygnałów sinusoidalnych o amplitudach $1 "V"$ i częstotliwości $1 "kHz"$ otrzymano na wyjściu napięcie o amplitudzie $19.99 "V"$, bardzo bliskie wartości teoretycznej $19.89 "V"$. Zaobserwowano również odwrócenie fazy sygnału wyjściowego, co jest zgodne z własnościami sumatora odwracającego.

Po zmianie częstotliwości drugiego generatora na $1.1 "kHz"$ pojawiło się zjawisko dudnień. Zmierzona częstotliwość sygnału zsumowanego wyniosła $1.06 "kHz"$, czyli wartość bliska średniej arytmetycznej częstotliwości sygnałów wejściowych. Natomiast częstotliwość obwiedni wyniosła $100.57 "Hz"$, czyli wartość bardzo zbliżoną do różnicy częstotliwości sygnałów wejściowych. Potwierdza to poprawne działanie układu oraz zgodność obserwacji z przewidywaniami teoretycznymi.

#pagebreak()

= Zadanie 4
== Treść
Dla zadanego napięcia histerezy równego $1 "V"$ zbudować przerzutnik Schmidta. Zaobserwować i odrysować przebiegi napięcia wyjściowego przy sinusoidalnym i trójkątnym napięciu wejściowym. Zmierzyć histerezę i wykreślić statyczną charakterystykę układu.

== Wstęp teoretyczny
=== Przerzutnik
*Przerzutniki* to układy elektroniczne wytwarzające prostokątne przebiegi napięciowe w wyniku szybkich procesów przełączania pomiędzy różnymi stanami. W przerzutnikach dwustanowych można wyróżnić dwie fazy odpowiadające niskiemu i wysokiemu poziomowi napięcia wyjściowego.
*Przerzutnik bistabilny (Schmitta)* posiada dwa stany stabilne. Do zmiany stanu wymagany jest sygnał zewnętrzny.

#v(1em)
#grid(
  columns: (1.506fr, 1fr),
  column-gutter: 1em,
  [
    #figure(
      image("./img/schmitt.png"),
      caption: [Schemat przerzutnika Schmitta],
    )
  ],
  [
    #figure(
      image("./img/histereza.png"),
      caption: [Histereza],
    ) <histereza>
  ],
)

=== Histereza
Kluczową cechą przerzutnika Schmitta jest histereza (@histereza) - różne progi przełączania "w górę" i "w dół".
Histereza jest ważna, ponieważ bez niej przy zaszumionym sygnale, który oscyluje wokół progu, wyjście chaotycznie skacze między $+"E"$ i $−"E"$. Dzięki histerezie żeby przełączyć się na przeciwny stan, sygnał musi zmienić się o $2U_p$, co eliminuje fałszywe przełączenia.
Próg przerzutu dany jest wzorem:
$
U_p = R_2/(R_1+R_2) dot (plus.minus E)
$

#pagebreak()

== Praktyka
Chcemy, aby szerokość histerezy było równe $1 "V"$, czyli żeby $2U_p= plus.minus 1 "V"$. Więc:
$
2U_p = 1 "V" \
2 R_2/(R_1+R_2) dot plus.minus E = plus.minus 1 "V" \
R_2/(R_1+R_2) dot plus.minus 20 "V" = plus.minus 1 "V" \
R_2/(R_1+R_2) = 1/20 = 50/1000 \
$

Wybrano oporniki:
#math.equation(
  block: true,
  numbering: none,
  $
    R_1 & = 992 space Omega approx 1000 space Omega \
    R_2 & = 49.7 space Omega approx 50 space Omega"."
  $,
)

Napięcie przerzutu wynosi:
$
U_p = (49.7 space Omega)/(992 space Omega + 49.7 space Omega) dot (plus.minus 10 "V") approx plus.minus 0.48 "V"
$
Czyli szerokość histerezy dla takich rezystorów wynosi $0.96 "V" approx 1 "V"$.

\
Następnie zbudowano przerzutnik Schmitta na płytce:
#v(-1em)
#figure(
  grid(
    columns: (auto, auto),
    column-gutter: 0.5em,
    [ #image("./img/3.4.01_topdown.jpeg") ], [ #image("./img/3.4.02_wideview.jpeg") ],
  ),
  caption: [Zmontowany przerzutnik Schmitta],
)

#figure(
  image("./img/3.4.03_histeresis_2V_1kHz.png", width: 100%),
  caption: [Działanie przerzutnika dla fali sinusoidalnej (dół), oraz wykres histerezy (góra)]
)

Z wykresu XY widać metodą "na oko", że szerokość histerezy wynosi około $0.8 "V"$.

== Podsumowanie
Zbudowany przerzutnik Schmitta działał zgodnie z przewidywaniami teoretycznymi. Dobór rezystorów $R_1 approx 1000 space Omega$ oraz $R_2 approx 50 space Omega$ pozwolił uzyskać napięcie przerzutu około $plus.minus 0.48 "V"$, co odpowiada szerokości histerezy równej około $0.96 "V"$, czyli praktycznie zgodnej z założoną wartością $1 "V"$.

Na podstawie obserwacji przebiegów oraz wykresu XY stwierdzono, że układ przełącza się skokowo pomiędzy dwoma stanami i wykazuje wyraźną histerezę o szerokości około $0.8 "V"$. Otrzymane wyniki potwierdzają poprawne działanie przerzutnika Schmitta oraz zgodność pomiarów z obliczeniami.
