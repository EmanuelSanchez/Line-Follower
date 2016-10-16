	######################################################################
#
# Sensor Matrox Line Follower Proccesing
#
######################################################################

import cv2
import numpy as np
from matplotlib import pyplot as plt
from examples import *


def construc_image(example):

	img0 = np.zeros((7,7,3), np.uint8)

	img0[:,:,0] = ex
	img0[:,:,1] = ex
	img0[:,:,1] = ex

	img = np.zeros((7,7,3), np.uint8)

	img[:,:,0] = example
	img[:,:,1] = example
	img[:,:,2] = example

	img_original = img.copy()

	return img_original, img0, img

def detec_line(image):
# HoughLinesP(source, rho accuray, theta accuracy, theshold, mim larch line, max larch betwer end and start)
	try:
		lines = cv2.HoughLinesP(image, 1, np.pi/180, 3, 3, 2)[0]
		for x1, y1, x2, y2 in lines:
			cv2.line(img, (x1,y1), (x2,y2), (0,255,0),1)
	except: #No_line_detected:
		raise SystemExit('Error: No line detected')
	return lines

def calc_angle(line):

	print('P1 = (',line[0][0],',',line[0][1],')')
	print('P2 = (',line[0][2],',',line[0][3],')')

	delta_x = line[0][0]-line[0][2]
	delta_y = line[0][1]-line[0][3]

	# direction :
	#	0 - left
	#	1 - right

	if delta_x == 0:
		direction = 'Vertical'
		alpha = 0
	elif delta_y == 0:
		direction = 'Horizontal'
		alpha = 180
	elif delta_y > 0:
		alpha = np.degrees(np.arctan(abs(delta_x)/abs(delta_y)))
		direction = 'Right'
	elif delta_y < 0:
		direction = 'Left'
		alpha = np.degrees(np.arctan(abs(delta_x)/abs(delta_y)))
	try:
		print(direction)
		print('Angle = ',alpha)
		return alpha
	except: 
		raise SystemExit('Error: Rare Direction')


img_original, img0, img = construc_image(ex11)

img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

ret,img_th = cv2.threshold(img_gray,120,255,cv2.THRESH_BINARY)

line = detec_line(img_th)

angle = calc_angle(line)

fig = plt.figure('Line Follower')
fig_a = fig.add_subplot(2,3,1)
fig_a.set_title('7x7 Matrix')
imgplot = plt.imshow(img0)
plt.axis("off")
fig_a=fig.add_subplot(2,3,2)
fig_a.set_title('Sensor Image')
imgplot = plt.imshow(img_original)
plt.axis("off")
fig_a=fig.add_subplot(2,3,3)
fig_a.set_title('Threshold')
imgplot = plt.imshow(img_th, cmap='Greys')
plt.axis("off")
fig_a=fig.add_subplot(2,3,4)
fig_a.set_title('Detection')
imgplot = plt.imshow(img)
plt.axis("off"
f)ig_a=fig.add_subplot(2,3,6)
fig_a.set_title('Detection')
imgplot = plt.imshow(img)
plt.axis("off")
plt.show()