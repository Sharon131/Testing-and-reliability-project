# PYTHON 3.10
# how the script works:
# input argument: desired frequency
# the script checks each com port and finally connects with the test board
# then it sets the desired cpu frequency and reads the id from ICM20948 sensor
# finally, the script prints out the ICM20948 ID

from comm_functions import response_is_correct
from comm_functions import COM_BAUD_RATE
import serial


com_port  = input()
spi_speed = input()

# check spi speed - all faith put in teststand
# if not (1 <= int(spi_speed) <= 80):
#     print(f"Error! invalid input frequency (1-80), was:{spi_speed}\n")
#     exit(-2)

try:
    # connect with the board
    ser = serial.Serial(com_port, COM_BAUD_RATE, timeout=1)

    # clear serial from any buffered data
    ser.read_until(expected=b'\n')

    # set desired SPI speed
    ser.write(bytes(f"freq:{spi_speed}.", 'utf-8'))

    # check if the board successfully changed the frequency
    if not response_is_correct(serial_object=ser, is_silent=True):
        exit(1)

    # get ICM20948 id from the test board
    ser.write(bytes("id.", 'utf-8'))

    # check if the board executed the command
    if not response_is_correct(serial_object=ser, is_silent=False):
        exit(1)

    # get the ID
    read_bytes = ser.read_until(expected=b'\n').decode('utf-8')

    # print out the response
    print(f"ID:{read_bytes}\n")

    # close the COM port
    ser.close()
except:
    print("COMM ERROR")