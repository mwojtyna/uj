from collections import Counter
from pathlib import Path
from typing import Callable, NamedTuple

import matplotlib.pyplot as plt
import numpy as np
from lxml import etree
from matplotlib.figure import Figure
from numpy.typing import NDArray


class Word(NamedTuple):
    word: str
    lemma: str
    pos: str


def extractWordsFromTEI(filename: str) -> list[Word]:
    """
    Return words with their lemma and part of speech, if present.
    """

    result: list[Word] = []

    root = etree.parse(filename).getroot()
    TEI = {"tei": "http://www.tei-c.org/ns/1.0"}

    words = root.findall(".//tei:text//tei:w", namespaces=TEI)
    for w in words:
        result.append(Word(w.text or "", w.get("lemma") or "", w.get("pos") or ""))

    return result


def plotZipf(
    texts: dict[str, list[Word]],
    title: str,
    select: Callable[[Word], str] = lambda w: w.word,
) -> Figure:
    """Plot word frequencies against their ranks on logarithmic axes."""
    fig, ax = plt.subplots(figsize=(10, 6))
    reference_scale: float | None = None
    max_rank = 0

    for label, text in texts.items():
        counts = Counter(token for word in text if (token := select(word).casefold()))
        if not counts:
            continue
        if reference_scale is None:
            reference_scale = max(counts.values()) / counts.total()
        max_rank = max(max_rank, len(counts))

        frequencies = np.array(sorted(counts.values(), reverse=True), dtype=np.float64)
        ranks = np.arange(1, len(frequencies) + 1)
        relative_frequencies = frequencies / frequencies.sum()
        ax.loglog(
            ranks,
            relative_frequencies,
            marker=".",
            linestyle="none",
            markersize=3,
            label=f"{label} (N={counts.total()})",
        )

    if reference_scale is not None:
        ranks = np.arange(1, max_rank + 1)
        ax.loglog(
            ranks,
            reference_scale / ranks,
            "k--",
            label="Odniesienie: f(r) = C/r",
            alpha=0.7,
        )

    ax.set_title(title)
    ax.set_xlabel("Ranga słowa (log)")
    ax.set_ylabel("Częstość względna w danej grupie (log)")
    ax.grid(True, which="both", alpha=0.2)
    ax.legend()
    fig.tight_layout()
    return fig


def vocabularyGrowth(
    text: list[Word], select: Callable[[Word], str] = lambda w: w.word
) -> NDArray[np.int64]:
    """Count distinct types in successive prefixes, preserving token order."""
    seen: set[str] = set()
    sizes: list[int] = []
    for word in text:
        token = select(word).casefold()
        if not token:
            continue
        seen.add(token)
        sizes.append(len(seen))
    return np.array(sizes, dtype=np.int64)


def plotHeaps(
    texts: dict[str, list[Word]],
    title: str,
    select: Callable[[Word], str] = lambda w: w.word,
) -> Figure:
    """Plot the number of distinct words against the number of tokens read."""
    fig, ax = plt.subplots(figsize=(10, 6))

    for label, text in texts.items():
        sizes = vocabularyGrowth(text, select)
        if not len(sizes):
            continue
        tokens = np.arange(1, len(sizes) + 1)
        ax.plot(
            tokens,
            sizes,
            ".",
            markersize=2,
            label=f"{label} (N={len(sizes)}, V={sizes[-1]})",
            rasterized=True,
        )

    ax.set_title(title)
    ax.set_xlabel("Liczba przeczytanych tokenów")
    ax.set_ylabel("Liczba różnych wyrazów / lematów")
    ax.grid(True, alpha=0.2)
    ax.legend()
    fig.tight_layout()
    return fig


balucki_BialyMurzyn = extractWordsFromTEI("./xml/POL0001_balucki_bialy-murzyn.xml")
balucki_PanBurmistrz = extractWordsFromTEI("./xml/POL0002_balucki_pan-burmistrz.xml")
balucki_Przebudzeni = extractWordsFromTEI("./xml/POL0003_balucki_przebudzeni.xml")
sienkewicz_QuoVadis = extractWordsFromTEI("./xml/POL0071_sienkiewicz_quo-vadis.xml")
krzemienicka_Fatum = extractWordsFromTEI("./xml/POL0041_krzemieniecka_fatum.xml")
trollope_Armstrong = extractWordsFromTEI("./xml/ENG18400_Trollope.xml")
stifter_Feldblumen = extractWordsFromTEI("./xml/DEU023.xml")

PATH = Path(__file__).resolve().parent / "img"


def num1():
    """
    1. wybierając 3 teksty jednego autora w jednym dowolnym języku; przeanalizować wyrazy
    """
    texts = {
        "Biały Murzyn": balucki_BialyMurzyn,
        "Pan Burmistrz": balucki_PanBurmistrz,
        "Przebudzeni": balucki_Przebudzeni,
    }
    figure = plotZipf(
        texts,
        "Prawo Zipfa - książki Michała Bałuckiego [wyrazy]",
    )
    figure.savefig(PATH / "zipf1.svg")
    heaps = plotHeaps(texts, "Prawo Heapsa - książki Michała Bałuckiego [wyrazy]")
    heaps.savefig(PATH / "heaps1.svg", dpi=200)


def num2():
    """
    2. wybierając 3 teksty jednego autora w jednym dowolnym języku; przeanalizować lematy
    """
    texts = {
        "Biały Murzyn": balucki_BialyMurzyn,
        "Pan Burmistrz": balucki_PanBurmistrz,
        "Przebudzeni": balucki_Przebudzeni,
    }
    figure = plotZipf(
        texts,
        "Prawo Zipfa - książki Michała Bałuckiego [lematy]",
        select=lambda w: w.lemma,
    )
    figure.savefig(PATH / "zipf2.svg")
    heaps = plotHeaps(
        texts,
        "Prawo Heapsa - książki Michała Bałuckiego [lematy]",
        select=lambda w: w.lemma,
    )
    heaps.savefig(PATH / "heaps2.svg", dpi=200)


def num3():
    """
    3. wybierając jeden długi tekst w dowolnym języku; przeanalizować wyrazy osobno dla >= 3 wybranych części mowy
    """

    nouns: list[Word] = [word for word in sienkewicz_QuoVadis if word.pos == "NOUN"]
    verbs: list[Word] = [word for word in sienkewicz_QuoVadis if word.pos == "VERB"]
    adjectives: list[Word] = [word for word in sienkewicz_QuoVadis if word.pos == "ADJ"]

    texts = {
        "Cały tekst": sienkewicz_QuoVadis,
        "Rzeczowniki": nouns,
        "Czasowniki": verbs,
        "Przymiotniki": adjectives,
    }
    figure = plotZipf(
        texts,
        "Prawo Zipfa - 'Quo vadis' [3 części mowy]",
    )
    figure.savefig(PATH / "zipf3.svg")
    heaps = plotHeaps(texts, "Prawo Heapsa - 'Quo vadis' [3 części mowy]")
    heaps.savefig(PATH / "heaps3.svg", dpi=200)


def num4():
    """
    4. wybierając >=3 teksty różnych autorów w jednym dowolnym języku; przeanalizować wyrazy
    """

    texts = {
        "Biały Murzyn": balucki_BialyMurzyn,
        "Quo Vadis": sienkewicz_QuoVadis,
        "Fatum": krzemienicka_Fatum,
    }
    figure = plotZipf(
        texts,
        "Prawo Zipfa - Bałucki, Sienkiewicz, Krzemienicka",
    )
    figure.savefig(PATH / "zipf4.svg")
    heaps = plotHeaps(texts, "Prawo Heapsa - Bałucki, Sienkiewicz, Krzemienicka")
    heaps.savefig(PATH / "heaps4.svg", dpi=200)


def num5():
    """
    5. wybierając >=3 teksty z różnych języków; przeanalizować wyrazy
    """
    texts = {
        "Biały Murzyn": balucki_BialyMurzyn,
        "The Life and Adventures of Michael Armstrong": trollope_Armstrong,
        "Feldblumen": stifter_Feldblumen,
    }
    figure = plotZipf(
        texts,
        "Prawo Zipfa - polski, angielski, niemiecki",
    )
    figure.savefig(PATH / "zipf5.svg")
    heaps = plotHeaps(texts, "Prawo Heapsa - polski, angielski, niemiecki")
    heaps.savefig(PATH / "heaps5.svg", dpi=200)


num1()
num2()
num3()
num4()
num5()
