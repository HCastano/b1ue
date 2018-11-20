import serial
import time

ser = serial.Serial('/dev/tty.usbmodem14101', 9600)
time.sleep(2)
ser.write(b'H')
ser.write(b'E')
ser.write(b'Y')

ser.close()
