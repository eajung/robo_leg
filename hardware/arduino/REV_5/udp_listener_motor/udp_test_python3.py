import socket
import time

###UDP_IP = "192.168.1.124"
##UDP_IP = "192.168.1.107"
UDP_PORT = 4210
##
##
##print "UDP target IP:", UDP_IP
##print "UDP target port:", UDP_PORT
###print "message:", MESSAGE



##MESSAGE = "1,200"
##sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
##


##for i in range(0,1024,100):
##    
##    MESSAGE = "1," + str(i)
##    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
##    MESSAGE = "2," + str(1024-i)
##    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
##    time.sleep(1)


def send_command(bot_id,wheel,speed):
    # addr = "192.168.0." + str(110 + bot_id)
    addr = "192.168.4.1" # Hardcoded host ID
    print(addr)
    sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

    MESSAGE = str(wheel) + "," + str(speed)
    
    sock.sendto(str.encode(MESSAGE), (addr, UDP_PORT))

##send_command(1,500)
##time.sleep(0.1)
##send_command(2,450)
##time.sleep(3.5)
##send_command(2,700)
##time.sleep(4.5)
##send_command(2,450)
##time.sleep(0.1)
##send_command(2,300)
##time.sleep(7)
##send_command(1,0)
##time.sleep(0.1)
##send_command(2,0)
# send_command(1,3,500)
send_command(1,2,-500)
#send_command(1,1000)
#time.sleep(10)
#send_command(2,0)
#send_command(1,0)
