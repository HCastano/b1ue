import serial
import time

ser = serial.Serial('/dev/tty.usbmodem14101', 9600)
# Sleep in seconds
time.sleep(1)

for i in range(0, 10):
    a = input("Halur")
    if i % 2 == 0:
        ser.write(b'E')
    else:
        ser.write(b'X')
    time.sleep(1)

ser.close()

# A170 B30 C14
