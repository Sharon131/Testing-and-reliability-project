# PYTHON 3.10
# how the script works:
# input argument: desired frequency
# the script checks each com port and finally connects with the test board
# then it sets the desired cpu frequency and reads the id from ICM20948 sensor
# finally, the script prints out the ICM20948 ID

import serial
from serial.tools import list_ports

COM_BAUD_RATE = 9600


def response_is_correct(serial_object, is_silent):
    """Function waits for "OK\n" response from the test board for a time specified in serial_object.
    If the response differs from OK\n (or timeout occurs) then
    is_silent = False: the function exits the script with an exit value of -1.
    is_silent = True: the function returns False

    if response id OK then function returns True"""
    response = serial_object.read_until(expected=b'\n').decode('utf-8')

    if response != "OK\n":
        if is_silent:
            return False
        else:
            print("Did not receive response from board\n")
            exit(-1)

    return True


def find_test_board_com_port_name():
    """function gets the available com ports, connects to them and checks if the device connected to said com port
     responds with "OK\n" to a "ok." command. If the function finds the right test board,
     then if returns the com port name, closing the port.

     POSSIBLE MODIFICATION: write the last valid com port to a file and connect with it in the first place..."""
    ports = list(list_ports.comports(include_links=False))
    for port in ports:
        try:
            ser = serial.Serial(port.device, COM_BAUD_RATE, timeout=0.2)                # connect with tester com port
            ser.write(bytes("ok.", 'utf-8'))                                            # write a test command
            is_correct_port = response_is_correct(serial_object=ser, is_silent=True)    # read the response
            ser.close()                                                                 # close port
            if is_correct_port:                                                         # check if the response is correct
                return port.device
        except:
            print(f"Cannot connect with port {port.device}!!")

    print("Error! Couldn't find the test board!")
    exit(-3)


# get test board com port name
com_port = find_test_board_com_port_name()

# read the desired frequency - 1-80 MHz
# DEBUG
# print(f"Found! ({com_port}), enter freq: ")
spi_speed = input()

# check spi speed
if not (1 <= int(spi_speed) <= 80):
    print(f"Error! invalid input frequency (1-80), was:{spi_speed}\n")
    exit(-2)

# connect with the board
ser = serial.Serial(com_port, COM_BAUD_RATE, timeout=1)

# clear serial from any buffered data
ser.read_until(expected=b'\n')

# set desired SPI speed
ser.write(bytes(f"freq:{spi_speed}.", 'utf-8'))

# check if the board successfully changed the frequency
response_is_correct(serial_object=ser, is_silent=False)

# get ICM20948 id from the test board
ser.write(bytes("id.", 'utf-8'))

# check if the board executed the command
response_is_correct(serial_object=ser, is_silent=False)

# get the ID
read_bytes = ser.read_until(expected=b'\n').decode('utf-8')

# print out the response
print(f"Response:{read_bytes}\n")

# close the COM port
ser.close()