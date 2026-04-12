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
]

amp = [
    968.2 / 1000,
    903.8 / 1000,
    824.2 / 1000,
    735.7 / 1000,
    655.5 / 1000,
    592.2 / 1000,
    528.2 / 1000,
    479.8 / 1000,
    439.6 / 1000,
    399.8 / 1000,
    216.2 / 1000,
    136.0 / 1000,
    104.0 / 1000,
    87.97 / 1000,
    71.97 / 1000,
    55.94 / 1000,
    56.0 / 1000,
    40.0 / 1000,
    39.97 / 1000,
    15.98 / 1000,
    8.008 / 1000,
]


phase = [
    -12.60,
    -24.06,
    -33.70,
    -40.61,
    -47.93,
    -53.42,
    -57.12,
    -60.37,
    -63.16,
    -65.47,
    -76.63,
    np.nan,
    np.nan,
    np.nan,
    np.nan,
    np.nan,
    np.nan,
    np.nan,
    np.nan,
    np.nan,
    np.nan,
]

f_g = 440
tau = 0.0003503
plot_freq = np.logspace(np.log10(min(freq)), np.log10(max(freq)), 500)
output_dir = Path(__file__).resolve().parent / "img"


def theoretical_amp(frequency):
    return 1 / np.sqrt(1 + (frequency / f_g) ** 2)


def theoretical_phase(f):
    return np.rad2deg(-np.arctan(2 * np.pi * f * tau))


def amp_graph():
    plt.figure()
    plt.semilogx(freq, amp, marker="o", linestyle="", label="Pomiar")
    plt.semilogx(
        plot_freq,
        theoretical_amp(plot_freq),
        label=rf"Krzywa teoretyczna, $f_d={f_g}\,\mathrm{{Hz}}$",
    )
    ax = plt.gca()
    decimal_formatter = FuncFormatter(lambda value, _: f"{value:g}")
    ax.yaxis.set_major_formatter(decimal_formatter)
    ax.yaxis.set_minor_formatter(decimal_formatter)
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Uwy/Uwe")
    plt.grid(True)
    plt.legend()
    plt.savefig(output_dir / "rc_amp_graph.svg", bbox_inches="tight")
    plt.close()


def phase_graph():
    valid_phase = np.isfinite(phase)
    plt.figure()
    plt.semilogx(
        np.array(freq)[valid_phase],
        np.array(phase)[valid_phase],
        marker="o",
        linestyle="",
        label="Pomiar",
    )
    plt.semilogx(plot_freq, theoretical_phase(plot_freq), label="Krzywa teoretyczna")
    plt.xlabel("Częstotliwość [Hz]")
    plt.ylabel("Faza [°]")
    plt.grid(True)
    plt.legend()
    plt.savefig(output_dir / "rc_phase_graph.svg", bbox_inches="tight")
    plt.close()


def main():
    amp_graph()
    phase_graph()


if __name__ == "__main__":
    main()
