import serial			
# beforehand run: pip install pyserial
# BE CAREFUL!!! The package is called "pyserial", not "serial"
# If you installed serial by mistake, then:
# 1. uninstall both serial and pyserial by using pip uninstall
# 2. restart your machine
# 3. change the name of the python file you are trying to run (cache issues)

ser = serial.Serial(
    port='/dev/ttyUSB0',	# Replace with the port you want to read from
    baudrate=115200,		# Replace with the baudrate of the transaction
    parity=serial.PARITY_NONE,	# No parity bits
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None          	# Blocks until data is received
)

# Opens output.raw in binary write mode
with open('output.raw', 'wb') as file:
    while True:
        data = ser.read(4096)	# Number of bytes to be received and saved

        if data:
            file.write(data)

# For the change in the file to be seen, the program has to be terminated first
# with Ctrl+C or SIGTERM

ser.close()
