import serial
import time
import struct

ser = serial.Serial('/dev/tty.usbmodem14101', 9600, timeout=1)

# Sleep in seconds
time.sleep(1)

for i in range(0, 100):
    a = input(">>>")

    if i % 2 == 0:
        ser.write(b'E')
        ser.write(struct.pack('>BBBBBB', 60, 120, 60, 120, 60, 120))
    else:
        ser.write(b'X')
        ser.write(struct.pack('>BBBBBB', 90, 90, 90, 90, 90, 90))

    time.sleep(1)

ser.close()
