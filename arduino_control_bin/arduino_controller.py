def send_speed(ser, speed):
    """
    Sends the motor speed (normalized 0-1) to Arduino via serial.
    """
    if ser is not None:
        ser.write(f"{speed}\n".encode())
    else:
        print("Serial object is None, cannot send data.")
