# Arduino Peristalsis Motor CLI

This command-line tool controls a DC motor (via Arduino) to simulate peristaltic motion at different speeds representing various organs. It wraps serial communication to an Arduino and exposes a simple CLI with numeric and named presets.

---

## Features

- Set motor speed as a numeric value between 0.0 (stop) and 1.0 (full speed).
- Use named presets corresponding to organ-like peristaltic patterns (e.g., `esophagus`, `stomach`).
- Optional test mode that runs without a real Arduino connected.
- Optional explicit serial port selection.
- Prints all available presets on every run.

---

## Requirements

- Python 3.8+
- An Arduino (e.g., Arduino Uno) flashed with the matching firmware sketch.
- `pyserial` (for serial communication), for example:
