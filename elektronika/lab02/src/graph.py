import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter

freq = [
    100,
    200,
    300,
    400,
    500,
    600,
    700,
    800,
    900,
    1000,
    2000,
    3000,
    4000,
    5000,
    6000,
    7000,
    8000,
    9000,
    10_000,
    20_000,
    30_000,
    40_000,
    50_000,
    60_000,
    70_000,
    80_000,
    90_000,
    100_000,
    200_000,
    300_000,
]

amp = [
    207.8 / 1000,
    400.0 / 1000,
    543.7 / 1000,
    663.7 / 1000,
    735.7 / 1000,
    799.7 / 1000,
    832.9 / 1000,
    864.0 / 1000,
    887.4 / 1000,
    903.8 / 1000,
    968.2 / 1000,
    975.7 / 1000,
    983.8 / 1000,
    983.8 / 1000,
    983.8 / 1000,
    983.8 / 1000,
    983.8 / 1000,
    983.8 / 1000,
    983.8 / 1000,
    991.9 / 1000,
    991.9 / 1000,
    991.9 / 1000,
    991.6 / 1000,
    999.7 / 1000,
    999.7 / 1000,
    999.7 / 1000,
    999.7 / 1000,
    999.7 / 1000,
    999.7 / 1000,
    999.4 / 1000,
]

phase = [
    282.8,
    294.5,
    303.9,
    311.9,
    318.2,
    323.4,
    327.7,
    331.0,
    333.6,
    335.9,
    347.3,
    351.5,
    353.6,
    354.8,
    355.7,
    356.3,
    356.7,
    357.1,
    357.4,
    358.8,
    239.1,
    358.8,
    359.5,
    359.5,
    359.5,
    359.5,
    359.5,
    359.7,
    359.6,
    294.3,
]


def amp_graph():
    plt.loglog(freq, amp, marker="o")
    ax = plt.gca()
    decimal_formatter = FuncFormatter(lambda value, _: f"{value:g}")
    ax.yaxis.set_major_formatter(decimal_formatter)
    ax.yaxis.set_minor_formatter(decimal_formatter)
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Uwy/Uwe")
    plt.grid(True)
    plt.show()


def phase_graph():
    plt.loglog(freq, phase, marker="o")
    ax = plt.gca()
    decimal_formatter = FuncFormatter(lambda value, _: f"{value:g}")
    ax.yaxis.set_major_formatter(decimal_formatter)
    ax.yaxis.set_minor_formatter(decimal_formatter)
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Faza [°]")
    plt.grid(True)
    plt.show()


def main():
    amp_graph()
    phase_graph()


if __name__ == "__main__":
    main()
