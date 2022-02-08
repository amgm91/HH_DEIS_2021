import serial
import time

ser = serial.Serial('/dev/uno', 9600, timeout = 1)
while True:
	