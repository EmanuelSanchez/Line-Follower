import cv2
import numpy as np
from matplotlib import pyplot as plt
from examples import *

def construc_image(example):

	img_pix = np.zeros((7,7,3), np.uint8)

	img_pix[:,:,0] = ex
	img_pix[:,:,1] = ex
	img_pix[:,:,2] = ex

	img = np.zeros((7,7,3), np.uint8)

	img[:,:,0] = example
	img[:,:,1] = example
	img[:,:,2] = example

	img_original = img.copy()

	return img_pix, img_original, img

def hough_line(img):
  print(img)
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

def draw_lineDetected(img, m, b):
	#print(m, b)

	for x in range(7):
		if theta > 0 :
			a = m*x+b
		else:
			a = m*x+b
		#print(x, a)
		if(a < 7 and a > 0):
			img[a][x] = [255,0,0]

	return img

def line_centre_calc(theta):
	centre_x = rho*np.cos(theta)
	centre_y = rho*np.sin(theta)
	return centre_x, centre_y

def line_ecuation_calc(theta, rho):
	m = round(-1*np.cos(theta)/np.sin(theta))
	b = round(rho/np.sin(theta))
	print('y = ',m,'x + ',b)
	return m, b

def line_aproximation(img_centre, theta, centre_x, m, b):
	if theta == -90 or theta == 90:
		print('Horizontal')
	elif -5 < theta and theta < 5:
		print('Vertical')
		print ('Offset = %.0f' % (centre_x-3))
	elif theta > 5:
		print('Right')
		draw_lineDetected(img_centre, m, b)
		print ('Degrees = %.0f' % (90-np.degrees(np.arctan(abs(m)))))
		print ('Offset = %.0f' % (centre_x-3))
	elif theta < -5:
		print('Left')
		draw_lineDetected(img_centre, m ,b)
		print ('Degrees = %.0f' % (90-np.degrees(np.arctan(abs(m)))))
		print ('Offset = %.0f' % (centre_x-3))
	else:
		raise SystemExit('Error: Dirreción no conocida (Right, Left, Horizontal, Vertical')

img_original = cv2.imread('prueba4.png')
img_pix = cv2.imread('prueba4.png')
img = cv2.imread('prueba4.png')
#img_pix, img_original, img = construc_image(ex11)
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
ret,img_th = cv2.threshold(img_gray,120,255,cv2.THRESH_BINARY)

# Create binary image and call hough_line
#image = np.zeros((7,7))
#image[:7, :7] = np.eye(7)

theta, rho = hough_line(img_th)

centre_x, centre_y = line_centre_calc(theta)

m, b = line_ecuation_calc(theta, rho)

img_centre = cv2.cvtColor(img_th, cv2.COLOR_GRAY2BGR)

theta = int(np.rad2deg(theta))

line_aproximation(img_centre, theta, centre_x, m, b)

img_centre[round(centre_y)][round(centre_x)]= [0,255,0]


#img_th[centre_x-1][centre_y-1]=[]

#print ('rho= %.2f   theta= %.0f' % (rho, theta))
#print ('y = %.0f x + %.0f' % (m, b))
#print ('Centre: X= %.0f    Y= %.0f' % (centre_x, centre_y))


fig = plt.figure('Line Follower')
fig_a=fig.add_subplot(1,2,1)
fig_a.set_title('Pixeles')
imgplot = plt.imshow(img_pix, cmap='Greys')
plt.axis("off")
fig_a=fig.add_subplot(1,2,2)
fig_a.set_title('Image')
imgplot = plt.imshow(img_centre, cmap='Greys')
plt.axis("on")
plt.show()