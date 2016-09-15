import time
import serial
import numpy as np


matriz = np.zeros((7,7), np.uint8)


ser = serial.Serial()
ser.baudrate = 115200
ser.timeout = 1
ser.port = '/dev/ttyACM0'
ser.open()

ser.setDTR(False)
time.sleep(1)
ser.flushInput()
ser.setDTR(True)

for i in range(1,15):
	
	try:
		a = ser.readline()
		print (a)
		#a = str(ser.readline())
		#print(a[2:])
		#if(str(a[2:])=='begin\n')
	except:
		pass



'''
for i in range(1,8):
	try:
		line = str(ser.readline())
		print(line)
		for j in range(1,8):
			print(line.plit[','])
			matriz[i][j-1] = int(line.plit[','][2:])
	except:
		pass

print(matriz)
'''
#for i in range(1,100):
#	a = ser.read()
#	print(int(a))
#	print(type(a))
#print(ser.read(10))

ser.close()


