import matplotlib.pyplot as plt

MEASUREMENT_NAMES = ["Remove last vertex", "Remove middle vertex"]

results = [
    [100.00000000, 53.40000000, 49.91000000],
    [250.00000000, 951.96400000, 123.00000000],
    [500.00000000, 3259.68200000, 411.70200000],
    [1000.00000000, 3412.63200000, 812.81500000],
    [2000.00000000, 3914.31550000, 1857.64200000],
    [3000.00000000, 4601.19700000, 4604.76700000],
    [4000.00000000, 5559.88650000, 7400.31100000],
    [5000.00000000, 6308.66340000, 11375.05860000],
]


def main():
    n_values = [row[0] for row in results]
    for index, name in enumerate(MEASUREMENT_NAMES, start=1):
        measurements = [row[index] for row in results]
        plt.plot(n_values, measurements, marker="o", label=name)

    plt.xlabel("N")
    plt.ylabel("Time per operation (ns)")
    plt.title("Graph removeVertex() Benchmark Results")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
