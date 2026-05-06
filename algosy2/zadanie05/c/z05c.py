import matplotlib.pyplot as plt

MEASUREMENT_NAMES = ["addVertex"]

results = [
    [100.00000000, 24.33020000],
    [250.00000000, 23.36500000],
    [500.00000000, 23.08574000],
    [1000.00000000, 23.41219000],
    [2000.00000000, 23.02861500],
    [3000.00000000, 23.88369333],
    [4000.00000000, 22.92854000],
    [5000.00000000, 22.37831000],
]


def main():
    n_values = [row[0] for row in results]

    for index, name in enumerate(MEASUREMENT_NAMES, start=1):
        measurements = [row[index] for row in results]
        plt.plot(n_values, measurements, marker="o", label=name)

    plt.ylim(bottom=0, top=30)
    plt.xlabel("N")
    plt.ylabel("Time per operation (ns)")
    plt.title("Graph addVertex() Benchmark Results")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
