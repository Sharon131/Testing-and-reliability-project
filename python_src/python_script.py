import serial
from serial.tools import list_ports

# spi_speed = int(input())
spi_speed = input()

# TODO: check spi speed?

ports = list(list_ports.grep(r'.*STM.*'))
ser = serial.Serial(ports[0].device, 115200)    # TODO: baud rate to change?

ser.write(bytes(spi_speed, "ascii"))

read_bytes = ser.read_until(terminator=b';').decode('utf-8')

print("Response:", read_bytes, "\n")
