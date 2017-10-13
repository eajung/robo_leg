#armBrain



import serial
import QLearning

goal = (0,0,30)
arm = QLearning.armAgent(goal)
reward = 0

# ser = serial.Serial('/dev/cu.usbmodem1441', 57600)
ser = serial.Serial('/dev/cu.usbmodem1441', 57600, timeout=1)
kp = 4
set_point = -30
while True:
    raw = ser.readline()
 
    raw = ser.readline()
    raw = raw.strip()
    dev_id,x,y,z = raw.split(',')
    # Raw X,Y,Z into those values from the arduino
    x = float(x)
    y = float(y)
    z = float(z)
    if z <= (goal[2]+.2)  and z>= (goal[2]-.2):
      reward = 5
      print 'I AM DONE'
      #break
    else:
      reward = 0
    action = arm.chooseAction((x,y,z), reward)
    ser.write(action + '\n')
    
    
    
    
    #error = set_point - z
    #output = error * kp
    #print z,output
    #ser.write(str(output) + '\n')