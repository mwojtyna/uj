import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path
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
    360 - 282.8,
    360 - 294.5,
    360 - 303.9,
    360 - 311.9,
    360 - 318.2,
    360 - 323.4,
    360 - 327.7,
    360 - 331.0,
    360 - 333.6,
    360 - 335.9,
    360 - 347.3,
    360 - 351.5,
    360 - 353.6,
    360 - 354.8,
    360 - 355.7,
    360 - 356.3,
    360 - 356.7,
    360 - 357.1,
    360 - 357.4,
    360 - 358.8,
    360 - 239.1,
    360 - 358.8,
    360 - 359.5,
    360 - 359.5,
    360 - 359.5,
    360 - 359.5,
    360 - 359.5,
    360 - 359.7,
    360 - 359.6,
    360 - 294.3,
]

f_d = 450
tau = 0.0003503
plot_freq = np.logspace(np.log10(min(freq)), np.log10(max(freq)), 500)
output_dir = Path(__file__).resolve().parent / "img"


def theoretical_amp(f):
    scaled_frequency = f / f_d
    return scaled_frequency / np.sqrt(1 + scaled_frequency**2)


def theoretical_phase(f):
    return np.rad2deg(np.pi / 2 - np.arctan(2 * np.pi * f * tau))


def amp_graph():
    plt.figure()
    plt.semilogx(freq, amp, marker="o", linestyle="", label="Pomiar")
    plt.semilogx(
        plot_freq,
        theoretical_amp(plot_freq),
        label=rf"Krzywa teoretyczna, $f_d={f_d}\,\mathrm{{Hz}}$",
    )
    ax = plt.gca()
    decimal_formatter = FuncFormatter(lambda value, _: f"{value:g}")
    ax.yaxis.set_major_formatter(decimal_formatter)
    ax.yaxis.set_minor_formatter(decimal_formatter)
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Uwy/Uwe")
    plt.grid(True)
    plt.legend()
    plt.savefig(output_dir / "cr_amp_graph.svg", bbox_inches="tight")
    plt.close()


def phase_graph():
    plt.figure()
    plt.semilogx(freq, phase, marker="o", linestyle="", label="Pomiar")
    plt.semilogx(plot_freq, theoretical_phase(plot_freq), label="Krzywa teoretyczna")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Faza [°]")
    plt.grid(True)
    plt.legend()
    plt.savefig(output_dir / "cr_phase_graph.svg", bbox_inches="tight")
    plt.close()


def main():
    amp_graph()
    phase_graph()


if __name__ == "__main__":
    main()
