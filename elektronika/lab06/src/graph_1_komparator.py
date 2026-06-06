import re
import subprocess
from pathlib import Path
import os

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib")
import matplotlib.pyplot as plt
import numpy as np

ROOT = Path(__file__).resolve().parent
IMG = ROOT / "img"


def frequency_from_name(name):
    match = re.search(r"_([0-9]+)(k?)Hz\.png$", name)
    if not match:
        raise ValueError(f"Cannot parse frequency from {name}")
    value = float(match.group(1))
    if match.group(2) == "k":
        value *= 1000
    return value


FILES = sorted(
    IMG.glob("1.*_komparator_oscy_sinus_5V_*.png"),
    key=lambda path: frequency_from_name(path.name),
)


def parse_value(text, meas_number):
    pattern = (
        rf"Meas {meas_number}.*?[up][': ]+\s*([0-9]+(?:[.,][0-9]+)?)\s*([kM]?Hz|mV|V)"
    )
    match = re.search(pattern, text, re.DOTALL)
    if not match:
        raise ValueError(f"Cannot parse Meas {meas_number} from OCR text:\n{text}")

    value = float(match.group(1).replace(",", "."))
    unit = match.group(2)
    if unit == "V" and value > 100:
        value /= 1000
    if unit == "mV":
        value /= 1000
    if unit == "kHz":
        value *= 1000
    elif unit == "MHz":
        value *= 1_000_000
    return value


def ocr_measurements(path):
    crop = Path("/tmp") / f"{path.stem}_measurements.png"
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
    plt.xlabel("Częstotliwość sygnału wejściowego [Hz]")
    plt.ylabel("Amplituda sygnału wyjściowego [V]")
    plt.grid(True)
    plt.legend()
    plt.savefig(IMG / "komparator_sinus_amplituda.svg", bbox_inches="tight")
    plt.close()

    rows = []
    for input_frequency, output_amplitude, _ in data:
        rows.append(
            f"        [{format_frequency(input_frequency)}], [{output_amplitude:.3f}],"
        )
    (ROOT / "komparator_sinus_amplituda_table.typ").write_text(
        "\n".join(rows) + "\n", encoding="utf-8"
    )


if __name__ == "__main__":
    main()
