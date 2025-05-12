import serial
# beforehand run: pip install pyserial
# BE CAREFUL!!! The package is called "pyserial", not "serial"
# If you installed serial by mistake, then:
# 1. uninstall both serial and pyserial by using pip uninstall
# 2. restart your machine
# 3. change the name of the python file you are trying to run (cache issues)

PORT = '/dev/ttyUSB0'
BAUD = 115200

with serial.Serial(PORT, BAUD, timeout=1) as ser:
    try:
        while True:
            data = ser.read(ser.in_waiting or 1)
            if data:
                print(data.decode(errors='replace'), end='')
    except KeyboardInterrupt:
        print("\nStopped by user.")
