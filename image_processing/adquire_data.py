#######################################################################
#
#   Adquire data from sensor matrix
# 
#
#######################################################################

import cv2
import numpy as np
import serial
import time
import shutil
import os

def read_matrix(serial_port):

	matriz = []

	try:
	# while for receive 'begin' in the comunication
		for i in range (1,1000):
			if(serial_port.readline().decode('utf-8') == 'begin\n'):
				for i in range(1,8):
					line = serial_port.readline().decode('utf-8').split(',')
					line = line[:7]
					line = [int(i) for i in line]
					matriz.append(line)
				# build the image from the readings
				image = np.zeros((7,7,3), np.uint8)
				image[:,:,0] = matriz
				image[:,:,1] = matriz
				image[:,:,2] = matriz
				return(image)
	except:
		raise SystemExit('Error: Imposible to read the serial port')

def main ():

	# Open and configure the seial comunication
	port = serial.Serial()
	port.baudrate = 115200
	port.timeout = 1
	port.port = '/dev/ttyACM0'
	port.open()

	j=0
	i=88
	photo = np.zeros((7,7,3), np.uint8)
	ok_flag = True
	while ok_flag:
		try:
			img = read_matrix(port)
			j+=1
			if(j==50):
				photo = img
				cv2.imwrite(str(i)+'.png',img)
				shutil.move(str(i)+'.png', "samples/")
				i+=1
				j=0
			ok_flag = True
		except:
			pass
		frame = np.concatenate((img, photo), axis=1)
		cv2.namedWindow('Matrix Readings', cv2.WINDOW_NORMAL)
		cv2.resizeWindow('Matrix Readings', 300, 300)
		cv2.imshow('Matrix Readings', frame)
		if cv2.waitKey(1) & 0xFF == ord('q'):
			ok_flag = False
			break
			#while(~(cv2.waitKey(1) & 0xFF == ord('q'))):
			#	pass
	cv2.destroyAllWindows()

if __name__ == "__main__":
 	main()
