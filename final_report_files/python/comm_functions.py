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
            ser = serial.Serial(port.device, COM_BAUD_RATE, timeout=1)                  # connect with tester com port
            ser.write(bytes("ok.", 'utf-8'))                                            # write a test command
            is_correct_port = response_is_correct(serial_object=ser, is_silent=True)    # read the response
            ser.close()                                                                 # close port
            if is_correct_port:                                                         # check if the response is correct
                return port.device
        except:
            pass
            #print(f"Cannot connect with port {port.device}!!")

    #print("Error! Couldn't find the test board!")
    #exit(-3)
    return "NONE"
