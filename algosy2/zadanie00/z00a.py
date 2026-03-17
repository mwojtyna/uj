import matplotlib.pyplot as plt

MEASUREMENT_NAMES = [
    "Union",
    "Intersection",
    "Difference",
    "Equality",
    "Insert",
    "Remove",
    "Contains",
]

results = [
    [
        1000.00000000,
        0.06732000,
        0.07383100,
        0.07410000,
        0.00010000,
        0.00005048,
        0.00005118,
        0.00007182,
    ],
    [
        10000.00000000,
        0.66766500,
        0.77435500,
        0.78591500,
        0.00027000,
        0.00006939,
        0.00005274,
        0.00005028,
    ],
    [
        100000.00000000,
        6.83997500,
        7.54208000,
        7.44551900,
        0.00018000,
        0.00008262,
        0.00005562,
        0.00005080,
    ],
    [
        1000000.00000000,
        69.62632900,
        76.08664100,
        76.59604400,
        0.00010000,
        0.00005203,
        0.00005413,
        0.00005279,
    ],
    [
        5000000.00000000,
        343.01232000,
        375.34917300,
        383.09755300,
        0.00049000,
        0.00005179,
        0.00005399,
        0.00005614,
    ],
]


def main():
    n_values = [row[0] for row in results]

    for index, name in enumerate(MEASUREMENT_NAMES, start=1):
        measurements = [row[index] for row in results]
        plt.plot(n_values, measurements, marker="o", label=name)

    plt.xlabel("N")
    plt.ylabel("Time (ms)")
    plt.title("SimpleSet Benchmark Results")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
