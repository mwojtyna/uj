from collections import defaultdict
from collections.abc import Callable
import random
import time
import matplotlib.pyplot as plt
from sorts import *  # pyright: ignore[reportImplicitRelativeImport]


def timeExec(fun: Callable[[], None]) -> float:
    start_time = time.time()
    fun()
    return time.time() - start_time


def main():
    sorts: list[tuple[str, Callable[[list[int]], None]]] = [
        # O(n^2)
        # ("Bubble sort", bubble_sort),
        # ("Insertion sort", insertion_sort),
        # ("Selection sort", selection_sort),
        # O(nlogn)
        ("Heap sort", heap_sort),
        ("Quick sort", quicksort),
        ("Merge sort", merge_sort),
    ]

    sizes = [
        50,
        100,
        200,
        500,
        1_000,
        2_000,
        5_000,
        10_000,
        20_000,
        50_000,
        100_000,
        1_000_000,
    ]
    results: defaultdict[str, list[float]] = defaultdict(list)

    for n in sizes:
        base_arr = [random.randint(0, 10**6) for _ in range(n)]

        print(f"Testing array size = {n}")

        for name, sorter in sorts:
            arr = base_arr.copy()
            elapsed = timeExec(lambda: sorter(arr))
            results[name].append(elapsed)

    plt.figure(figsize=(10, 6))
    for name, times in results.items():
        plt.plot(sizes, times, marker="o", label=name)

    plt.title("Porównanie czasów wykonania algorytmów sortowania")
    plt.xlabel("Ilość danych")
    plt.ylabel("Czas wykonania [s]")
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.6)
    plt.tight_layout()
    plt.ticklabel_format(style="plain")
    plt.tick_params(axis="both", which="major", labelsize=10)
    plt.show()


if __name__ == "__main__":
    main()
