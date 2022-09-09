# PYTHON 3.10
# how the script works:
# input argument: desired frequency
# the script checks each com port and finally connects with the test board
# then it sets the desired cpu frequency and reads the id from ICM20948 sensor
# finally, the script prints out the ICM20948 ID

import serial
from serial.tools import list_ports
from comm_functions import find_test_board_com_port_name

# get test board com port name
com_port = find_test_board_com_port_name()
print(f"PORT:{com_port}")