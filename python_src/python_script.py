import serial
from serial.tools import list_ports


def check_response():
    response = ser.read_until(terminator=b'\n').decode('utf-8')

    if response != "OK\n":
        print("Did not receive response from board\n")
        exit(-1)


# spi_speed = int(input())
spi_speed = input()

# TODO: check spi speed?

ports = list(list_ports.grep(r'.*STM.*'))
ser = serial.Serial(ports[0].device, 9600, timeout=1)

# clear serial from any buffered data
ser.read_until(terminator=b'\n')

ser.write(bytes(spi_speed, "ok."))

check_response()

ser.write(bytes(spi_speed, "freq:" + spi_speed))

check_response()

ser.write(bytes(spi_speed, "id01"))

check_response()

read_bytes = ser.read_until(terminator=b'\n').decode('utf-8')

print("Response:", read_bytes, "\n")
