import serial
import serial.tools.list_ports
import time

def find_arduino_port():
    arduino_keywords = [
        'Arduino', 
        'CH340', 
        'USB-SERIAL', 
        'CDC', 
        'VID:2341'
    ]  
    arduino_uno_keywords = [
        "Arduino Uno",
        "VID_2341",
        "PID_0043",
        "ATmega328P",
        "USB Serial"
    ]
    ports = serial.tools.list_ports.comports()
    for port in ports:
        desc = port.description.lower()
        if any(keyword.lower() in desc for keyword in arduino_uno_keywords):
            return port.device  # e.g., 'COM7'
    return None

def open_serial(port, baudrate=9600, timeout=2):
    try:
        arduino = serial.Serial(port, baudrate, timeout=timeout)
        time.sleep(2)  # Allow Arduino to autoreset
        return arduino
    except serial.SerialException as e:
        print(f"Serial connection failed: {e}")
        return None
