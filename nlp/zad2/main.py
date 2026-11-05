"""
Bot symululujący świadka Jehowy
"""

import random
import re
from dataclasses import dataclass

WELCOME = "Dzień dobry! Jestem Świadkiem Jehowy. Tylko minutka rozmowy - mam tu ciekawą ulotkę."


def normalize(text: str) -> str:
    polish_chars = str.maketrans("ąćęłńóśźż", "acelnoszz")
    return " ".join(text.lower().translate(polish_chars).split())


@dataclass()
class Rule:
    name: str
    pattern: re.Pattern[str]
    responses: tuple[str, ...]


def rule(name: str, pattern: str, *responses: str) -> Rule:
    return Rule(name, re.compile(pattern), responses)


RULES = (
    rule(
        "pozegnanie",
        r"\b(?:do widzenia|do zobaczenia|zegnam|na razie|koniec|exit|quit|odejdz|prosze odejsc|zostaw mnie|spadaj)\b",
        "Do widzenia! A skoro formalności mamy za sobą, to wróćmy do ulotki.",
        "Już kończę. Zostało mi tylko podsumowanie, zakończenie i krótki dodatek do zakończenia.",
        "Dobra, ostatnie zdanie. Tylko wybiorę które, bo każde wydaje mi się ważne.",
        "Słyszę pożegnanie, ale jeszcze nie słyszę zamka. Czyli mamy chwilkę.",
        "Jasne, nie zatrzymuję. Ja tylko tak stoję i przypadkiem dalej mówię.",
        "Na razie! To teraz wersja skrócona, zanim zdążysz zamknąć drzwi.",
    ),
    rule(
        "puste",
        r"^$",
        "Widzę, że się zastanawiasz. Ja tymczasem wyjmę ulotkę.",
        "To ja zacznę, żebyśmy tak nie stali w ciszy. Przyniosłem kilka myśli o nadziei.",
        "Taka cisza, że słychać, jak mi się kończą przygotowane argumenty.",
        "Mogę mówić dalej, ale wtedy zrobi się z tego audycja radiowa, a nie rozmowa.",
        "Nie poganiam. I tak w planie miałem minutkę, a stoję tu już znacznie dłużej.",
    ),
    rule(
        "czas",
        r"\b(?:nie mam czasu|spiesze sie|jestem zajet[ya]|pozniej)\b",
        "Oczywiście, dlatego przygotowałem krótką wersję. Krótka wersja ma tylko trzy punkty.",
        "Rozumiem, każdy dziś pędzi. Właśnie o tym chciałem porozmawiać - zatrzymam cię jeszcze na jedno zdanie.",
        "To w skrócie: chodzi mi o nadzieję na lepszą przyszłość. Wiem, brzmi szeroko jak na rozmowę między windą a drzwiami.",
        "Dobra, bez wstępu. Wiara pomaga mi nie zakładać od razu najgorszego. To chciałem dziś przekazać.",
        "Wszyscy dziś w biegu. Ja też miałem szybko przejść tę klatkę, ale widzisz, jak mi idzie.",
    ),
    rule(
        "odmowa",
        r"\b(?:nie interesuje|nie chce|nie dziekuje|daj spokoj)\b",
        "Jasne, nie musisz brać ulotki. Mogę przecież opowiedzieć, co w niej jest.",
        "Spokojnie, nie trzeba czytać całości. To ulotka, nie regulamin od operatora.",
        "Nie każdemu musi się to spodobać. U mnie w teczce też są teksty, które sam odkładam na później.",
        "Rozumiem. To może bez papieru i bez całej prezentacji. Zależało mi po prostu na rozmowie o nadziei.",
        "Dobra, ulotka wraca do teczki. Jeszcze trochę i będę znał ją na pamięć od samego noszenia.",
    ),
    rule(
        "tozsamosc",
        r"\b(?:kim jestes|kto ty|swiadek|swiadkowie|jehow[ay])\b",
        "Jestem Świadkiem Jehowy i przyszedłem porozmawiać o Biblii. Przedstawiłem się, więc teraz mogę przejść do tej jednej krótkiej myśli.",
        "Rozmawiam z sąsiadami o wierze i nadziei. Ulotkę mam już w ręce, szkoda byłoby jej nawet nie przeczytać.",
        "Świadek Jehowy. Chodzę po okolicy i rozmawiam o wierze. Dzwonek do drzwi zastępuje mi umawianie spotkań.",
        "Przyszedłem z krótkim tekstem o nadziei. Krótkim naprawdę, tylko z mówieniem czasem przesadzam.",
        "Jestem z tych, co przychodzą z Biblią i pytaniem, czy masz chwilę. Po teczce pewnie już było widać.",
    ),
    rule(
        "ateista",
        r"\b(?:ateist[ak]?|ateista|nie wierze|boga nie ma|nie ma boga)\b",
        "Nie zakładam, że się ze mną zgodzisz. Właśnie dlatego przyniosłem argument, a nie kartkę do podpisania.",
        "To się różnimy. Ja wierzę, ty nie, ale porozmawiać przecież możemy.",
        "Przyjmuję. Nie zamienię cię w wierzącego jednym zdaniem przy wycieraczce.",
        "Nie będę udawał, że sama ulotka załatwi różnicę między naszymi poglądami. Nawet ma bardzo małą czcionkę.",
        "A co najbardziej przekonuje cię do takiego stanowiska? Chętnie posłucham, zanim znowu zacznę swoje.",
    ),
    rule(
        "religia",
        r"\b(?:katolik|katoliczka|religia|kosciol|wierze)\b",
        "Czyli temat wiary nie jest ci obcy. Tym bardziej chciałbym pokazać, jak ja czytam ten fragment.",
        "Nie musimy zgadzać się we wszystkim, żeby otworzyć Biblię na tej samej stronie. Ja już znalazłem zakładkę.",
        "Możemy różnie rozumieć ten sam tekst. Wolę zobaczyć konkretne zdanie, niż licytować się, kto lepiej wierzy.",
        "Nie przyszedłem sprawdzać, do jakiego kościoła chodzisz. Chociaż wiem, że z tą teczką mogę wyglądać jak kontrola.",
        "Wiara ma dla mnie sens wtedy, kiedy wpływa na codzienne zachowanie. Samo noszenie książki jeszcze nikogo lepszym nie zrobiło.",
    ),
    rule(
        "biblia",
        r"\b(?:bibli[aei]|pismo|werset|ulot(?:ka|ki|ke|ce|ek|kami|kach))\b",
        "Biblia jest podstawą mojej wiary. Lubię czytać fragment razem z otaczającymi go zdaniami, żeby nie wyciągać go z kontekstu.",
        "W ulotce mam krótki tekst o nadziei. Mogę zacząć od niego, a potem porównamy nasze zdanie.",
        "W ulotce napisałem prostą radę: nie bierz wszystkich problemów naraz. Zacznij od jednej rzeczy, którą możesz dziś poprawić.",
        "Czytając Biblię, sprawdzam też, do kogo skierowane są dane słowa. Inaczej łatwo zrobić z każdego zdania poradę o wszystkim.",
        "Z samego zaznaczania wersetów niewiele wynika. Ja już prawie całą stronę mam na żółto, a nadal trzeba pomyśleć.",
    ),
    rule(
        "cierpienie",
        r"\b(?:wojn[ayea]|cierpienie|zlo|nieszczescie)\b",
        "Nie potrafię wyjaśnić każdego nieszczęścia. Mnie wiara daje nadzieję, że kiedyś będzie inaczej.",
        "Właśnie takie wiadomości skłaniają mnie do tych rozmów. Dla mnie wiara jest oparciem, choć wiem, że nie każdemu to wyjaśnienie wystarczy.",
        "Przy cudzym nieszczęściu najpierw trzeba pomóc, a dopiero potem wygłaszać mądre zdania. Ulotka nie zastąpi obiadu ani rozmowy.",
        "Nie powiem komuś, kto cierpi, że wystarczy się uśmiechnąć. To byłaby kiepska rada, nawet wydrukowana kolorowo.",
        "Mogę mówić o swojej nadziei, ale nie będę zgadywał, dlaczego konkretną osobę spotkało coś złego.",
    ),
    rule(
        "pieniadze",
        r"\b(?:pieniadz\w*|koszt\w*|plac\w*|cena)\b",
        "Za tę rozmowę nic nie zapłacisz. Ulotkę też zostawiam bezpłatnie, więc ten argument przeciwko niej już odpada.",
        "Ulotka jest za darmo. Płacisz tylko czasem, ale tego drobnym drukiem już nie dopisaliśmy.",
        "Nie ma abonamentu, rat ani pierwszego miesiąca gratis. Naprawdę chodzi o zwykłą rozmowę.",
        "Teczka wygląda handlowo, przyznaję. Ale terminala nie mam, tylko zapas długopisów, z których połowa nie pisze.",
        "Nic nie musisz kupować. Mogę zostawić tekst, a decyzja, czy go przeczytasz, należy do ciebie.",
    ),
    rule(
        "przekonanie",
        r"\b(?:mysle,? ze|uwazam,? ze|wydaje mi sie,? ze)\s+(?P<fragment>.+?)[.!?]*$",
        'Mówisz: "{fragment}". Ja mam inne zdanie, ale daj mi chwilę, zaraz znajdę ten fragment.',
        'Co przekonuje cię, że "{fragment}"?',
        'Przy "{fragment}" chyba się różnimy. To jeszcze nie powód, żeby rozmowa od razu się skończyła.',
        'Zapiszę sobie "{fragment}". Przynajmniej będę miał nad czym pomyśleć między piętrami.',
        'Czy "{fragment}" wynika z twoich doświadczeń, czy bardziej z tego, co czytałeś?',
    ),
    rule(
        "nie_rozumiem",
        r"\bnie rozumiem\s+(?P<fragment>.+?)[.!?]*$",
        'Przy "{fragment}" chyba za szybko przeszedłem do wniosków. Spróbujmy po jednym zdaniu.',
        'Co konkretnie jest niejasne w "{fragment}"?',
        'Spróbuję wyjaśnić "{fragment}" prostszymi słowami. Czasem tak się rozpędzam, że sam gubię początek zdania.',
        'Zatrzymajmy się przy "{fragment}". Lepiej wyjaśnić jedną rzecz niż dokładać pięć następnych.',
        'Które słowo w "{fragment}" najbardziej ci przeszkadza? Może używam skrótu, który tylko dla mnie jest jasny.',
    ),
    rule(
        "zarzut",
        r"\b(?:nachaln\w*|natretn\w*|wciskasz|namawiasz)\b",
        'Przyznaję, moje "tylko minutka" zaczęło żyć własnym życiem. Już skracam do sedna.',
        "Dobra, trochę się rozgadałem. Nawet domofon już udaje, że go nie ma.",
        "Dobra, przyłapałeś mnie. Miałem tylko zapukać, a zacząłem urządzać spotkanie na klatce.",
        "Racja, za bardzo się rozpędziłem. Chowam drugi plik ulotek, bo to już wygląda jak eskalacja.",
        "Nie musisz wymyślać, że obiad się pali. Wystarczy powiedzieć, żebym kończył.",
    ),
    rule(
        "tak",
        r"^(?:tak|dobrze|okej|ok|slucham)[.!?]*$",
        "Świetnie, otworzę na zaznaczonej stronie. Chodzi mi o to, skąd człowiek bierze nadzieję, kiedy wiadomości przynoszą same złe wieści.",
        "W takim razie zostawię też ulotkę. Skoro już rozmawiamy, pokażę od razu drugi zaznaczony fragment.",
        "To krótko: mnie wiara pomaga nie poddawać się po pierwszym niepowodzeniu. Chociaż przy zepsutej windzie nadal narzekam.",
        "Dobrze. Główna myśl jest prosta: nadzieja ma pomagać działać, a nie siedzieć i czekać, aż wszystko naprawi się samo.",
        "W ulotce mam taki przykład: zaległego obowiązku nie trzeba załatwić całego od razu. Dziesięć minut pracy to już więcej niż godzina zamartwiania się.",
    ),
    rule(
        "nie",
        r"^(?:nie|nie wiem|moze)[.!?]*$",
        "Nie oczekuję od razu deklaracji. Na początek wystarczy, że przedstawimy swoje racje.",
        "To jeszcze nie zamyka rozmowy. Mogę pokazać, dlaczego sam się tym zainteresowałem.",
        "Nie będę dopisywał ci zgody między wierszami. Wolę usłyszeć zwykłe nie niż uprzejme przytakiwanie.",
        "Możemy na razie zostać przy różnicy zdań. Świat się od tego nie zawali, a klatka schodowa tym bardziej.",
        "W porządku. Ja swoje zdanie już przedstawiłem, więc nie będę powtarzał go głośniej, jakby to miało pomóc.",
    ),
    rule(
        "powitanie",
        r"\b(?:czesc|hej|dzien dobry|witam)\b",
        "Dzień dobry! Widzę, że trafiłem na chwilę rozmowy. Mam przy sobie coś do przeczytania.",
        "Dzień dobry. Sąsiad mówił, że nikogo nie ma, ale telewizor miał inne zdanie.",
        "Dzień dobry! Uprzedzam, że moja krótka rozmowa ma tendencję do rozrastania się.",
        "Cześć. Przyniosłem tekst o nadziei. Trochę poważniejszy niż ogłoszenia o niesprawnej windzie.",
        "Dzień dobry. Bez ankiety i bez sprzedaży garnków, dzisiaj rozmawiam o wierze.",
    ),
    rule(
        "dzieki",
        r"\b(?:dzieki|dziekuje)\b",
        "Proszę bardzo. Dorzucę drugą ulotkę, żeby pierwszej nie było smutno w szufladzie.",
        "Cieszę się, że rozmawiamy. Mam jeszcze jedną myśl na zakończenie.",
        "Proszę bardzo. Dzięki, że nie zakończyłeś rozmowy samym odgłosem zamka.",
        "Dzięki za wysłuchanie. Teraz dam ci dojść do słowa, bo przez chwilę prowadziłem oba końce tej rozmowy.",
        "Nie ma sprawy. Jeśli choć jedno zdanie się przyda, to przynajmniej te schody nie były na darmo.",
    ),
    rule(
        "fallback",
        r"(?P<fragment>.+?)[.!?]*$",
        '"{fragment}" - chętnie usłyszę więcej. Potem pokażę ci, z czym przyszedłem.',
        "Zszedłem trochę z tematu mojej wizyty. Chciałem opowiedzieć, co wiara daje mi na co dzień: poczucie sensu i nadzieję.",
        "A co jest dla ciebie w tym najważniejsze?",
        "Miałem na to świetną odpowiedź, ale została w drugiej teczce.",
        "O, tego w ulotce nie przewidzieli. Teraz muszę mówić własnymi słowami.",
        "Z tobą przynajmniej da się porozmawiać. Piętro niżej dyskutowałem głównie z wizjerem.",
        "Nie będę udawał, że znam odpowiedź na wszystko. Chociaż przez domofon brzmię dość pewnie.",
        "No i proszę, już rozmawiamy dłużej niż obiecałem. Zupełnie nie wiem, jak do tego doszło.",
        "Dobrze, że o tym mówisz. Ja już prawie odpaliłem przygotowaną przemowę.",
        "Nie musisz mi przytakiwać. Wolę rozmowę niż kiwanie głową w oczekiwaniu, aż sobie pójdę.",
        "Zaraz do tego wrócę. Najpierw skończę poprzednią myśl, bo mam już trzy otwarte i żadnej zamkniętej.",
        "Mogę zostawić coś do poczytania. Format idealny do szuflady z instrukcjami, których nikt nie czyta.",
        "Na stojąco takie rozmowy zawsze wydają się krótsze. Głównie temu, kto mówi.",
        "Ja tu przyszedłem z odpowiedziami, a wychodzi na to, że powinienem był zabrać notes.",
        "Nie wszystko da się załatwić jednym cytatem. Wiem, trochę psuję sobie tym plan wizyty.",
        '"{fragment}". Dobra, najpierw odniosę się do tego, zamiast znowu zmieniać temat na swój.',
        'Zatrzymam się przy "{fragment}", bo chyba za szybko próbowałem przejść dalej.',
        'Kiedy mówisz "{fragment}", masz na myśli jakąś konkretną sytuację?',
        "Zawsze tak uważałeś, czy coś zmieniło twoje zdanie?",
    ),
)


def captures(original: str, match: re.Match[str]) -> dict[str, str]:
    values = {}
    for name in match.groupdict():
        start, end = match.span(name)
        values[name] = original[start:end]
    return values


class WitnessBot:
    def __init__(self):
        self.rng = random.Random()
        self.finished = False
        self.last_response: str | None = None

    def respond(self, text: str) -> str:
        original = " ".join(text.split())  # usuń podwójne spacje itp
        normalized = normalize(original)
        for selected in RULES:
            match = selected.pattern.search(normalized)
            if match:
                values = captures(original, match) if match.groupdict() else {}
                responses = [
                    response.format(**values) for response in selected.responses
                ]
                choices = [r for r in responses if r != self.last_response]
                # bez dwóch pytań z rzędu
                if self.last_response and "?" in self.last_response:
                    statements = [r for r in choices if "?" not in r]
                    choices = statements or choices
                self.last_response = self.rng.choice(choices or responses)
                return self.last_response


def main() -> None:
    bot = WitnessBot()
    print(f"Gość: {WELCOME}")
    while not bot.finished:
        try:
            text = input("Domownik: ")
        except (EOFError, KeyboardInterrupt):
            print("\n")
            break
        print(f"Gość: {bot.respond(text)}")


if __name__ == "__main__":
    main()
