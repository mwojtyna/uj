import matplotlib.pyplot as plt

MEASUREMENT_NAMES = ["Pop"]

results = [
    [1000.00000000, 12.36000000],
    [5000.00000000, 12.24800000],
    [10000.00000000, 12.26710000],
    [25000.00000000, 22.27972000],
    [50000.00000000, 12.12708000],
    [100000.00000000, 12.35838000],
    [250000.00000000, 12.72320000],
    [500000.00000000, 12.53328000],
    [1000000.00000000, 13.59378600],
    [2000000.00000000, 12.78000100],
    [3000000.00000000, 12.69502733],
    [5000000.00000000, 13.08665700],
    [10000000.00000000, 12.75553100],
]


def main():
    n_values = [row[0] for row in results]
    for index, name in enumerate(MEASUREMENT_NAMES, start=1):
        measurements = [row[index] for row in results]
        plt.semilogx(n_values, measurements, marker="o", label=name)

    plt.xlabel("N")
    plt.ylabel("Time per operation (ns)")
    plt.title("PriorityQueue pop() Benchmark Results")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
