# Arduino Peristalsis Motor CLI

Control a DC motor via Arduino to simulate organ-like peristaltic motion from the command line. This CLI lets you set motor speed numerically or by using named presets corresponding to different organs.

---

## Table of Contents

- [Features](#features)
- [Quick Start](#quick-start)
- [Installation](#installation)
  - [Option 1: Clone the Repo](#option-1-clone-the-repo)
  - [Option 2: Download ZIP from GitHub](#option-2-download-zip-from-github)
- [Usage](#usage)
  - [Basic Commands](#basic-commands)
  - [Presets](#presets)
- [Project Structure](#project-structure)
- [Extending](#extending)

---

## Features

- CLI control of a DC motor connected to an Arduino.
- Speed as a float in [0.0, 1.0] or as a named preset.
- Test mode that runs without real hardware (dummy serial).
- Auto-detection of Arduino serial port, with manual override.
- Presets printed on every run for quick reference.

---

## Quick Start

Assuming you have Python and Git installed:

1. Clone the repository
git clone https://github.com/<your-username>/<your-repo-name>.git
cd <your-repo-name>

2. (Optional but recommended) create a virtual environment
python -m venv .venv

Windows
.venv\Scripts\activate

macOS/Linux
source .venv/bin/activate

3. Install Python dependencies
pip install -r requirements.txt

4. Run the CLI (test mode, no Arduino required)
python main.py stomach --test


Replace `<your-username>` and `<your-repo-name>` with your actual GitHub path.

---

## Installation

### Option 1: Clone the Repo

1. Open a terminal.
2. Run:

git clone https://github.com/<your-username>/<your-repo-name>.git
cd <your-repo-name>


3. (Optional) Create and activate a virtual environment:

python -m venv .venv

Windows
.venv\Scripts\activate

macOS/Linux
source .venv/bin/activate


4. Install dependencies:

pip install -r requirements.txt


5. Connect your Arduino (with the matching firmware sketch flashed) via USB.

### Option 2: Download ZIP from GitHub

1. Go to the repository page in your browser.
2. Click **Code → Download ZIP**.
3. Extract the ZIP somewhere on your machine.
4. Open a terminal in the extracted folder (e.g., right-click → "Open in Terminal" or `cd` into it).
5. (Optional) Create and activate a virtual environment as above.
6. Install dependencies:

pip install -r requirements.txt


7. Connect your Arduino via USB.

---

## Usage

From the project root (where `main.py` lives):

python main.py [speed] [--port PORT] [--test]


### Arguments

- `speed` (positional, optional)
  - Float in [0.0, 1.0], e.g. `0.3`, `0.7`.
  - Or a preset name (see [Presets](#presets)).
  - Defaults to `"0.5"` if omitted.
- `--port PORT` (optional)
  - Explicit serial port (e.g. `COM3`, `/dev/ttyUSB0`).
  - If omitted, the program attempts to auto-detect the Arduino.
- `--test` (optional flag)
  - Use a dummy serial connection (no hardware required).
  - Useful for development, demo, or when the Arduino is not plugged in.

### Basic Commands

Default speed (0.5), auto-detect port
python main.py

Numeric speed, auto-detect port
python main.py 0.7

Numeric speed on a specific port
python main.py 0.3 --port COM5

Named organ preset (e.g., 'stomach') in test mode
python main.py stomach --test


On startup, the program prints all available presets and their mapped speed values so you can see what is available each time you run it.

---

## Presets

Presets are defined in `main.py` like:

PRESET_SPEEDS = {
"esophagus": 0.8,
"stomach": 0.4,
"small_intestine": 0.5,
"colon": 0.2,
"ureter": 0.3,
}


Use any key as the `speed` argument:

python main.py esophagus
python main.py small_intestine --test


---

## Project Structure

A minimal layout for the CLI-only component:

<repo-root>/
├─ main.py # CLI entry point (argparse, presets, serial flow)
├─ serial_utils.py # find_arduino_port(), open_serial()
├─ arduino_controller.py # send_speed(arduino, speed)
├─ requirements.txt # Python dependencies (e.g., pyserial)
└─ README.md # This file


---

## Extending

- Add or adjust presets by editing `PRESET_SPEEDS` in `main.py`.
- Tune numeric values to match your motor, tubing, and fluid for realistic peristaltic behavior.
- Extend the CLI with additional parameters (e.g., frequency, waveform type) and update the Arduino firmware to handle them.
