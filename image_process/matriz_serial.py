import time
import serial
import numpy as np
from matplotlib import pyplot as plt
import cv2
import sys

def read_detection(serial_port):
	
	matriz1 = []
	
	try:
	# while for receive 'begin' in the comunication
		for i in range (1,100):
			if(serial_port.readline().decode('utf-8') == 'begin\n'):
				for i in range(1,8):
					line = serial_port.readline().decode('utf-8').split(',')
					line = line[:7]
					line = [int(i) for i in line]
					matriz1.append(line)
				# construct the image from the readings
				image = np.zeros((7,7,3), np.uint8)
				image[:,:,0] = matriz1
				image[:,:,1] = matriz1
				image[:,:,2] = matriz1
				return(image)
	except:
		raise SystemExit('Error: Imposible to read the serial')

def hough_line(img):

	# Rho and Theta ranges
	thetas = np.deg2rad(np.arange(-90.0, 90.0))
	width, height = img.shape
	diag_len = np.ceil(np.sqrt(width * width + height * height))   # max_dist
	rhos = np.linspace(-diag_len, diag_len, diag_len * 2.0)

	# Cache some resuable values
	cos_t = np.cos(thetas)
	sin_t = np.sin(thetas)
	num_thetas = len(thetas)

	# Hough accumulator array of theta vs rho
	accumulator = np.zeros((2 * diag_len, num_thetas), dtype=np.uint64)
	y_idxs, x_idxs = np.nonzero(img)  # (row, col) indexes to edges

	# Vote in the hough accumulator
	for i in range(len(x_idxs)):
		x = x_idxs[i]
		y = y_idxs[i]

		for t_idx in range(num_thetas):
			# Calculate rho. diag_len is added for a positive index
			rho = round(x * cos_t[t_idx] + y * sin_t[t_idx]) + diag_len
			accumulator[rho, t_idx] += 1

	# Easiest peak finding based on max votes
	idx = np.argmax(accumulator)
	rho = round(rhos[idx / accumulator.shape[1]])-1
	theta = thetas[idx % accumulator.shape[1]]

	return theta, rho

def line_ecuation_calc(theta, rho):
	m = round(-1*np.cos(theta)/np.sin(theta))
	b = round(rho/np.sin(theta))
	print('y = ',m,'x + ',b)
	return m, b

def line_aproximation(img_centre, theta, centre_x, m, b):
	if theta == -90 or theta == 90:
		draw_lineDetected(img_centre,theta, m, b)
		print('Horizontal')
	elif -5 < theta and theta < 5:
		draw_lineDetected(img_centre, theta, m, b)
		print('Vertical')
		print ('Offset = %.0f' % (centre_x-3))
	elif theta > 5:
		print('Right')
		draw_lineDetected(img_centre, theta, m, b)
		print ('Degrees = %.0f' % (90-np.degrees(np.arctan(abs(m)))))
		print ('Offset = %.0f' % (centre_x-3))
	elif theta < -5:
		print('Left')
		draw_lineDetected(img_centre, theta, m ,b)
		print ('Degrees = %.0f' % (90-np.degrees(np.arctan(abs(m)))))
		print ('Offset = %.0f' % (centre_x-3))
	else:
			raise SystemExit('Error: Dirreción no conocida (Right, Left, Horizontal, Vertical')

def line_centre_calc(theta, rho):
	centre_x = rho*np.cos(theta)
	centre_y = rho*np.sin(theta)
	return centre_x, centre_y

def draw_lineDetected(img, theta, m, b):

	for x in range(7):
		if theta > 0 :
			a = m*x+b
		else:
			a = m*x+b
			
		if(a < 7 and a > 0):
			img[a][x] = [255,0,0]

	return img

def main ():

	# Open and configure the seial comunication
	port = serial.Serial()
	port.baudrate = 115200
	port.timeout = 1
	port.port = '/dev/ttyACM0'
	port.open()

	# Reboot the arduino
	port.setDTR(False)
	time.sleep(1)
	port.flushInput()
	port.setDTR(True)


	img = read_detection(port)

	#cv2.imwrite('prueba4.png',img)

	# image acondition
	img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	ret, img_thres = cv2.threshold(img_gray, 120, 255, cv2.THRESH_BINARY)

	# Line aproximation calc
	theta, rho = hough_line(img_thres)
	centre_x, centre_y = line_centre_calc(theta, rho)
	m, b = line_ecuation_calc(theta, rho)
	img_centre = cv2.cvtColor(img_thres, cv2.COLOR_GRAY2BGR)
	theta = int(np.rad2deg(theta))
	line_aproximation(img_centre, theta, centre_x, m, b)

	#img_centre[round(centre_y)][round(centre_x)]= [0,255,0]

	# show images
	fig = plt.figure('Line Follower')
	fig_a=fig.add_subplot(2,2,1)
	fig_a.set_title('Sensor Matrix')
	imgplot = plt.imshow(img, cmap='Greys')
	plt.axis("off")
	fig_a=fig.add_subplot(2,2,2)
	fig_a.set_title('Threshold Image')
	imgplot = plt.imshow(img_thres, cmap='Greys')
	plt.axis("on")
	fig_a=fig.add_subplot(2,2,3)
	fig_a.set_title('Line Aproximation')
	imgplot = plt.imshow(img_centre, cmap='Greys')
	plt.axis("on")
	plt.show()

	# Close serial port
	port.close()

if __name__ == "__main__":
 	main()


