import matplotlib.pyplot as plt

MEASUREMENT_NAMES = ["Pop"]

results = [
    [1000.00000000, 32.13100000],
    [5000.00000000, 35.20220000],
    [10000.00000000, 36.63320000],
    [25000.00000000, 36.60020000],
    [50000.00000000, 37.23480000],
    [100000.00000000, 39.15092000],
    [250000.00000000, 38.69565200],
    [500000.00000000, 40.50122000],
    [1000000.00000000, 41.22131600],
    [2000000.00000000, 42.21943150],
    [3000000.00000000, 43.32086433],
    [5000000.00000000, 47.06192580],
    [10000000.00000000, 48.20546420],
    [20000000.00000000, 49.21545075],
    [30000000.00000000, 50.04052037],
    [40000000.00000000, 48.65937098],
    [50000000.00000000, 49.37413268],
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
