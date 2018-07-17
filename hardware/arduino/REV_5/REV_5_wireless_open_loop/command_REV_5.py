import socket
import time

UDP_PORT = 4210

def send_command(command):
    # addr = "192.168.0." + str(110 + bot_id) # Ask Pat about how to authomatically search
    addr = "192.168.4.1" # Hardcoded host ID for communication
    print(addr)
    sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

    MESSAGE = str(command)
    
    sock.sendto(str.encode(MESSAGE), (addr, UDP_PORT))

while 1:
	welcome_message = "Hello, please enter the command ('s' or 'x'):\n"
	print(welcome_message)
	command = input()
	if command == "exit":
		exit(1)
	else:
		send_command(command)