import matplotlib.pyplot as plt
from pathlib import Path
from matplotlib.ticker import FuncFormatter

freq = [
    100.0,
    200.0,
    300.0,
    400.0,
    500.0,
    600.0,
    700.0,
    800.0,
    900.0,
    1000.0,
    2000.0,
    3000.0,
    4000.0,
    5000.0,
    6000.0,
    7000.0,
    8000.0,
    9000.0,
    10000.0,
    20000.0,
    30000.0,
    40000.0,
    50000.0,
    60000.0,
    70000.0,
    80000.0,
    90000.0,
    100000.0,
    200000.0,
    300000.0,
    400000.0,
    500000.0,
    600000.0,
    700000.0,
    800000.0,
    900000.0,
]

amp = [
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.997,
    9.840,
    9.840,
    9.761,
    9.604,
    9.289,
    5.277,
    3.518,
    2.780,
    2.259,
    1.882,
    1.620,
    1.419,
    1.240,
    1.100,
    0.5441,
    0.3518,
    0.2559,
    0.2000,
    0.1679,
    0.1359,
    0.1199,
    0.1040,
]

phase = [
    179.9,
    179.9,
    179.7,
    179.6,
    179.5,
    179.4,
    179.3,
    179.2,
    179.1,
    179.0,
    178.0,
    177.0,
    175.6,
    174.2,
    172.1,
    169.2,
    165.2,
    160.1,
    154.6,
    122.3,
    112.0,
    106.9,
    102.8,
    100.2,
    97.9,
    95.9,
    93.9,
    92.5,
    83.0,
    75.9,
    66.8,
    57.1,
    46.1,
    float("nan"),
    float("nan"),
    float("nan"),
]


output_dir = Path(__file__).resolve().parent / "img"


def amp_graph():
    plt.figure()
    plt.plot(freq, amp, marker="o")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Uwy [V]")
    plt.grid(True)
    plt.savefig(output_dir / "opamp_rev_amp_graph.svg", bbox_inches="tight")
    plt.close()


def phase_graph():
    plt.figure()
    plt.plot(freq, [180 + (180 - p) for p in phase], marker="o")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Faza [°]")
    plt.grid(True)
    plt.savefig(output_dir / "opamp_rev_phase_graph.svg", bbox_inches="tight")
    plt.close()


def main():
    amp_graph()
    phase_graph()


if __name__ == "__main__":
    main()
