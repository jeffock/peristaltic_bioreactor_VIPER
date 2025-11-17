from serial_utils import * 
from arduino_controller import send_speed

def main():
    port = find_arduino_port()  # Change as needed
    arduino = open_serial(port)
    if arduino is None:
        print(f"Could not connect to Arduino on {port}")
        return

    # Example: set motor speed to 0.6
    send_speed(arduino, 0.6)
    print("Speed sent!")

    arduino.close()

if __name__ == "__main__":
    main()
