import argparse
from serial_utils import find_arduino_port, open_serial
from arduino_controller import send_speed

class DummySerial:
    """Minimal 'dummy' serial object for test mode."""
    def __init__(self, port="TEST_PORT"):
        self.port = find_arduino_port

    def write(self, data):
        print(f"[TEST] Would write to {self.port}: {data!r}")

    def close(self):
        print(f"[TEST] Closing dummy serial on {self.port}")

def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Control Arduino motor speed via serial.")
    parser.add_argument(
        "speed",
        type=float,
        nargs='?',  # Optional argument
        default=0.5,
        help="Motor speed between 0.0 (stop) and 1.0 (full speed)"
    )
    parser.add_argument(
        "--port",
        type=str,
        default=None,
        help="Specify Arduino serial port (e.g., COM3 or /dev/ttyUSB0). Auto-detected if omitted."
    )
    parser.add_argument(
        "--test",
        action="store_true",
        help="Run in test mode with a dummy Arduino connection."
    )
    
    args = parser.parse_args()

    # Validate speed
    if not (0.0 <= args.speed <= 1.0):
        print("Error: Speed must be between 0.0 and 1.0")
        return

    # Determine port and connection
    if args.test:
        # Assume Arduino Uno is connected and create a dummy serial
        port = args.port or "ARDUINO_UNO_TEST"
        arduino = DummySerial(port=port)
        print(f"[TEST] Assuming Arduino Uno on {port}")
    else:
        # Real mode
        port = args.port or find_arduino_port()
        if port is None:
            print("Error: Could not auto-detect Arduino port. Try specifying --port manually.")
            return

        # Open serial connection
        arduino = open_serial(port)
        if arduino is None:
            print(f"Error: Could not connect to Arduino on {port}")
            return

    # CHECK
    print(f"SPEED: {args.speed:.2f}")
    print(f"PORT: {port}")

    try:
        # Send speed
        send_speed(arduino, args.speed)
        action = "stopped" if args.speed == 0.0 else f"set to {args.speed:.2f}"
        prefix = "[TEST] " if args.test else ""
        print(f"{prefix}✅ Motor {action} on {port}")
    finally:
        arduino.close()

if __name__ == "__main__":
    main()