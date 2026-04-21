import matplotlib.pyplot as plt

MEASUREMENT_NAMES = [
    "POP",
]

results = []


def main():
    n_values = [row[0] for row in results]

    for index, name in enumerate(MEASUREMENT_NAMES, start=1):
        measurements = [row[index] for row in results]
        plt.plot(n_values, measurements, marker="o", label=name)

    plt.xlabel("N")
    plt.ylabel("Time per operation (ms)")
    plt.title("SetLinked Benchmark Results")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
