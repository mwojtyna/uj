import re
import subprocess
from pathlib import Path
import os

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

ROOT = Path(__file__).resolve().parent
IMG = ROOT / "img"
TMP = ROOT / "tmp"
TMP.mkdir(exist_ok=True)


def frequency_from_name(name):
    match = re.search(r"_([0-9]+)(k?)Hz\.png$", name)
    if not match:
        raise ValueError(f"Cannot parse frequency from {name}")
    value = float(match.group(1))
    if match.group(2) == "k":
        value *= 1000
    return value


FILES = sorted(
    IMG.glob("1.15.*_opamp_oscy_sinus_5V_*.png"),
    key=lambda path: frequency_from_name(path.name),
)


def parse_value(text, meas_number):
    # Search within the specific section for robustness
    start_idx = text.find(f"Meas {meas_number}")
    if start_idx == -1:
        raise ValueError(f"Meas {meas_number} not found in text:\n{text}")

    next_meas_number = meas_number + 1
    end_idx = text.find(f"Meas {next_meas_number}")
    if end_idx == -1:
        end_idx = len(text)

    section = text[start_idx:end_idx]

    # Match a number followed by V, mV, mvV, Hz, kHz, MHz
    match = re.search(
        r"([0-9]+(?:[.,][0-9]+)?)\s*(V|mV|mvV|Hz|kHz|MHz)", section, re.IGNORECASE
    )
    if not match:
        raise ValueError(
            f"Cannot parse value in section for Meas {meas_number}:\n{section}"
        )

    value = float(match.group(1).replace(",", "."))
    unit = match.group(2)

    if unit.lower() in ("mv", "mvv"):
        value /= 1000.0
    elif unit.lower() == "khz":
        value *= 1000.0
    elif unit.lower() == "mhz":
        value *= 1000000.0

    return value


def ocr_measurements(path):
    crop = TMP / f"{path.stem}_measurements.png"
    subprocess.run(
        [
            "magick",
            str(path),
            "-crop",
            "175x300+1105+220",
            "-resize",
            "400%",
            "-colorspace",
            "Gray",
            "-sharpen",
            "0x1",
            str(crop),
        ],
        check=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    result = subprocess.run(
        ["tesseract", str(crop), "stdout", "--psm", "6"],
        check=True,
        text=True,
        capture_output=True,
    )
    text = result.stdout
    return parse_value(text, 2), parse_value(text, 3)


def format_frequency(freq):
    return f"{freq:,.0f}".replace(",", " ")


def main():
    data = []
    for path in FILES:
        input_frequency, output_amplitude = ocr_measurements(path)
        data.append((input_frequency, output_amplitude, path.name))
        print(f"{path.name}: f={input_frequency:g} Hz, Uwy={output_amplitude:g} V")

    freq = np.array([row[0] for row in data])
    amp = np.array([row[1] for row in data])

    plt.figure()
    plt.semilogx(freq, amp, marker="o", linestyle="", label="Pomiar")

    # Match the formatter style of lab 02
    ax = plt.gca()
    decimal_formatter = FuncFormatter(lambda value, _: f"{value:g}")
    ax.xaxis.set_major_formatter(decimal_formatter)

    plt.xlabel("Częstotliwość sygnału wejściowego [Hz]")
    plt.ylabel("Amplituda sygnału wyjściowego [V]")
    plt.grid(True, which="both", ls="-")
    plt.legend()
    plt.savefig(IMG / "opamp_sinus_amplituda.svg", bbox_inches="tight")
    plt.close()

    # Create typst table contents
    rows = []
    for input_frequency, output_amplitude, _ in data:
        rows.append(
            f"    [{format_frequency(input_frequency)}], [{output_amplitude:.3f}],"
        )
    (ROOT / "opamp_sinus_amplituda_table.typ").write_text(
        "\n".join(rows) + "\n", encoding="utf-8"
    )
    print("Table rows saved to opamp_sinus_amplituda_table.typ")


if __name__ == "__main__":
    main()
